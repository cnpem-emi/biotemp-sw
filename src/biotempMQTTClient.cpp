#include <biotempMQTTClient.hpp>

void BioTempMQTTClient::mqttConfig() {
    mqtt.config(WIFI_SSID, WIFI_PASSWORD);
}

void BioTempMQTTClient::publish(const char* topic, String message) {
    mqtt.publishMessage(topic, message, false);
}

String BioTempMQTTClient::getIP() {
    return mqtt.getIP();
}

String BioTempMQTTClient::getMAC() {
    return mqtt.getMAC();
}