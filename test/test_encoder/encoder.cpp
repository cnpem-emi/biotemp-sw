#include <unity.h>
#include <Arduino.h>
#include "InputController.cpp"


InputController encoder;

void test_isPressed_false(){
    bool status_enconder = encoder.isPressed();
    TEST_ASSERT_EQUAL(false, status_enconder);
}

void setup(){
    delay(2000);
    UNITY_BEGIN();

    //attachInterrupt(digitalPinToInterrupt(CLK_PIN), ISR_encoder, RISING);
}

void loop (){
    RUN_TEST(test_isPressed_false);
    UNITY_END();
}

