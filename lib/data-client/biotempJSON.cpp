#include "biotempJSON.hpp"

String BiotempJson::configPublisher() {
    configDoc["sensor_1_mode"] = "1";
    configDoc["sensor_2_mode"] = "2";
    configDoc["sensor_3_mode"] = "3";

    return configDoc.as<String>();
}

/**
 * Generates a JSON packet containing temperature data for MQTT communication.
 * 
 * @return Returns a JSON string representation of the temperature data.
 */
String BiotempJson::mqttGeneratePacket() {
    TempResults tempResults = temperature_handler.getAllTemperatures();
    
    for ( auto it = tempResults.begin(); it != tempResults.end(); ++it) {
        mqttDoc[it->first] = String((it->second));
    }

   return mqttDoc.as<String>();
}