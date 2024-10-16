#include "biotempDataJSON.hpp"

//this function is just to simulate the publisher in the broker, delete it later pls
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


void BiotempDataJson::handleConfigRequest(ConfigRequestDocument& configJson){
    sensorConfigs.clear();
    JsonArray topicConfig = configJson["topic_config"];

    for (JsonObject sensorConfigJson : topicConfig) {

        uint8_t sensor_type = sensorConfigJson["sensor_type"];

        if(sensor_type != -1) {
            SensorConfig sensorConfig;
            sensorConfig.sensor_id = sensorConfigJson["sensor_id"];
            sensorConfig.sensor_type = sensor_type;
            sensorConfig.is_enabled = sensorConfigJson["is_enabled"];
            sensorConfig.min_threshold = sensorConfigJson["min_threshold"];
            sensorConfig.max_threshold = sensorConfigJson["max_threshold"];

            // Adiciona a configuração do sensor ao vetor
            sensorConfigs.push_back(sensorConfig);

            temperature_handler.addSensor(sensor_type);
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