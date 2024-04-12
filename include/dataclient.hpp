#ifndef _INCLUDE_DATACLIENT_HPP_
#define _INCLUDE_DATACLIENT_HPP_

#include <Arduino.h>
#include <vector>
#include <temphandler.hpp>

class DataClient {
    public:
        void subscribe(SensorPT100 *s);
        void subscribe(SensorNTC *s);

        void unsubscribe(SensorPT100 *s);
        void unsubscribe(SensorNTC *s);

        void getData();

    private:
        bool registered[3] = {false, false, false};
};

#endif  // _INCLUDE_DATACLIENT_HPP_
