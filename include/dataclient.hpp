#ifndef _INCLUDE_DATACLIENT_HPP_
#define _INCLUDE_DATACLIENT_HPP_

#include <Arduino.h>
#include <vector>
#include <temphandler.hpp>

/*****************************************************/
/*!
    @brief Sensor struct that contains the data to be sent.
    It contains the sensor parameters that will be formated into JSON.
*/
/*****************************************************/
struct sensorData {
    bool enabled; // Sensor status. If disabled, it will not be read.
    std::string model; // Sensor model name (PT100 or NTC).
    float temperature; // Sensor temperature value.
};

/*****************************************************/
/*!
    @brief DataClient interface class. It is used to send the data from the sensor to other modules.
*/
/*****************************************************/
class DataClient {
    public:
        // Activate the sensor and create a sctruct containing its parameters
        void subscribe(SensorPT100 s);
        // Activate the sensor and create a sctruct containing its parameters
        void subscribe(SensorNTC s);

        // Deactivate the sensor
        void unsubscribe(SensorPT100 s);
        // Deactivate the sensor
        void unsubscribe(SensorNTC s);

        // Gets the temperature from the sensor
        void getData(SensorPT100 s);
        // Gets the temperature from the sensor
        void getData(SensorNTC s);

    private:
        std::vector<sensorData> sensorList; // The list that contains all the sensor structs.
};

#endif  // _INCLUDE_DATACLIENT_HPP_
