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

void TempHandler::addSensor(uint8_t sensor_id, float gain, float offset) {
    switch (sensor_id)
    {
    case 1:
        addNTCSensor(NTC_ID_1, NTC_PIN_1);
        available_sensors[NTC_ID_1]->setCalibration(gain, offset);
        break;
    case 2:
        addNTCSensor(NTC_ID_2, NTC_PIN_2);
        available_sensors[NTC_ID_2]->setCalibration(gain, offset);
        break;
    case 3:
        addPT100Sensor(PT100_ID);
        available_sensors[PT100_ID]->setCalibration(gain, offset);
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

std::vector<uint8_t> TempHandler::errorCodeGenerate(JsonObject& sensorConfig) {
    std::vector<uint8_t> error_codes(NUM_SENSORS, 0b000000); // Vetor para armazenar códigos de erro para cada sensor

    for (int i = 1; i <= NUM_SENSORS; i++) {
        // Gera as chaves para cada sensor
        String sensorIsEnabledKey = "sensor_" + String(i) + "_is_enabled";
        String sensorMinThresholdKey = "sensor_" + String(i) + "_min_threshold";
        String sensorMaxThresholdKey = "sensor_" + String(i) + "_max_threshold";
        String sensorGainKey = "sensor_" + String(i) + "_gain";
        String sensorOffSetKey = "sensor_" + String(i) + "_offSet";

        // Verifica se "sensor_x_is_enabled" é booleano
        if (!sensorConfig[sensorIsEnabledKey].is<bool>()) {
            error_codes[i - 1] |= 0b000001; 
        }

        // Verifica se "sensor_x_min_threshold" é um float e está no intervalo permitido que é -100°C
        float min_threshold = 0.;
        if (!sensorConfig[sensorMinThresholdKey].is<float>() || (min_threshold = sensorConfig[sensorMinThresholdKey], min_threshold < MIN_SENSOR_THRESHOLD)) {
            error_codes[i - 1] |= 0b000010; 
        } 

        // Verifica se "sensor_x_max_threshold" é um float e está no intervalo permitido que é 50°C
        float max_threshold = 0.;
        if (!sensorConfig[sensorMaxThresholdKey].is<float>() || (max_threshold = sensorConfig[sensorMaxThresholdKey], max_threshold > MAX_SENSOR_THRESHOLD )) {
            error_codes[i - 1] |= 0b000100; 
        }

        // Verifica se "sensor_x_gain_error" é um float
        if (!sensorConfig[sensorGainKey].is<float>()) {
            error_codes[i - 1] |= 0b001000; 
        }

        // Verifica se "sensor_x_gain_error" 
        if (!sensorConfig[sensorOffSetKey].is<int>() && !sensorConfig[sensorOffSetKey].is<float>() && !sensorConfig[sensorOffSetKey].isNull()) {
            error_codes[i - 1] |= 0b010000;
        }


    }

    return error_codes;
}