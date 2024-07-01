#include "temphandler.hpp"
#include "sensorPT100.hpp"
#include "sensorNTC.hpp"

using TempSensorPtr = std::unique_ptr<TemperatureSensorBase>;

TempHandler::TempHandler(){
    // Don't do Dynamic allocation like this in small microcontrollers
    available_sensors[PT100_ID] = TempSensorPtr(new SensorPT100(PT100_ID));
    available_sensors[NTC_ID_1] =  TempSensorPtr(new SensorNTC(NTC_PIN_1));
    available_sensors[NTC_ID_2] =  TempSensorPtr(new SensorNTC(NTC_PIN_2));
}


float TempHandler::getTemperature(const std::string& sensor_id){
    return available_sensors[sensor_id]->getTemperature();
}
