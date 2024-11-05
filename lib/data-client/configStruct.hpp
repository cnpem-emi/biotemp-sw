#ifndef _INCLUDE_CONFIGSTRUCT_HPP_
#define _INCLUDE_CONFIGSTRUCT_HPP_

#define SENSOR_NUM 3
#include <vector>

struct SensorConfig {
            int8_t sensor_id;
            bool is_enabled;
            float min_threshold;
            float max_threshold;
            uint8_t error_code;
        };

#endif 
