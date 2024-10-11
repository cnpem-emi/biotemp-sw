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
    
    //@TODO change this to be able to sub and read config by the network
    configDoc["sensor_1_type"] = -1;
    configDoc["sensor_2_type"] = -1;
    configDoc["sensor_3_type"] = -1; 

    return configDoc.as<String>();
}

void BiotempDataJson::handleConfigRequest(ConfigRequestDocument& configJson){
    // Acessa os dados do JSON
  int sensor1Type = configJson["sensor_1_type"];
  int sensor2Type = configJson["sensor_2_type"];
  int sensor3Type = configJson["sensor_3_type"];

  //Lógica para alterar modos
  //Alterar layout de acordo com config recebida

  if (sensor1Type == 1) {
        temperature_handler.addNTCSensor(NTC_ID_1, NTC_PIN_1);
    } else if (sensor1Type == 2) {
        temperature_handler.addNTCSensor(NTC_ID_2, NTC_PIN_2);
    } else if (sensor1Type == 3) {
        temperature_handler.addPT100Sensor(PT100_ID);
    }

    if (sensor2Type == 1) {
        temperature_handler.addNTCSensor(NTC_ID_1, NTC_PIN_1);
    } else if (sensor2Type == 2) {
        temperature_handler.addNTCSensor(NTC_ID_2, NTC_PIN_2);
    } else if (sensor2Type == 3) {
       temperature_handler.addPT100Sensor(PT100_ID);
    }

    if (sensor3Type == 1) {
        temperature_handler.addNTCSensor(NTC_ID_1, NTC_PIN_1);
    } else if (sensor3Type == 2) {
        temperature_handler.addNTCSensor(NTC_ID_2, NTC_PIN_2);
    } else if (sensor3Type == 3) {
        temperature_handler.addPT100Sensor(PT100_ID);
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