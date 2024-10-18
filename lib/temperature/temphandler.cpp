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

void TempHandler::addSensor(uint8_t sensor_type) {
    switch (sensor_type)
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


// void TempHandler::checkThreshold(){
//     uint8_t triggered_count = 0;

    
//     for ( auto it = available_sensors.begin(); it != available_sensors.end(); ++it) {

//         if((it->second)->getTemperature() > threshold){
//             isThresholdTrespassed = true;
            
//             triggered_count++;

//             buzzer.buzzerON();
//             led.ledON();
//         }
//     }

//     if(triggered_count == 0) {
//         buzzer.buzzerOFF();
//         led.ledOFF();
//         isThresholdTrespassed = false;
//     }
// }


void TempHandler::checkThreshold(uint8_t sensor_id, float setThresholdMin, float setThresholdMax){
    uint8_t triggered_count = 0;
    float currentTemperature;

    // Converter sensor_id de uint8_t para string, supondo que seja um número
    std::string sensorIdStr = std::to_string(sensor_id);

    Serial.printf("Verificando sensor_id: %d\n", sensor_id);
    Serial.printf("Limites - Min: %.2f, Max: %.2f\n", setThresholdMin, setThresholdMax);

     

     // Itera sobre os sensores disponíveis
    for (const auto& it : available_sensors) {
        // Acessa a temperatura do sensor atual
        currentTemperature = (it.second)->getTemperature(); // Aqui, it.second é um shared_ptr para o sensor
        Serial.printf("Temperatura atual do sensor %s: %.2f\n", it.first.c_str(), currentTemperature);

        // Adicionando logs para debug
        Serial.printf("Comparando it.first: %s com sensor_id: %d\n", it.first.c_str(), sensor_id);

        // Compara o sensor_id atual (como string) com o sensorIdStr (também como string)
        if (it.first == std::to_string(sensor_id)) {
            if (currentTemperature < setThresholdMin || currentTemperature > setThresholdMax) {
                isThresholdTrespassed = true;
                Serial.println("OU TO AQUI DENTRO");
                triggered_count++;

                buzzer.buzzerON();
                led.ledON();
            } else {
                Serial.println("Temperatura dentro dos limites.");
            }
        }
    }


    // Se nenhum limite foi excedido, desliga buzzer e LED
    if (triggered_count == 0) {
        buzzer.buzzerOFF();
        led.ledOFF();
        isThresholdTrespassed = false;
    }
}
