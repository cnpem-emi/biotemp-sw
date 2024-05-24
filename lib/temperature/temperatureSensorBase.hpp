#ifndef SENSOR_BASE_HPP
#define SENSOR_BASE_HPP

#include<string>

class TemperatureSensorBase {
public:
    // Constructor
    //TemperatureSensorBase() {}

    // Virtual destructor
    //virtual ~SensorBase() {}

    std::string sensor_id;
    bool is_enabled = false;

    virtual bool isSensorEnabled() = 0;
    virtual std::string getSensorID() = 0;

    // Virtual methods
    virtual void enableSensor() = 0;
    virtual void disableSensor() = 0;
    virtual float getTemperature() = 0;
};

#endif // SENSOR_BASE_HPP
