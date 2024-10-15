#ifndef _INCLUDE_CONFIGSTRUCT_HPP_
#define _INCLUDE_CONFIGSTRUCT_HPP_

#include <map>

#define SENSOR_NUM 3

struct SensorConfig {
            uint8_t sensor_id;
            uint8_t sensor_type;
            bool is_enabled;
            float min_threshold;
            float max_threshold;
        };


//typedef enum  {NONE = -1, NTC = 0 , PT100 = 1} SensorTypes;
// std::map<SensorTypes, std::string> sensorTypeToLabel = {{NONE, "NONE"},
//                                                         {NTC, "NTC"},
//                                                         {PT100, "PT100"}};

#endif 
