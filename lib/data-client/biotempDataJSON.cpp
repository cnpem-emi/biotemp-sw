#include "biotempDataJSON.hpp"

/**
 * sets values in a config JSON and returns it as a String.
 * 
 * @return Returns a JSON string representation of the configuration options.
 */
String BiotempDataJson::configPublisher() {
    JsonDocument configDoc;
    configDoc.clear();
    configDoc["biotemp_mode"] = MODES_DISPLAY_STR[temperature_handler.operation_mode];
    configDoc["sensor_layout"] = SENSOR_LAYOUTS_STR[temperature_handler.currentLayout];
    
    //@TODO change this to be able to sub and read config by the network
    configDoc["sensor_1_mode"] = -1;
    configDoc["sensor_2_mode"] = -1;
    configDoc["sensor_3_mode"] = -1; 

    return configDoc.as<String>();
}

/**
 * Generates a JSON packet containing temperature data for MQTT communication.
 * 
 * @return Returns a JSON string representation of the temperature data.
 */
String BiotempDataJson::mqttGeneratePacket() {
    JsonDocument mqttDoc;
    TempResults tempResults = temperature_handler.getAllTemperatures();
    mqttDoc.clear();

    // Starts the json with the default variables
    for(int i = 1; i <= 3; ++i){
        std::string sensor_base = std::string{"sensor_"} + std::to_string(i);
        mqttDoc[sensor_base + "_mode"] = -1;
        mqttDoc[sensor_base + "_temp"] = 0;
    }
    
    // Please generalize this
    std::map<std::string, std::string> SensorName2Id = {{"NTC1", "sensor_1"},
                                                        {"NTC2", "sensor_2"},
                                                        {"PT100", "sensor_3"}};

    for ( auto it = tempResults.begin(); it != tempResults.end(); ++it) {
        std::string sensor_base = SensorName2Id[it->first];
        mqttDoc[sensor_base + "_mode"] = temperature_handler.operation_mode;
        mqttDoc[sensor_base + "_temp"] = String((it->second));
    }

   return mqttDoc.as<String>();
}