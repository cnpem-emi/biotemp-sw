#ifndef _INCLUDE_CONFIGSTRUCT_HPP_
#define _INCLUDE_CONFIGSTRUCT_HPP_

#define SENSOR_NUM 3

#include <vector>

struct SensorConfig {
            int8_t sensor_id = 0;
            bool is_enabled = false;
            float min_threshold = 0;
            float max_threshold = 0;
            float gain = 1.0;
            float offSet = 0;
            uint8_t error_code = 0;
        };

#endif 
