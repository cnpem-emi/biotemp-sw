#ifndef TEMPHANDLER_HPP 
#define TEMPHANDLER_HPP 

#include <map>
#include <string>
#include <memory>

#include "temperatureSensorBase.hpp"

//Change this if want to add more sensors
#define PT100_ID "PT100"
#define NTC_PIN_1 1
#define NTC_PIN_2 2
#define NTC_ID_1 "NTC1"
#define NTC_ID_2 "NTC2"

enum OperationModes {Freezer, UltraFreezer,  Refrigerator, Ambient}; 

typedef std::map<std::string, std::shared_ptr<TemperatureSensorBase>> SensorMap;

class TempHandler {
    public:
        void addPT100Sensor(const std::string& sensor_id);
        void addNTCSensor(const std::string& sensor_id, const int sensor_pin); 
        
        // @TODO do this with enums or something
        SensorMap available_sensors;

        float getTemperature(const std::string& sensor_id);

        bool isThresholdTrespassed = false;

        void setOperationMode(OperationModes mode) {operation_mode = mode; threshold= mode2Threshold[mode];};

        std::map<OperationModes, float> mode2Threshold = {{ Freezer,    -20.0},
                                                          { UltraFreezer, -80},
                                                          { Ambient,       25},
                                                          { Refrigerator, 5.0}}; 

        float threshold = mode2Threshold[operation_mode];  

        void checkThreshold();

      

    private: 
        bool isAnySensorConfig = false;
        OperationModes operation_mode = Ambient;
};

#endif  //TEMPHANDLER_HPP_
