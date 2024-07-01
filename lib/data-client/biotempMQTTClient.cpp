#include <biotempMQTTClient.hpp>

BiotempJson json;

void BioTempMQTTClient::mqttConfig() {
    mqtt.config(WIFI_SSID, WIFI_PASSWORD);
}

void BioTempMQTTClient::publish(const char* topic, String message) {
    mqtt.publishMessage(topic, message, false);
}

void BioTempMQTTClient::publishConfig() {
    topic += getMAC();
    mqtt.publishMessage(topic.c_str(), json.configPublisher(), false);
}

void BioTempMQTTClient::publishTemp () {
    //topic += getMAC();
    mqtt.publishMessage(topic.c_str(), json.mqttPusblisher(), false);
}


String BioTempMQTTClient::getIP() {
    return mqtt.getIP();
}

String BioTempMQTTClient::getMAC() {
    // ENCONTRAR AGLUMA FUNÇÃO QUE RETIRE OS PONTOS DO ENREÇO MAC
    // "A0:B7:65:DD:89:3C" -> "A0B765DD893C"
    return mqtt.getMAC();
}