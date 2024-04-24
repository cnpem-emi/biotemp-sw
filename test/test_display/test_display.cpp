/**
 * @file    unit_tests.cpp
 * @authors Pedro Mamud / Rodrigo Moraes
 * @date    April 16, 2024
 * @brief   This file defines a unit test to verify the correct behavior of the Display module.
 *
 * @details
 * - 
 */

#include <unity.h>
#include <Arduino.h>
#include "display.cpp"

Display disp;

class MockDisplay {
    public:
        void setPosition(int position) { 
            disp.arrowPos = position; 
        }
};

MockDisplay mockDisplay;


void test_drawArrow() {
    mockDisplay.setPosition(2);
    TEST_ASSERT_EQUAL(2, disp.arrowPos);
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
}

void loop() {

    RUN_TEST(test_drawArrow);
    UNITY_END();
}

