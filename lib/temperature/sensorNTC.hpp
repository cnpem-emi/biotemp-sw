#ifndef SENSOR_NTC_HPP
#define SENSOR_NTC_HPP

#include "temperatureSensorBase.hpp"
#include "debug-config.hpp"
#include <Arduino.h>

#define BETA_COEFF 3935 // NTC beta coefficient at 25/50
#define T_0 298.15 // NTC reference temperature: 25°C 
#define R_0 10000 // NTC reference resistance: R(T_0)
#define R_DIV 56000 // Voltage divider resistor



#define NOT_HEALTHY_THRESHOLD 1500 // based on ESP32 ADC

#define NTCID1 "NTC1"
#define NTCID2 "NTC2"

enum ADCPins {ADC1_PIN=3, // Default ESP32 WROOM pin: 35 
              ADC2_PIN=2  // Default ESP32 WROOM pin: 34
              };

/*****************************************************/
/*!
    @brief NTC sensor interface class. The sensor initializes disabled.
*/
/*****************************************************/
class SensorNTC : public TemperatureSensorBase {
    public:
        /*************************************************************/
        /*!
            @brief NTC sensor class constructor.
            @param ntc_id the ID of the sensor, selects the correct ADC pin.
        */
        /*************************************************************/
        SensorNTC(int ntc_id);

        bool isSensorEnabled() override;
        std::string getSensorID() override;
        void enableSensor() override;
        void disableSensor() override;
        float getTemperature() override;
        bool checkSensorHealth() override;

    private:
        /*************************************************************/
        /*!
            @brief Reads the ADC from a specified ID.
            @returns ADC value in millivolts.
        */
        /*************************************************************/
        float readADCPin();
        int sensor_pin;
};
#endif
