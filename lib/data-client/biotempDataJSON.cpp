#include "biotempDataJSON.hpp"

// Método para simular o formato que iremos receber as configurações do broker/interface
 String BiotempDataJson::configPublisher() {
    JsonDocument sensor;
    sensor.clear();

        sensor["sensor_1_is_enabled"] = false;
        sensor["sensor_1_min_threshold"] = -1;
        sensor["sensor_1_max_threshold"] = -1;

        sensor["sensor_2_is_enabled"] = false;
        sensor["sensor_2_min_threshold"] = -1;
        sensor["sensor_2_max_threshold"] = -1;

        sensor["sensor_3_is_enabled"] = false;
        sensor["sensor_3_min_threshold"] = -1;
        sensor["sensor_3_max_threshold"] = -1;
    
    return sensor.as<String>();
}


void BiotempDataJson::handleConfigRequest(ConfigRequestDocument& configJson) {
    // Limpa as últimas configurações registradas antes de novas requisições
    temperature_handler.clearSensorMap();

    // Vetor temporário para armazenar as novas configurações
    std::vector<SensorConfig> newConfigs;

    // Extrai o JsonObject do ConfigRequestDocument
    JsonObject sensorConfig = configJson.as<JsonObject>();

    // Gera os códigos de erro a partir das configurações do sensor
    std::vector<uint8_t> error_codes = temperature_handler.errorCodeGenerate(sensorConfig);

    // Define os membros da classe para serem usados posteriormente em readBackJSON
    setSensorConfig(sensorConfig);    // Armazena a configuração do sensor
    setErrorCodes(error_codes);       // Armazena os códigos de erro

    for (int i = 1; i <= NUM_SENSORS; i++) {
        String sensorIsEnabledKey = "sensor_" + String(i) + "_is_enabled";
        String sensorMinThresholdKey = "sensor_" + String(i) + "_min_threshold";
        String sensorMaxThresholdKey = "sensor_" + String(i) + "_max_threshold";

        // Lê as configurações do JSON
        bool is_enabled = sensorConfig[sensorIsEnabledKey];
        float min_threshold = sensorConfig[sensorMinThresholdKey];
        float max_threshold = sensorConfig[sensorMaxThresholdKey];

        // Verifica se o sensor está habilitado
        if(is_enabled == true && sensorConfig[sensorIsEnabledKey].is<bool>()) {
        SensorConfig sensorConfigEntry;
        sensorConfigEntry.sensor_id = i;  // Define o ID do sensor como o índice
        sensorConfigEntry.is_enabled = is_enabled;
        sensorConfigEntry.min_threshold = min_threshold;
        sensorConfigEntry.max_threshold = max_threshold;

        // Adiciona a configuração ao vetor
        newConfigs.push_back(sensorConfigEntry);

        // Método para setar o sensor
        temperature_handler.addSensor(sensorConfigEntry.sensor_id);

        }
    }

    // Atualiza o temperature_handler com as novas configurações
    temperature_handler.setSensorConfigs(newConfigs);

    // Depois de configurar todos os sensores, verifica os thresholds
    for (const SensorConfig& config : newConfigs) {
        if (config.is_enabled) { 
            temperature_handler.checkThreshold(config.is_enabled, config.sensor_id, config.min_threshold, config.max_threshold);
        }
    }

    // Gera o JSON do readback que será publicado pelo publishReadBack na callBack
    readBackJSON();
    
}


String BiotempDataJson::mqttGeneratePacket() {
    JsonDocument mqttDoc;
    TempResults tempResults = temperature_handler.getAllTemperatures();
    mqttDoc.clear();

    // Starts the json with the default variables
    for(int i = 1; i <= 3; ++i){
        mqttDoc[std::string{"temp_"} + std::to_string(i)] = 0;
    }
    
    // Please generalize this
    std::map<std::string, std::string> SensorName2Id = {{"NTC1", "1"},
                                                        {"NTC2", "2"},
                                                        {"PT100", "3"}};

    for ( auto it = tempResults.begin(); it != tempResults.end(); ++it) {
        std::string sensorId = SensorName2Id[it->first];
        mqttDoc[std::string{"temp_"} + sensorId ] = String((it->second));
    }

   return mqttDoc.as<String>();
}

// Armazena a configuração do sensor
void BiotempDataJson::setSensorConfig(JsonObject& config) {
        sensorConfig = config;  
}

// Armazena os códigos de erro
void BiotempDataJson::setErrorCodes(const std::vector<uint8_t>& errors) {
        errorCodes = errors;  
}


String BiotempDataJson::readBackJSON() {
    JsonDocument readBackJSON;
    
    for (int i = 1; i <= NUM_SENSORS; i++) {
        String sensorIsEnabledKey = "sensor_" + String(i) + "_is_enabled";
        String sensorMinThresholdKey = "sensor_" + String(i) + "_min_threshold";
        String sensorMaxThresholdKey = "sensor_" + String(i) + "_max_threshold";
        String sensorErrorCodeKey = "sensor_" + String(i) + "_error_code";

        // Adiciona as configurações e o código de erro à resposta
        readBackJSON[sensorIsEnabledKey] = sensorConfig[sensorIsEnabledKey];
        readBackJSON[sensorMinThresholdKey] = sensorConfig[sensorMinThresholdKey];
        readBackJSON[sensorMaxThresholdKey] = sensorConfig[sensorMaxThresholdKey];
        readBackJSON[sensorErrorCodeKey] = errorCodes[i - 1];  // Acessa o código de erro correspondente
    }

    return readBackJSON.as<String>(); 
}