#ifndef _MQTTCALLBACKS_HPP_
#define _MQTTCALLBACKS_HPP_

#include <ArduinoJson.h>

#include "biotempDataJSON.hpp"
#include "global_instances.hpp"

void configRequestCallback(char *topic, byte *payload, unsigned int length); 

#endif  
