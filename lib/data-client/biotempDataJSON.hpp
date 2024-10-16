#ifndef _INCLUDE_BIOTEMPJSON_HPP_
#define _INCLUDE_BIOTEMPJSON_HPP_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <string>
#include <vector>

#include "temphandler.hpp"
#include "modes-and-layouts.hpp"
#include "configStruct.hpp"

typedef JsonDocument ConfigRequestDocument; 

// extern DynamicJsonDocument configDoc;

/*****************************************************/
/*!
    @brief DataClient interface class. It is used to send the data from the sensor to other modules.
*/
/*****************************************************/
class BiotempDataJson {
    public:
        // Gets the temperature from the sensor
        String configPublisher();
        String mqttGeneratePacket();

        BiotempDataJson(TempHandler& temp_handler): temperature_handler{temp_handler}{}

        void handleConfigRequest(ConfigRequestDocument& configJson);

        

    private:
        std::map<OperationModes, std::string> MODES_DISPLAY_STR = {{ULTRAFREEZER_MODE, "UltraFreezer"},
                                                                   {FREEZER_MODE, "Freezer"},
                                                                   {REFRIGERATOR_MODE, "Refrigerator"},
                                                                   {AMBIENT_MODE, "Ambient"}};

        std::map<SensorLayouts, std::string> SENSOR_LAYOUTS_STR = {{NONE, "None"},
                                                                   {NTC1, "NTC1"},
                                                                   {NTC2, "NTC2"},
                                                                   {PT100, "PT100"}};

        
        TempHandler& temperature_handler;

        //Vector to store sensor configuration
        std::vector<SensorConfig> sensorConfigs;

        
};


#endif 