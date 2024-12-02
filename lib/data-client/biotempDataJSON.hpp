#ifndef _INCLUDE_BIOTEMPJSON_HPP_
#define _INCLUDE_BIOTEMPJSON_HPP_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <string>
#include <vector>

#include "temphandler.hpp"
#include "configStruct.hpp"

#define NUM_SENSORS 3

typedef JsonDocument ConfigRequestDocument; 

/*****************************************************/
/*!
    @brief DataClient interface class. It is used to send the data from the sensor to other modules.
*/
/*****************************************************/
class BiotempDataJson {
    public:
        
        // Gets the temperature from the sensor
        String configPublisher();

        void handleConfigRequest(ConfigRequestDocument& configJson);

        String mqttGeneratePacket();

        void setSensorConfig(JsonObject& config);

        void setErrorCodes(const std::vector<uint8_t>& errors);

        String readBackJSON();

        BiotempDataJson(TempHandler& temp_handler): temperature_handler{temp_handler}{};

        std::vector<SensorConfig> sensorConfigs; // Stores the sensors data

    private:
        
        TempHandler& temperature_handler;
        JsonObject sensorConfig;              // Stores the sensor configuration  
        std::vector<uint8_t> errorCodes;      // Stores the error codes


};


#endif 