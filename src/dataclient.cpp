#include <dataclient.hpp>

void DataClient::subscribe(SensorPT100 *s) {
    s->enabled = true;
    registered[0] = true;
}

void DataClient::subscribe(SensorNTC *s) {
    s->enabled = true;
    registered[s->ntcID] = true;
}

void DataClient::unsubscribe(SensorPT100 *s) {
    s->enabled = false;
    registered[0] = false;
}

void DataClient::unsubscribe(SensorNTC *s) {
    s->enabled = false;
    registered[s->ntcID] = false;
}

void DataClient::getData() {
    
}
