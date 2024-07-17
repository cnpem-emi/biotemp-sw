#include <biotempMQTTClient.hpp>

void BioTempMQTTClient::mqttConfig() {
    mqtt.config(WIFI_SSID, WIFI_PASSWORD);
}

void BioTempMQTTClient::publish(const char* topic, String message) {
    mqtt.publishMessage(topic, message, false);
}

//na aplicação final, geralmente as inscrições e publicações devem usar o nome completo do tópico,
//tipo biotemp/biotemp_8065994B310A/state ou biotemp/biotemp_8065994B310A/config
void BioTempMQTTClient::publishConfig() {
    String configTopic;
    topic += getMAC();
    configTopic = topic + "/config";
    stateTopic = topic + "/state";
    mqtt.publishMessage(configTopic.c_str(), jsonHandler.configPublisher(), false);
}

void BioTempMQTTClient::publishTemp () {
    mqtt.publishMessage(stateTopic.c_str(), jsonHandler.mqttGeneratePacket(), false);
}

String BioTempMQTTClient::getIP() {
    return mqtt.getIP();
}

String BioTempMQTTClient::getMAC() {
    String mac = mqtt.getMAC();
    mac.replace(":", "");
    return mac;
}