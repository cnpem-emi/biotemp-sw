#ifndef TEMPHANDLER_HPP 
#define TEMPHANDLER_HPP 

#include <map>
#include <string>
#include <memory>

#include "temperatureSensorBase.hpp"
#include "modes-and-layouts.hpp"
#include "buzzer.hpp"
#include "LED.hpp"

//Change this if want to add more sensors
#define PT100_ID "PT100"
#define NTC_PIN_1 1
#define NTC_PIN_2 2
#define NTC_ID_1 "NTC1"
#define NTC_ID_2 "NTC2"

typedef std::map<std::string, std::shared_ptr<TemperatureSensorBase>> SensorMap;
typedef std::map<std::string, float> TempResults; 

class TempHandler {
    public:

        TempHandler(){buzzer.buzzerConfig(); led.ledConfig();};

        void addPT100Sensor(const std::string& sensor_id);
        void addNTCSensor(const std::string& sensor_id, const int sensor_pin); 
        
        SensorMap available_sensors;

        float getTemperature(const std::string& sensor_id);
        TempResults getAllTemperatures();

        bool isThresholdTrespassed = false;

        void setOperationMode(OperationModes mode) {operation_mode = mode; threshold= mode2Threshold[mode];};
        void setSensorLayout(SensorLayouts SensorLayout);

        std::map<OperationModes, float> mode2Threshold = {{ FREEZER_MODE,    -20.0},
                                                          { ULTRAFREEZER_MODE, -80.0},
                                                          { AMBIENT_MODE,       25.0},
                                                          { REFRIGERATOR_MODE, 5.0}}; 

        float threshold = mode2Threshold[AMBIENT_MODE];  

        void checkThreshold();

        bool isAnySensorConfig = false;
        Buzzer buzzer; 

        OperationModes operation_mode = AMBIENT_MODE;
        SensorLayouts currentLayout = NONE; 

    private: 
        void clearSensorMap();
        LED led;

};

#endif  //TEMPHANDLER_HPP_
