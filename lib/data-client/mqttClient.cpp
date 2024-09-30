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
    
    if(isConnected){MQTT.loop();} else{connectWifi();}

    if(!isConfigured){configMQTT(broker, port);}
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
          Serial.println("---------------------------");)
}

void MQTTClient::publishMessage(const char* topic, String payload , boolean retained=true){
    Serial.print("Sending:");
    Serial.println(payload.c_str());

    bool messageWasPublished = MQTT.publish(topic, payload.c_str(), retained);
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
    String macAddr = getMAC();
    client_id += macAddr;

    // Formats topic for last will
    macAddr.replace(":", "");

    std::string topicBase = std::string{"biotemp/biotemp_"} + macAddr.c_str(); 

    DEBUG(Serial.println(" Last Will Topic: "); Serial.println((topicBase + willTopic).c_str());)
    DEBUG(Serial.printf("The client %s connects to MQTT broker\n", client_id.c_str());)
    
    if (MQTT.connect(client_id.c_str(), (topicBase + willTopic).c_str(), willQOS, willRetain, willMessage)) {
        DEBUG(Serial.println("Broker connected");)
        //to subscribe topic:
        std::string configTopic = topicBase + "/config";
        MQTT.subscribe(configTopic.c_str()); 
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
