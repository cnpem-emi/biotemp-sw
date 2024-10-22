#include "biotempDataJSON.hpp"

// Método para simular o formato que iremos receber as configurações do broker/interface
 String BiotempDataJson::configPublisher() {
    JsonDocument configDoc;
    configDoc.clear();

    JsonArray topicConfig = configDoc["topic_config"].to<JsonArray>();

    for(int i=0; i<3; i++) {
        JsonObject sensor = topicConfig.add<JsonObject>();
        sensor["sensor_id"] = -1; 
        sensor["sensor_type"] = -1;
        sensor["is_enabled"] = false;
        sensor["min_threshold"] = -1;
        sensor["max_threshold"] = -1;
    }
    return configDoc.as<String>(); 
}


void BiotempDataJson::handleConfigRequest(ConfigRequestDocument& configJson) {
    // garrante que após novas requisições de configuração, limpe as ultimas configs registradas
    temperature_handler.clearSensorMap();
   

    // Criar um vetor temporário para armazenar as novas configurações
    std::vector<SensorConfig> newConfigs;
    JsonArray topicConfig = configJson["topic_config"];
    newConfigs.clear();

    // Iterando sobre as configurações recebidas
    for (JsonObject sensorConfigJson : topicConfig) {
        int8_t sensor_type = sensorConfigJson["sensor_type"];
        int8_t sensor_id = sensorConfigJson["sensor_id"];
        float min_threshold = sensorConfigJson["min_threshold"];
        float max_threshold = sensorConfigJson["max_threshold"];

        // Log para cada sensor lido
        // Serial.printf("Sensor ID: %d, Tipo: %d, Min Threshold: %.2f, Max Threshold: %.2f\n",
        //               sensor_id, sensor_type, min_threshold, max_threshold);

        // Verifica se o sensor_type é válido
        if(sensor_type != -1) {
            SensorConfig sensorConfig;
            sensorConfig.sensor_id = sensor_id;
            sensorConfig.sensor_type = sensor_type;
            sensorConfig.is_enabled = sensorConfigJson["is_enabled"];
            sensorConfig.min_threshold = min_threshold;
            sensorConfig.max_threshold = max_threshold;
            
            // Adiciona a configuração ao vetor
            newConfigs.push_back(sensorConfig);

            // Método para escolher qual o tipo de sensor desejado
            temperature_handler.addSensor(sensor_type);
            // Método para avaliar os intervalos de temperatura para cada sensor independentes
            temperature_handler.checkThreshold(sensor_id, min_threshold, max_threshold);
        } 
    }
    // Atualize o tempHandler com as novas configurações
    temperature_handler.setSensorConfigs(newConfigs); 
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