#include "biotempDataJSON.hpp"

/**
 * sets values in a config JSON and returns it as a String.
 * 
 * @return Returns a JSON string representation of the configuration options.
 */
String BiotempDataJson::configPublisher() {
    configDoc.clear();
    configDoc["biotemp_mode"] = MODES_DISPLAY_STR[temperature_handler.operation_mode];
    configDoc["sensor_layout"] = SENSOR_LAYOUTS_STR[temperature_handler.currentLayout];
    return configDoc.as<String>();
}

/**
 * Generates a JSON packet containing temperature data for MQTT communication.
 * 
 * @return Returns a JSON string representation of the temperature data.
 */
String BiotempDataJson::mqttGeneratePacket() {
    TempResults tempResults = temperature_handler.getAllTemperatures();
    mqttDoc.clear();
    
    for ( auto it = tempResults.begin(); it != tempResults.end(); ++it) {
        mqttDoc[it->first + "_mode"] = temperature_handler.operation_mode;
        mqttDoc[std::string{"temp_"} + it->first] = String((it->second));
    }

   return mqttDoc.as<String>();
}