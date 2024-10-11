#ifndef MODES_AND_LAYOUTS_HPP
#define MODES_AND_LAYOUTS_HPP

#define MODES_NUM 4// Number of modes
#define SENSOR_LAYOUTS_NUM 4


// Operation modes
typedef enum {
    ULTRAFREEZER_MODE,
    FREEZER_MODE,
    REFRIGERATOR_MODE,
    AMBIENT_MODE
} OperationModes;

typedef enum {
    NONE,
    NTC1,
    NTC2, 
    PT100
} SensorLayouts;

#endif