#include <mqttClient.hpp>

void MQTTClient::config(const char* wifi_ssid, const char* wifi_password){
    setWifiParams(wifi_ssid, wifi_password);
    connectWifi();
    configMQTT(broker, port);
}

void MQTTClient::setWifiParams(const char* wifi_ssid, const char* wifi_password) {
    wifiSSID = wifi_ssid;
    wifiPassword = wifi_password; 
}

void MQTTClient::connectWifi(){
    if(wifiSSID != nullptr){
        WiFi.mode(WIFI_STA);
        WiFi.begin(wifiSSID, wifiPassword);

        DEBUG(Serial.println("Conectando ao WiFi...");)
        delay(CONNECTION_WAIT_TIME);

        if(WiFi.status() != WL_CONNECTED) {
            DEBUG(Serial.println("Was not able to connect to WIFI");)
            isConnected = false;
        }
        else{
            isConnected = true;
        }
    }
    else{
        //DEBUG(Serial.println("Password and SSID incorrectly setted (or not setted)");) 
    }
}

void MQTTClient::configMQTT(const char* broker, const int port) {
    if (isConnected == true) {
        MQTT.setServer(broker, port);
        MQTT.setCallback(callback);
        if(!MQTT.connected()) {
            connect();
            isConfigured = false;
        } else {
            isConfigured = true;
        }
    }
}


void MQTTClient::mqttLoop() {
    if(isConnected){MQTT.loop();} else {connectWifi(); configMQTT(broker, port);}
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
