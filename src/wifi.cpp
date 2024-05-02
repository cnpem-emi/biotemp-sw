#include <wifi.hpp>

void WiFiConnection::config() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID);

    Serial.print("Conectando ao WiFi...");

    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
}

void WiFiConnection::configMQTT() {
    espClient.setCACert(root_ca);
    MQTT.setServer(mqtt_broker, mqtt_port);
    MQTT.setCallback(callback);
    if(!MQTT.connected()) {
        reconnect();
    }
}

void WiFiConnection::mqttLoop() {
    MQTT.loop();
}

String WiFiConnection::getIP() {
    ip = WiFi.localIP().toString();
    return ip;
}

String WiFiConnection::getMAC() {
    mac_address = WiFi.macAddress();
    return mac_address;
}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

void WiFiConnection::publishMessage(const char* topic, String payload , boolean retained){
    if (MQTT.publish(topic, payload.c_str(), true))
        Serial.println("Message publised ["+String(topic)+"]: "+payload);
}

void WiFiConnection::reconnect() {
    while(!MQTT.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to MQTT broker\n", client_id.c_str());
    if (MQTT.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
        Serial.println("Broker connected");
        MQTT.subscribe(topic);
    } else {
        Serial.print("failed with state ");
        Serial.print(MQTT.state());
        delay(2000);
        }
    }
}