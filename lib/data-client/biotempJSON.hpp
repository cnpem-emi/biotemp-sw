#ifndef _INCLUDE_BIOTEMPJSON_HPP_
#define _INCLUDE_BIOTEMPJSON_HPP_

#include <Arduino.h>
#include <vector>
#include <ArduinoJson.h>
#include "temphandler.hpp"

/*****************************************************/
/*!
    @brief DataClient interface class. It is used to send the data from the sensor to other modules.
*/
/*****************************************************/
class BiotempJson {
    public:
        // Gets the temperature from the sensor
        String configPublisher();
        String mqttPusblisher();

    private:
        JsonDocument configDoc;
        JsonDocument mqttDoc;
};


#endif //_INCLUDE_BIOTEMPJSON_HPP_