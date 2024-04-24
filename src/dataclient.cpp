#include <dataclient.hpp>

void DataClient::subscribe(SensorPT100 s) {
    s.enabled = true;

    sensorData aux;
    aux.enabled = s.enabled;
    aux.model = s.pt100ID;
    aux.temperature = s.getTemperature();

    sensorList.emplace_back(aux);
}

void DataClient::subscribe(SensorNTC s) {
    s.enabled = true;

    sensorData aux;
    aux.enabled = s.enabled;
    aux.model = s.sensorID;
    aux.temperature = s.getTemperature();

    sensorList.emplace_back(aux);
}

void DataClient::unsubscribe(SensorPT100 s) {
    s.enabled = false;
}

void DataClient::unsubscribe(SensorNTC s) {
    s.enabled = false;
}

void DataClient::getData(SensorPT100 s) {
    for(int i=0; i<sensorList.size(); i++) {
        if(sensorList[i].model == s.pt100ID) {
            sensorList[i].temperature = s.getTemperature();
        }
    }
}

void DataClient::getData(SensorNTC s) {
    for(int i=0; i<sensorList.size(); i++) {
        if(sensorList[i].model == s.sensorID) {
            sensorList[i].temperature = s.getTemperature();
        }
    }
}
