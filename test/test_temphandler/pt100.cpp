#include "unity.h"
#include "temphandler.hpp"
#include <Arduino.h>

SensorPT100 s1;

void test_enabled_true() {
    //TEST_ASSERT_EQUAL(, LED_BUILTIN);
}

void test_enabled_false() {
    s1.enabled = false;
    TEST_ASSERT_EQUAL(false, s1.enabled);
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
}

void loop() {
    RUN_TEST(test_enabled_true);
    RUN_TEST(test_enabled_false);
    UNITY_END();
}