#ifndef _INCLUDE_BIOTEMPMQTTCLIENT_HPP_
#define _INCLUDE_BIOTEMPMQTTCLIENT_HPP_

#include <mqttClient.hpp>
#include <secrets.h>

/**************************************************************/
/*!
*   @brief BioTemp MQTT interface class.
*/
/**************************************************************/
class BioTempMQTTClient {
    public:
    /**************************************************************/
    /*!
    *   @brief Publish a message to the specified topic.
    *   @param topic The topic to publish a message.
    *   @param message The message to be published.
    */
    /**************************************************************/
        void publish(const char* topic, String message);

        // Configures the MQTT module in the BioTemp context.
        void mqttConfig();

        // Returns the device IP.
        String getIP();

        //Returns the device MAC address.
        String getMAC();

    private:
        const char *topic = "test"; // MQTT topic to publish messages

        MQTTClient mqtt = MQTTClient(BROKER_URL, PORT);
        //MQTTClient mqtt = MQTTClient(USERNAME, PASSWORD, root_ca, BROKER_URL, PORT);
};

#endif  // _INCLUDE_BIOTEMPMQTTCLIENT_HPP_
