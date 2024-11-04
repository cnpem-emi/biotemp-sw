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

// void BiotempDataJson::handleConfigRequest(ConfigRequestDocument& configJson) {
//     // garrante que após novas requisições de configuração, limpe as ultimas configs registradas
//     temperature_handler.clearSensorMap();

//     // Criar um vetor temporário para armazenar as novas configurações
//     std::vector<SensorConfig> newConfigs;
//     JsonArray topicConfig = configJson["topic_config"];
//     newConfigs.clear();

//     // Iterando sobre as configurações recebidas
//     for (JsonObject sensorConfigJson : topicConfig) {
//         int8_t sensor_type = sensorConfigJson["sensor_type"];
//         int8_t sensor_id = sensorConfigJson["sensor_id"];
//         bool is_enabled = sensorConfigJson["is_enabled"];
//         float min_threshold = sensorConfigJson["min_threshold"];
//         float max_threshold = sensorConfigJson["max_threshold"];

//         if(sensor_type > 0 && is_enabled) {
//             SensorConfig sensorConfig;
//             sensorConfig.sensor_id = sensor_id;
//             sensorConfig.sensor_type = sensor_type;
//             sensorConfig.is_enabled = is_enabled;
//             sensorConfig.min_threshold = min_threshold;
//             sensorConfig.max_threshold = max_threshold;
            
//             // Adiciona a configuração ao vetor
//             newConfigs.push_back(sensorConfig);

//             // Método para escolher qual o tipo de sensor desejado
//             temperature_handler.addSensor(sensor_type);

//         } 
//     }

//     // Atualize o tempHandler com as novas configurações
//     temperature_handler.setSensorConfigs(newConfigs); 

//     // Depois de configurar todos os sensores, verifica os thresholds
//     for (const SensorConfig& config : newConfigs) {
//         if (config.is_enabled) { 
//             temperature_handler.checkThreshold(config.is_enabled, config.sensor_id, config.min_threshold, config.max_threshold);
//         }
//     }
// }

void BiotempDataJson::handleConfigRequest(ConfigRequestDocument& configJson) {
    // Limpa as últimas configurações registradas antes de novas requisições
    temperature_handler.clearSensorMap();

    // Vetor temporário para armazenar as novas configurações
    std::vector<SensorConfig> newConfigs;

    for (int i = 1; i <= NUM_SENSORS; i++) {
        
        String sensorIsEnabledKey = "sensor_" + String(i) + "_is_enabled";  // ex: sensor_1_is_enabled or sensor_2_is_enabled or sensor_3_is_enabled
        String sensorMinThresholdKey = "sensor_" + String(i) + "_min_threshold";
        String sensorMaxThresholdKey = "sensor_" + String(i) + "_max_threshold";

        // Lê as configurações do JSON
        bool is_enabled = configJson[sensorIsEnabledKey];
        float min_threshold = configJson[sensorMinThresholdKey];
        float max_threshold = configJson[sensorMaxThresholdKey];

        // Verifica se o sensor está habilitado
        if (is_enabled) {
            SensorConfig sensorConfig;
            sensorConfig.sensor_id = i;  // Define o ID do sensor como o índice
            sensorConfig.is_enabled = is_enabled;
            sensorConfig.min_threshold = min_threshold;
            sensorConfig.max_threshold = max_threshold;

            // Adiciona a configuração ao vetor
            newConfigs.push_back(sensorConfig);

            // Método para setar o sensor
            temperature_handler.addSensor(sensorConfig.sensor_id);
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