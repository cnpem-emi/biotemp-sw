#ifndef _INCLUDE_DATACLIENT_HPP_
#define _INCLUDE_DATACLIENT_HPP_

#include <Arduino.h>
#include <vector>
#include <temphandler.hpp>

class DataClient {
    public:
        std::string currentMode;

        void getData(std::vector<TempHandler> sensorList);
};

#endif  // _INCLUDE_DATACLIENT_HPP_
