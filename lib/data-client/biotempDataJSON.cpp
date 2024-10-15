#include "biotempDataJSON.hpp"

/**
 * sets values in a config JSON and returns it as a String.
 * 
 * @return Returns a JSON string representation of the configuration options.
 */
// String BiotempDataJson::configPublisher() {
//     JsonDocument configDoc;
//     configDoc.clear();
//     //configDoc["biotemp_mode"] = MODES_DISPLAY_STR[temperature_handler.operation_mode];
//     //configDoc["sensor_layout"] = SENSOR_LAYOUTS_STR[temperature_handler.currentLayout];
    
//     //@TODO change this to be able to sub and read config by the network
//     configDoc["sensor_1_mode"] = -1;
//     configDoc["sensor_2_mode"] = -1;
//     configDoc["sensor_3_mode"] = -1; 

//     return configDoc.as<String>();
// }

/**
 * Generates a JSON packet containing temperature data for MQTT communication.
 * 
 * @return Returns a JSON string representation of the temperature data.
 */
// String BiotempDataJson::mqttGeneratePacket() {
//     JsonDocument mqttDoc;
//     TempResults tempResults = temperature_handler.getAllTemperatures();
//     mqttDoc.clear();

//     // Starts the json with the default variables
//     for(int i = 1; i <= 3; ++i){
//         std::string sensor_base = std::string{"sensor_"} + std::to_string(i);
//         mqttDoc[sensor_base + "_mode"] = -1;
//         mqttDoc[std::string{"temp_"} + std::to_string(i)] = 0;
//     }
    
//     // Please generalize this
//     std::map<std::string, std::string> SensorName2Id = {{"NTC1", "1"},
//                                                         {"NTC2", "2"},
//                                                         {"PT100", "3"}};

//     for ( auto it = tempResults.begin(); it != tempResults.end(); ++it) {
//         std::string sensorId = SensorName2Id[it->first];
//         mqttDoc[std::string{"sensor_"} + sensorId + "_mode"] = temperature_handler.operation_mode;
//         mqttDoc[std::string{"temp_"} + sensorId ] = String((it->second));
//     }

//    return mqttDoc.as<String>();
// }

//----------------------publishing test 09/10--------------------------//

 String BiotempDataJson::configPublisher() {
    JsonDocument configDoc;
    configDoc.clear();

    JsonArray sensorsConfigs = configDoc["topic_config"].to<JsonArray>();
    
    for(SensorConfig& SensorConfig : sensorsConfigValues) {
        JsonObject sensor = sensorsConfigs.add<JsonObject>();
        sensor["sensor_id"] = -1; 
        sensor["sensor_type"] = -1;
        sensor["is_enabled"] = false;
        sensor["min_threshold"] = -1;
        sensor["max_threshold"] = -1;
    }

    return configDoc.as<String>(); // Retorna o JSON como uma String
}


void BiotempDataJson::handleConfigRequest(ConfigRequestDocument& configJson){
    
    JsonArray configArray = configJson["topic_config"].to<JsonArray>();
    int idx = 0; 
    for(JsonVariant configJsonObj : configArray) {
        SensorConfig config; 
        config.sensor_id = configJsonObj["sensor_id"];
        config.sensor_type = configJsonObj["sensor_type"];
        config.is_enabled = configJsonObj["is_enabled"];
        config.min_threshold = configJsonObj["min_threshold"];
        config.max_threshold = configJsonObj["max_threshold"];

        sensorsConfigValues[idx] = config;
        idx++;
        addSensor(config.sensor_type);
    }
    //SensorConfig config;
    // addSensor(config.sensor_type);

}


void BiotempDataJson::addSensor(uint8_t sensorType) {
    switch (sensorType)
    {
    case 1:
        temperature_handler.addNTCSensor(NTC_ID_1, NTC_PIN_1);
        break;
    case 2:
        temperature_handler.addNTCSensor(NTC_ID_2, NTC_PIN_2);
        break;
    case 3:
        temperature_handler.addPT100Sensor(PT100_ID);
        break;    
    default:
        break;
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