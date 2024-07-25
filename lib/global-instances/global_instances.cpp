#include "global_instances.hpp"

GraphicalViewHandler handler;
TempHandler temperature_handler;
BioTempMQTTClient mqtt{temperature_handler};

