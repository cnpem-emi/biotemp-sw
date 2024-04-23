#ifndef _INCLUDE_WIFI_H_
#define _INCLUDE_WIFI_H_

#include <WiFi.h>

/**
 * @class WiFiConnection
 * @brief Class for managing WiFi connections.
 *
 * This class provides methods for configuring a WiFi connection
 */
class WiFiConnection {
    public:
        void config();  // Configures the WiFi connection
        String getIP(); // Gets the IP address assigned to the ESP device

    private:
        String ip;
        const String WIFI_SSID = "Devices";

};

#endif  // _INCLUDE_DATA_CLIENT_H_