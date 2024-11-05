#ifndef _INCLUDE_BIOTEMPJSON_HPP_
#define _INCLUDE_BIOTEMPJSON_HPP_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <string>
#include <vector>

#include "temphandler.hpp"
#include "modes-and-layouts.hpp"
#include "configStruct.hpp"
//#include "biotempMQTTClient.hpp"

#define NUM_SENSORS 3

typedef JsonDocument ConfigRequestDocument; 

// extern DynamicJsonDocument configDoc;

/*****************************************************/
/*!
    @brief DataClient interface class. It is used to send the data from the sensor to other modules.
*/
/*****************************************************/
class BiotempDataJson {
    public:
        
        // Gets the temperature from the sensor
        String configPublisher();

        void handleConfigRequest(ConfigRequestDocument& configJson);

        String mqttGeneratePacket();

        void setSensorConfig(JsonObject& config);
        void setErrorCodes(const std::vector<uint8_t>& errors);
        String readBackJSON();

        BiotempDataJson(TempHandler& temp_handler): temperature_handler{temp_handler}{};

        std::vector<SensorConfig> sensorConfigs; // Para armazenar os dados dos sensores

    private:
        std::map<OperationModes, std::string> MODES_DISPLAY_STR = {{ULTRAFREEZER_MODE, "UltraFreezer"},
                                                                   {FREEZER_MODE, "Freezer"},
                                                                   {REFRIGERATOR_MODE, "Refrigerator"},
                                                                   {AMBIENT_MODE, "Ambient"}};

        std::map<SensorLayouts, std::string> SENSOR_LAYOUTS_STR = {{NONE, "None"},
                                                                   {NTC1, "NTC1"},
                                                                   {NTC2, "NTC2"},
                                                                   {PT100, "PT100"}};

        
        TempHandler& temperature_handler;

        JsonObject sensorConfig;              // Armazena a configuração do sensor
        
        std::vector<uint8_t> errorCodes;      // Armazena os códigos de erro


};


#endif 