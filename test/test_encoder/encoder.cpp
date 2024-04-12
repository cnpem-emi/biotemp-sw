/**
 * @file    unit_tests.cpp
 * @authors Pedro Mamud / Rodrigo Moraes
 * @date    April 12, 2024
 * @brief   Unit tests for the InputController class, focusing on encoder position and button press functionality.
 *
 * @details
 * - This file includes unit tests for the "InputController" class, using the Unity testing framework.
 * - Mock objects are employed to simulate encoder behavior for controlled testing.
 * - Tests cover various encoder positions (zero, positive, negative) and button press status.
 * - A restart counter test verifies the "restart_counter()" function's effectiveness.
 *
 */

#include <unity.h>
#include <Arduino.h>
#include <InputController.cpp>

InputController encoder;

// Mock encoder class for controlled test environment
class MockEncoder {
    public:
        void setPosition(int position) { 
            counter = position; 
            }
        int getPosition() { 
            return counter; 
            }

    private:
        int currentPosition = 0;
};

MockEncoder mockEncoder;

/**
 * @brief Test that encoder position is correctly reported as zero.
 */
void test_encoderPosition_zero() {
  mockEncoder.setPosition(0);
  mockEncoder.getPosition();
  TEST_ASSERT_EQUAL(0, counter);
}

/**
 * @brief Test that encoder position is correctly reported for positive values.
 */
void test_encoderPosition_positive() {
  mockEncoder.setPosition(10);
  mockEncoder.getPosition();
  TEST_ASSERT_EQUAL(10, counter);
}

/**
 * @brief Test that encoder position is correctly reported for negative values.
 */
void test_encoderPosition_negative() {
  mockEncoder.setPosition(-5);
  mockEncoder.getPosition();
  TEST_ASSERT_EQUAL(-5, counter);
}

/**
 * @brief Test that "isPressed" function correctly reports button state (not pressed).
 */
void test_isPressed_false(){
    bool status_enconder = encoder.isPressed();
    TEST_ASSERT_EQUAL(false, status_enconder);
}

/**
 * @brief Test that "restart_counter" function resets the encoder position to zero.
 */
void test_restart_counter() {
  counter = 10; 
  encoder.restart_counter();
  TEST_ASSERT_EQUAL(0, encoder.encoder_position);
}

void setup(){
    //delay(2000);
    UNITY_BEGIN();
}

void loop (){
    RUN_TEST(test_encoderPosition_zero);
    RUN_TEST(test_encoderPosition_positive);
    RUN_TEST(test_encoderPosition_negative);
    RUN_TEST(test_isPressed_false);
    RUN_TEST(test_restart_counter);
    
    UNITY_END();
}

