#include "temphandler.hpp"
#include "sensorPT100.hpp"
#include "sensorNTC.hpp"
#include "biotempDataJSON.hpp"

void TempHandler::addPT100Sensor(const std::string& sensor_id) {
    available_sensors[sensor_id] = TempSensorPtr(new SensorPT100(sensor_id));
    available_sensors[sensor_id]->enableSensor();
    isAnySensorConfig = true;
}

void TempHandler::addNTCSensor(const std::string& sensor_id, const int sensor_pin){
    available_sensors[sensor_id] =  TempSensorPtr(new SensorNTC(sensor_pin));
    available_sensors[sensor_id]->enableSensor();
    isAnySensorConfig = true;
}

void TempHandler::clearSensorMap(){
    available_sensors.clear();
    isAnySensorConfig = false;
}

void TempHandler::setSensorLayout(SensorLayouts sensorLayout) {
    currentLayout = sensorLayout;
    clearSensorMap();
    
    switch(currentLayout) {
        case NTC1:
            addNTCSensor(NTC_ID_1, NTC_PIN_1);
            break; 
        case NTC2:
            addNTCSensor(NTC_ID_1, NTC_PIN_1);
            addNTCSensor(NTC_ID_2, NTC_PIN_2);
            break;
        case PT100:
            addPT100Sensor(PT100_ID);
            break;
    }
}

void TempHandler::addSensor(uint8_t sensor_id) {
    switch (sensor_id)
    {
    case 1:
        addNTCSensor(NTC_ID_1, NTC_PIN_1);
        break;
    case 2:
        addNTCSensor(NTC_ID_2, NTC_PIN_2);
        break;
    case 3:
        addPT100Sensor(PT100_ID);
        break;    
    default:
        break;
    }
}

float TempHandler::getTemperature(const std::string& sensor_id){
    return available_sensors[sensor_id]->getTemperature();
}

TempResults TempHandler::getAllTemperatures(){
    TempResults tempResults;
    for ( auto it = available_sensors.begin(); it != available_sensors.end(); ++it) {
        tempResults[it->first] = (it->second)->getTemperature();
    }
    return tempResults;
}

bool TempHandler::getSensorsHealth(){
    for ( auto it = available_sensors.begin(); it != available_sensors.end(); ++it) {
        if(!(it->second)->checkSensorHealth()){ return false;}
    }
    return true;
}

void TempHandler::setSensorConfigs(const std::vector<SensorConfig>& newConfigs) {
    sensorConfigs = newConfigs;
}

bool TempHandler::checkThreshold(bool is_enabled, int8_t sensorIDint, float setThresholdMin, float setThresholdMax) {
    float currentTemperature = 0;
    uint8_t triggered_count = 0;

    for (const auto& it : available_sensors) {

        currentTemperature = (it.second)->getTemperature();
        int8_t currentSensorID = (it.second)->getSensorIDint();

        //Serial.printf("Sensor ID atual: %d, Sensor ID que está sendo verificado: %d\n", currentSensorID, sensorIDint);

        if(currentSensorID == sensorIDint) {
            if (is_enabled) {
                if (currentTemperature < setThresholdMin || currentTemperature > setThresholdMax) {
                    isThresholdTrespassed = true;
                    triggered_count++;
                    
                    buzzer.buzzerON(); 
                    led.ledON();

                    return true;
                }
            }
        }
    }
    return false;
}

void TempHandler::buzzer_turn_off(){
    buzzer.buzzerOFF(); 
    led.ledOFF();
    isThresholdTrespassed = false;     
}


