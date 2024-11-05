#include <biotempMQTTClient.hpp>

void BioTempMQTTClient::mqttConfig() {
    mqtt.config(WIFI_SSID, WIFI_PASSWORD);
    mqtt.MQTT.setBufferSize(1000);
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

void BioTempMQTTClient::publishTemp() {
    stateTopic = topic + "/state";
    mqtt.publishMessage(stateTopic.c_str(), jsonHandler.mqttGeneratePacket(), false);

}

void BioTempMQTTClient::publishReadBack() {
    readBackTopic = topic + "/read_back";
    mqtt.publishMessage(readBackTopic.c_str(), jsonHandler.readBackJSON(), false);
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

void BioTempMQTTClient::configRequestCallback(char *topic, byte *payload, unsigned int length) {
    std::string payloadStr;
    payloadStr.reserve(length);
    
    DEBUG(Serial.print("Message arrived in topic: ");
          Serial.println(topic);
          Serial.print("Message:");) 

          Serial.println("im here");  
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
        payloadStr += (char) payload[i];
    }
    DEBUG(Serial.println();
          Serial.println("-----------------------");)

  // Cria um buffer para o JSON
  ConfigRequestDocument doc; 

  // Faz o parsing do JSON
  DeserializationError error = deserializeJson(doc, payloadStr);  
  if (error) {
    Serial.print("Falha ao fazer o parsing do JSON: ");
    Serial.println(error.f_str());
    return;
  }

  jsonHandler.handleConfigRequest(doc);
  
  publishReadBack();

}