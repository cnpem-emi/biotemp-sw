#ifndef _INCLUDE_BIOTEMPMQTTCLIENT_HPP_
#define _INCLUDE_BIOTEMPMQTTCLIENT_HPP_

#include "mqttClient.hpp"
#include "secrets.h"

#include "biotempDataJSON.hpp"

#include <functional>

using namespace std::placeholders;

/**************************************************************/
/** 
*   @brief BioTemp MQTT interface class.
*/
/**************************************************************/
class BioTempMQTTClient {
    public:
        
        BioTempMQTTClient(TempHandler& temp_handler): jsonHandler{BiotempDataJson(temp_handler)}{}
        
        BiotempDataJson jsonHandler;
    /**************************************************************/
    /** 
    *   @brief Publish a message to the specified topic.
    *   @param topic The topic to publish a message.
    *   @param message The message to be published.
    */
    /**************************************************************/
        void publish(const char* topic, String message);
        
        void publishConfig();
        void publishTemp();
        void publishReadBack();

        // Configures the MQTT module in the BioTemp context.
        void mqttConfig();
        void mqttLoop();

        // Returns the device IP.
        String getIP();

        //Returns the device MAC address.
        String getMAC();

        bool isConnected();
        bool isConfigured();

        // Binds callback to instance
        void configCallback(){mqtt.MQTT.setCallback(std::bind(&BioTempMQTTClient::configRequestCallback, this, _1, _2, _3));};

        void configRequestCallback(char *topic, byte *payload, unsigned int length);

    private:
        //const char *topic = "test";
        String topic = "biotemp/biotemp_"; // MQTT topic to publish messages

        String stateTopic;
        String readBackTopic;

        MQTTClient mqtt = MQTTClient(BROKER_URL, PORT);
};

#endif  // _INCLUDE_BIOTEMPMQTTCLIENT_HPP_
