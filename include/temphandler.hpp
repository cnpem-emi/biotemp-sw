#ifndef _INCLUDE_TEMPHANDLER_HPP_
#define _INLCUDE_TEMPHANDLER_HPP_

#include <vector>
#include <string>
#include <cmath>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MAX31865.h>

class TempHandler {
    public:
        float temperature;
        std::string sensorID;

        float getTemperature();
};

const int CS_PIN = 10;
const float RREF = 430.0;

class SensorPT100 : public TempHandler {
    public:
        bool enabled = true;

        // Enable PT100 sensor
        void enablePT100();

        // Disable PT100 sensor
        void disablePT100();

        //Get the temperature from the PT100 sensor
        float getTemperature();
    
    private:
        Adafruit_MAX31865 max = Adafruit_MAX31865(CS_PIN);
};

const int ADC1_PIN = 35; // 3
const int ADC2_PIN = 2; // 2
const int BETA_COEFF = 3935;
const float T_0 = 298.15;
const int R_0 = 10000;

class SensorNTC : public TempHandler {
    public:
        int currentMode;
        bool enabled = true;

        // Enable NTC sensor
        void enableNTC();

        // Disable NTC sensor
        void disableNTC();
    
        /*************************************************************/
        /*!
            @brief Gets the temperature from NTC sensor.
            @param ntcID is the ADC id.
            @returns the temperature in degrees Celsius.
        */
        /*************************************************************/
        float getTemperature(int ntcID);

    private:
        /*************************************************************/
        /*!
            @brief Reads the ADC from a specified ID.
            @param ntcID The ADC id to read. Default: ADC1.
            @returns ADC value in bits.
        */
        /*************************************************************/
        float adcReader(int ntcID);
};

#endif  // _INCLUDE_TEMPHANDLER_HPP_
