#ifndef _GLOBAL_INSTANCES_HPP_
#define _GLOBAL_INSTANCES_HPP_

#include "graphicalViewHandler.hpp"
#include "temphandler.hpp"
#include "biotempMQTTClient.hpp"

extern GraphicalViewHandler handler;
extern TempHandler temperature_handler;
extern BioTempMQTTClient mqtt;

#endif