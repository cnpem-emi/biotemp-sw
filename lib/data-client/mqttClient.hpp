#ifndef _INCLUDE_MQTTCLIENT_H_
#define _INCLUDE_MQTTCLIENT_H_

#include <WiFi.h>
#include <PubSubClient.h>
//#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include "debug-config.hpp"

#define CONNECTION_WAIT_TIME 500

/**
 * @class WiFiConnection
 * @brief Class for managing WiFi connections.
 *
 * This class provides methods for configuring a WiFi connection
 */
class MQTTClient {
    public:
        void config(const char* wifi_ssid, const char* wifi_password);  // Configures the WiFi connection

        /*************************************************************/
        /*!
        *   @brief MQTT main configuration, needs to be called at "void setup()"
        *   @param certificate Certificate for secure connection.
        *   @param broker broker URL.
        *   @param port broker port.
        */
        /*************************************************************/
        //void configMQTT(const char* certificate, const char* broker, const int port);
        void configMQTT(const char* broker, const int port);
        void mqttLoop(); // MQTT main loop, needs to be called at "void loop()"

        /*************************************************************/
        /*!
        *   @brief Sends a message to the broker.
        *   @param topic The topic of the message.
        *   @param payload The message to be sent.
        *   @param retained If true, stores the message to ensure that 
        *       any nre client subscribing to the topic will receive the message.
        */
        /*************************************************************/
        void publishMessage(const char* topic, String payload , boolean retained);
        String getIP(); // Gets the IP address assigned to the ESP device
        String getMAC(); // Gets the MAC address of the device
        
        /*************************************************************/
        /*!
        *   @brief MQTTClient constructor. Defines the user and password
        *           to the class methods.
        *   @param mqttUser MQTT broker username
        *   @param mqttPass MQTT broker password
        *   @param mqttCertificate TLS certificate for secure connection
        *   @param mqttBroker MQTT broker URL
        *   @param mqttPort MQTT connection port
        */
        /*************************************************************/
        MQTTClient(const char* mqttBroker, const int mqttPort);
        

        void connectWifi();
        void setWifiParams(const char* wifi_ssid, const char* wifi_password);

        bool isConnected = false;
        bool isConfigured = false;

    private:
        String ip; // Device IP
        String mac_address; // Device MAC address

        const char* username = NULL;
        const char* password = NULL;
        const char* certificate;
        const char* broker;
        int port;

        const char* wifiSSID;
        const char* wifiPassword;


        //WiFiClientSecure espClient; // Instace of secure client, needs certificate
        WiFiClient espClient;
        PubSubClient MQTT = PubSubClient(espClient);

        // Create the connection between the device and MQTT broker
        //void connect(const char* user, const char* password);
        void connect();
};

/****************************************************************/
/*!
* @brief This function is called every time a message is received 
*    from the broker
*/
/****************************************************************/
void callback(char *topic, byte *payload, unsigned int length);

#endif  // _INCLUDE_MQTTCLIENT_H_
