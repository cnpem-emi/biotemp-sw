#ifndef TEMPHANDLER_HPP 
#define TEMPHANDLER_HPP 

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <ArduinoJson.h>

#include "temperatureSensorBase.hpp"
#include "buzzer.hpp"
#include "LED.hpp"
#include "configStruct.hpp"

//Change this if want to add more sensors
#define PT100_ID "PT100"
#define NTC_PIN_1 1
#define NTC_PIN_2 2
#define NTC_ID_1 "NTC1"
#define NTC_ID_2 "NTC2"

#define MAX_SENSOR_THRESHOLD 50
#define MIN_SENSOR_THRESHOLD -100

typedef std::map<std::string, std::shared_ptr<TemperatureSensorBase>> SensorMap;

typedef std::shared_ptr<TemperatureSensorBase> TempSensorPtr;
typedef std::map<std::string, float> TempResults;

class TempHandler {
    public:
        
        float temperature;

        TempHandler(){buzzer.buzzerConfig(); led.ledConfig();};

        /**
         * Adds a PT100 sensor to the available sensors map and enables the sensor.
         * 
         * @param sensor_id The `sensor_id` parameter is a `string` type that represents the unique
         * identifier of the PT100 sensor being added to the `TempHandler` class.
         */
        void addPT100Sensor(const std::string& sensor_id);

        /**
         * Adds a new NTC sensor to the `available_sensors` map with the provided
         * sensor ID and pin, enabling the sensor and setting `isAnySensorConfig` to true.
         * 
         * @param sensor_id The `sensor_id` parameter is a unique identifier for the NTC sensor being added.
         *  It is used to associate the sensor with a specific ID in the available sensors map.
         * 
         * @param sensor_pin The `sensor_pin` parameter represents the pin number to which the NTC sensor is
         * connected. This pin is used to read the temperature data from the NTC sensor.
         */
        void addNTCSensor(const std::string& sensor_id, const int sensor_pin); 
        
        // Map to Temperature Sensor instances
        SensorMap available_sensors;

        /**
         * The function `getTemperature` returns the temperature value from the sensor specified by the given
         * sensor ID.
         * 
         * @param sensor_id The `sensor_id` parameter is a `string` that represents the unique
         * identifier of the sensor for which you want to retrieve the temperature reading.
         * 
         * @return The `getTemperature` function is returning the temperature value from the sensor with the
         * specified `sensor_id`.
         */
        float getTemperature(const std::string& sensor_id);

        TempResults getAllTemperatures();

        bool isThresholdTrespassed = false;

        void buzzer_turn_off();
        
        bool checkThreshold(bool is_enabled, int8_t sensorIDint, float setThresholdMin, float setThresholdMax);
        
        const std::vector<SensorConfig>& getSensorConfigs() const {
        return sensorConfigs;
        }

        // Flag that represents that we have any sensor available
        bool isAnySensorConfig = false;
        Buzzer buzzer; 
        

        /**
         * iterates through available sensors and returns false if any sensor's
         * health check fails, otherwise true.
         * 
         * @return It returns `true` if all the sensors in the available sensors map are healthy
         *  (i.e., `checkSensorHealth` returns true for each sensor), otherwise returns false. 
         */
        bool getSensorsHealth();
        void addSensor(uint8_t sensorID, float gain, float offset);
        void setSensorConfigs(const std::vector<SensorConfig>& newConfigs);
        void clearSensorMap();
        
        //uint8_t errorCodeGenerate(JsonObject& sensorConfig);

        std::vector<uint8_t> errorCodeGenerate(JsonObject& sensorConfig);
        
    private: 
        LED led;
        std::vector<SensorConfig> sensorConfigs;

};
       

#endif  //TEMPHANDLER_HPP_
