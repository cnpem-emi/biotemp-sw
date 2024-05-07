#include "temphandler.hpp"

float TempHandler::getTemperature(std::string sensor_id){
    return available_sensors[sensor_id]->getTemperature();
}
