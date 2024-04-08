#ifndef _INCLUDE_TEMPHANDLER_HPP_
#define _INLCUDE_TEMPHANDLER_HPP_

#include <vector>
#include <string>
#include <Arduino.h>
#include <Adafruit_MAX31865.h>

class TempHandler {
    public:
        float temperature;
        std::string sensorID;

        float getTemperature();
};

class SensorPT100 : public TempHandler {
    public:
        bool enabled = true;

        // Enable PT100 sensor
        void enablePT100();

        // Disable PT100 sensor
        void disablePT100();

        //Get the temperature from the PT100 sensor
        float getTemperature();
};

class SensorNTC : public TempHandler {
    public:
        int currentMode;
        bool enabled = true;

        // Enable NTC sensor
        void enableNTC();

        // Disable NTC sensor
        void disableNTC();

        // Linearize the ADC input
        void lienarizeADC();
    
        // Get the temperature from the NTC sensor
        float getTemperature();

    private:
        /*************************************************************/
        /*!
            @brief Reads the ADC from a specified ID.
            @param ntcID The ADC id to read. Default: ADC1.
            @returns ADC value in bits.
        */
        /*************************************************************/
        int adcReader(int ntcID);

};

#endif  // _INCLUDE_TEMPHANDLER_HPP_
