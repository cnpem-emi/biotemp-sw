#ifndef _INCLUDE_BIOTEMPJSON_HPP_
#define _INCLUDE_BIOTEMPJSON_HPP_

#include <Arduino.h>
#include <vector>
#include <ArduinoJson.h>

#include "temphandler.hpp"
#include "modes-and-layouts.hpp"

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

    private:
        std::map<OperationModes, std::string> MODES_DISPLAY_STR = {{ULTRAFREEZER_MODE, "UltraFreezer"},
                                                                   {FREEZER_MODE, "Freezer"},
                                                                   {REFRIGERATOR_MODE, "Refrigerator"},
                                                                   {AMBIENT_MODE, "Ambient"}};

        std::map<SensorLayouts, std::string> SENSOR_LAYOUTS_STR = {{NONE, "None"},
                                                                   {NTC1, "NTC1"},
                                                                   {NTC2, "NTC2"},
                                                                   {PT100, "PT100"}};

        JsonDocument configDoc;
        JsonDocument mqttDoc;
        TempHandler& temperature_handler;
};


#endif 