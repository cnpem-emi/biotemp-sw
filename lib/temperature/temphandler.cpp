#include "temphandler.hpp"
#include "sensorPT100.hpp"
#include "sensorNTC.hpp"

using TempSensorPtr = std::unique_ptr<TemperatureSensorBase>;

TempHandler::TempHandler(){
    available_sensors[PT100_ID] = TempSensorPtr(new SensorPT100(PT100_ID));
    available_sensors[NTC_ID] =  TempSensorPtr(new SensorNTC(NTC_PIN));
}


float TempHandler::getTemperature(const std::string& sensor_id){
    return available_sensors[sensor_id]->getTemperature();
}
