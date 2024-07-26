#include "buzzer.hpp"
#include <Arduino.h>

/** 
 * The `buzzerConfig` function sets up the buzzer PWM channel and attaches it to a specific pin.
 */
void Buzzer:: buzzerConfig(){ 
    ledcSetup(BUZZER_PWM_CHANNEL, BUZZER_FREQUENCY, BUZZER_PWM_RESOLUTION);
    ledcAttachPin(BUZZER_PIN, BUZZER_PWM_CHANNEL);
}

/** 
 * The function `buzzerON` controls the state of a buzzer based on specified durations and updates the
 * buzzer state and LED brightness accordingly.
 *  
 */
void Buzzer:: buzzerON() {
  if(!isEnabled) {return;};

  if (buzzerState == HIGH)
  {
    if ((millis() - rememberTime) >= ON_BUZZER_DURATION) {
      buzzerState = LOW; // Altera o estado do buzzer
      rememberTime = millis(); // Atualiza o tempo atual
      ledcWrite(BUZZER_PWM_CHANNEL, 128); // Valor entre 0 e 255 (metade da resolução)
    }
  } 
  else 
  {
    if ((millis() - rememberTime) >= OFF_BUZZER_DURATION) {
      buzzerState = HIGH; // Altera o estado do buzzer
      rememberTime = millis(); // Atualiza o tempo atual
      ledcWrite(BUZZER_PWM_CHANNEL, 0);
    }
  }
  digitalWrite(BUZZER_PIN, buzzerState);
}

/** 
 * The function turns off a buzzer by setting the digital output pin to LOW and the PWM channel to 0.
 */
void Buzzer::buzzerOFF(){
  digitalWrite(BUZZER_PIN, LOW);
  ledcWrite(BUZZER_PWM_CHANNEL, 0);
}

/** 
 * The function `toggle` in the `Buzzer` class sets the `isEnabled` flag based on the input parameter
 * and turns off the buzzer if the input is false.
 * 
 * @param enable Disables or Enables toggling 
 */ 
void Buzzer::toggle( bool enable){
  isEnabled = enable;
  if(!enable){
    buzzerOFF();
  }
}