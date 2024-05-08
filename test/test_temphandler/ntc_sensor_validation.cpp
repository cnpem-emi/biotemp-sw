#include "unity.h"
#include "temphandler.hpp"
#include <Arduino.h>

// Test temperature to be within 
// Reasonable ambient range
#define EXPECTED_TEMP 25
#define DELTA_TEMP 10.0

TempHandler temperature_handler;

void test_ntc_sensor_created() {
    TEST_ASSERT_NOT_EQUAL(nullptr, temperature_handler.available_sensors[NTC_ID])
}

void test_ntc_enabled_true() {
    bool is_enabled = temperature_handler.available_sensors[NTC_ID]->isSensorEnabled();
    TEST_ASSERT_EQUAL(false, is_enabled);
}

void test_ntc_get_temperature() {
    float actual_temperature = temperature_handler.getTemperature(NTC_ID); 
    TEST_ASSERT_FLOAT_WITHIN(DELTA_TEMP, EXPECTED_TEMP, actual_temperature);
}

void test_ntc_disable_function() {
    temperature_handler.available_sensors[NTC_ID]->disableSensor();
    bool is_enabled = temperature_handler.available_sensors[NTC_ID]->isSensorEnabled();
    TEST_ASSERT_EQUAL(false, is_enabled);
}

void setup() {
    delay(2000);

    RUN_TEST(test_ntc_sensor_created);
    RUN_TEST(test_ntc_enabled_true);
    RUN_TEST(test_ntc_get_temperature);
    RUN_TEST(test_ntc_disable_function);

    UNITY_BEGIN();
}

void loop() {
    UNITY_END();
}