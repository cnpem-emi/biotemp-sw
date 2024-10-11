#include <biotempMQTTClient.hpp>

void BioTempMQTTClient::mqttConfig() {
    mqtt.config(WIFI_SSID, WIFI_PASSWORD);
}

void BioTempMQTTClient::publish(const char* topic, String message) {
    mqtt.publishMessage(topic, message, false);
}


void BioTempMQTTClient::publishConfig() {
    String configTopic;
    topic += getMAC();
    configTopic = topic + "/config";
    mqtt.publishMessage(configTopic.c_str(), jsonHandler.configPublisher(), false);
}

void BioTempMQTTClient::publishTemp () {
    stateTopic = topic + "/state";
    mqtt.publishMessage(stateTopic.c_str(), jsonHandler.mqttGeneratePacket(), false);

}

bool BioTempMQTTClient::isConfigured(){
    return mqtt.isConfigured;
}

String BioTempMQTTClient::getIP() {
    return mqtt.getIP();
}

bool BioTempMQTTClient::isConnected(){
    return mqtt.isConnected;
}

void BioTempMQTTClient::mqttLoop(){
    mqtt.mqttLoop();
}

String BioTempMQTTClient::getMAC() {
    String mac = mqtt.getMAC();
    mac.replace(":", "");
    return mac;
}

