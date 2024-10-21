#ifndef SENSOR_BASE_HPP
#define SENSOR_BASE_HPP

#define NOT_HEALTHY_THRESHOLD 1

#include<string>

class TemperatureSensorBase {
public:
    std::string sensor_id;
    bool is_enabled = false;

    virtual bool isSensorEnabled() = 0;
    virtual std::string getSensorID() = 0;

    // Virtual methods
    virtual void enableSensor() = 0;
    virtual void disableSensor() = 0;
    virtual float getTemperature() = 0;
    virtual bool checkSensorHealth() = 0;

    virtual uint8_t getSensorIDint() = 0;
};

#endif // SENSOR_BASE_HPP
