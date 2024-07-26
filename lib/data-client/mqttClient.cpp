#include <mqttClient.hpp>

void MQTTClient::config(const char* wifi_ssid, const char* wifi_password) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_password);

    DEBUG(Serial.print("Conectando ao WiFi...");)

    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    //configMQTT(certificate, broker, port);
    configMQTT(broker, port);
    
}

void MQTTClient::configMQTT(const char* broker, const int port) {
    MQTT.setServer(broker, port);
    MQTT.setCallback(callback);
    if(!MQTT.connected()) {
        connect();
    }
}


void MQTTClient::mqttLoop() {
    MQTT.loop();
}

String MQTTClient::getIP() {
    ip = WiFi.localIP().toString();
    return ip;
}

String MQTTClient::getMAC() {
    mac_address = WiFi.macAddress();
    return mac_address;
}

void callback(char *topic, byte *payload, unsigned int length) {
    DEBUG(Serial.print("Message arrived in topic: ");
          Serial.println(topic);
          Serial.print("Message:");) 

    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    DEBUG(Serial.println();
          Serial.println("-----------------------");)
}

void MQTTClient::publishMessage(const char* topic, String payload , boolean retained){
    bool messageWasPublished = MQTT.publish(topic, payload.c_str(), true);
    if (messageWasPublished){
        DEBUG(Serial.println("Message published ["+String(topic)+"]: "+payload);)
    }
    else {
        DEBUG(Serial.println("Error Sending Message["+String(topic)+"]: "+payload);)
    }
}

void MQTTClient::connect() {
    while(!MQTT.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());

    DEBUG(Serial.printf("The client %s connects to MQTT broker\n", client_id.c_str());)
    
    if (MQTT.connect(client_id.c_str())) {
        DEBUG(Serial.println("Broker connected");)
        //MQTT.subscribe(topic); //Verificar necessidade
    } else {
        DEBUG(Serial.print("failed with state ");
              Serial.print(MQTT.state());)
        delay(2000);
        }
    }
}

MQTTClient::MQTTClient(const char* mqttBroker, const int mqttPort) {
    broker = mqttBroker;
    port = mqttPort;
}
