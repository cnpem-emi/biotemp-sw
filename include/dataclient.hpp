#ifndef _INCLUDE_DATACLIENT_HPP_
#define _INCLUDE_DATACLIENT_HPP_

#include <Arduino.h>

class DataClient {
    public:
        std::string currentMode;

        void getData();
};

#endif  // _INCLUDE_DATACLIENT_HPP_
