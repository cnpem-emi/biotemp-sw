#ifndef SENSOR_PT100_HPP
#define SENSOR_PT100_HPP

#include <string>
#include <cmath>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MAX31865.h>

#include "temperatureSensorBase.hpp"

#define CS_PIN 10 // PT100 SPI chip selector pin
#define DI_PIN 11
#define DO_PIN 9
#define CLK_PIN 7

#define RREF 430.0 // PT100 reference 25°C resistance
#define RNOMINAL 100.0

#define SENSOR_PIN 3
#define SENSOR_ID_PT100 3

/*****************************************************/
/*!
    @brief PT100 sensor interface class. The sensor initializes disabled.
*/
/*****************************************************/
class SensorPT100 : public TemperatureSensorBase {
public:
    SensorPT100(const std::string& id);

    bool isSensorEnabled() override;
    std::string getSensorID() override;
    void enableSensor() override;
    void disableSensor() override;
    float getTemperature() override;
    bool checkSensorHealth() override;

    int8_t getSensorIDint() override;

    void setCalibration(float gain, float offset) override;


private:
    Adafruit_MAX31865 max_module = Adafruit_MAX31865(CS_PIN, DI_PIN, DO_PIN, CLK_PIN);
    
    int8_t sensorIDint;

    float gain = 1.;
    float offset = 0.;
};

#endif
