#ifndef TEMPHANDLER_HPP 
#define TEMPHANDLER_HPP 

#include <map>
#include <string>

#include "temperatureSensorBase.hpp"
#include "sensorPT100.hpp"
#include "sensorNTC.hpp"

//Change this if want to add more sensors
#define PT100_ID "PT100"
#define NTC_PIN 1
#define NTC_ID "NTC1"

class TempHandler {
    public:
         std::map<std::string, TemperatureSensorBase*> available_sensors = 
         {{PT100_ID, &SensorPT100(PT100_ID)},
          {NTC_ID  , &SensorNTC(NTC_PIN)}};

        float getTemperature(std::string sensor_id);
};

#endif  //TEMPHANDLER_HPP_
