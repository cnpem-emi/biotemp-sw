#include "biotempJSON.hpp"

String BiotempJson::configPublisher() {
    configDoc["sensor_1_mode"] = "1";
    configDoc["sensor_2_mode"] = "2";
    configDoc["sensor_3_mode"] = "3";

    return configDoc.as<String>();
}

String BiotempJson::mqttGeneratePacket() {
    //@TODO add correct sensor mode before temperature module integration 
    mqttDoc["sensor_1_mode"] = "1";
    mqttDoc["sensor_2_mode"] = "2";
    mqttDoc["sensor_3_mode"] = "3";
    
    mqttDoc["temp_1"] = temperature_handler.getTemperature(NTC_ID_1);
    mqttDoc["temp_2"] = temperature_handler.getTemperature(NTC_ID_2);
    mqttDoc["temp_3"] = temperature_handler.getTemperature(PT100_ID);

   return mqttDoc.as<String>();
}