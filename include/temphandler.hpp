#ifndef _INCLUDE_TEMPHANDLER_HPP_
#define _INLCUDE_TEMPHANDLER_HPP_

#include <string>
#include <cmath>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MAX31865.h>

/*****************************************************/
/*!
    @brief PT100 and NTC sensors base class.
*/
/*****************************************************/
class TempHandler {
    public:
        float temperature;
        std::string sensorID;

        float getTemperature();
};

#define CS_PIN 10 // PT100 SPI chip selector pin
#define RREF 430.0 // PT100 reference 25°C resistance

/*****************************************************/
/*!
    @brief PT100 sensor interface class. The sensor initializes disabled.
*/
/*****************************************************/
class SensorPT100 : public TempHandler {
    public:
        std::string sensorID = "PT100"; 
        bool enabled = false;

        // Enable PT100 sensor
        void enablePT100();

        // Disable PT100 sensor
        void disablePT100();

        //Get the temperature from the PT100 sensor
        float getTemperature();
    
    private:
        Adafruit_MAX31865 max = Adafruit_MAX31865(CS_PIN);
};

#define ADC1_PIN 35 // Default ESP32 S2 pin: GPIO3
#define ADC2_PIN 34 // Default ESP32 S2 pin: GPIO2
#define BETA_COEFF 3935 // NTC beta coefficient at 25/50
#define T_0 298.15 // NTC reference temperature: 25°C 
#define R_0 10000 // NTC reference resistance: R(T_0)

/*****************************************************/
/*!
    @brief NTC sensor interface class. The sensor initializes disabled. 
    It must be specified the sensor ID (1 or 2).
*/
/*****************************************************/
class SensorNTC : public TempHandler {
    public:
        int ntcID;
        bool enabled = false;

        // Enable NTC sensor
        void enableNTC();

        // Disable NTC sensor
        void disableNTC();
    
        /*************************************************************/
        /*!
            @brief Gets the temperature from NTC sensor.
            @returns the temperature in degrees Celsius.
        */
        /*************************************************************/
        float getTemperature();

        /*************************************************************/
        /*!
            @brief NTC sensor class constructor.
            @param ntcID the ID of the sensor, selects the correct ADC pin.
        */
        /*************************************************************/
        SensorNTC(int ntcID);

    private:
        /*************************************************************/
        /*!
            @brief Reads the ADC from a specified ID.
            @returns ADC value in millivolts.
        */
        /*************************************************************/
        float adcReader();
};

#endif  // _INCLUDE_TEMPHANDLER_HPP_
