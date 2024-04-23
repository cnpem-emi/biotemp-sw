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

String WiFiConnection::getIP() {
    ip = WiFi.localIP().toString();
    return ip;
}
