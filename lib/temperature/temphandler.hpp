#ifndef TEMPHANDLER_HPP 
#define TEMPHANDLER_HPP 

#include <map>
#include <string>
#include <memory>

#include "temperatureSensorBase.hpp"

//Change this if want to add more sensors
#define PT100_ID "PT100"
#define NTC_PIN 1
#define NTC_ID "NTC1"

class TempHandler {
    public:
        TempHandler();
        
        // @TODO do this with enums or something
        std::map<std::string, std::unique_ptr<TemperatureSensorBase>> available_sensors;

        float getTemperature(const std::string& sensor_id);
};

#endif  //TEMPHANDLER_HPP_
