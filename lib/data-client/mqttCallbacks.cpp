#include "mqttCallbacks.hpp"

void configRequestCallback(char *topic, byte *payload, unsigned int length) {
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

  handler.mqttConfigRequest(doc);

}