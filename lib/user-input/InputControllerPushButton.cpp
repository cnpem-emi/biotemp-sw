#include "InputControllerPushButton.hpp"

ezButton button(PUSH_BUTTON_PIN); // create ezButton object that attach to pin 12

void InputControllerPushButton::configPushButton() {
    //pinMode(PUSH_BUTTON_PIN, INPUT_PULLUP);
    button.setDebounceTime(DEBOUNCE_TIME); // set debounce time
}

bool InputControllerPushButton::isPressed() {
    bool isPressed = button.isPressed();
    return isPressed;
}

bool InputControllerPushButton::isReleased() {
    bool isReleased = button.isReleased();
    return isReleased;
}
