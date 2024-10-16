#ifndef _INCLUDE_CONFIGSTRUCT_HPP_
#define _INCLUDE_CONFIGSTRUCT_HPP_

#define SENSOR_NUM 3
#include <vector>

struct SensorConfig {
            uint8_t sensor_id;
            uint8_t sensor_type;
            bool is_enabled;
            float min_threshold;
            float max_threshold;
        };

//SensorConfig sensorsConfigValues[SENSOR_NUM];


#endif 
