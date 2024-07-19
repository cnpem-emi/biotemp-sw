#include "buzzer.hpp"
#include <Arduino.h>

void Buzzer:: buzzerConfig(){ 
    ledcSetup(BUZZER_PWM_CHANNEL, BUZZER_FREQUENCY, BUZZER_PWM_RESOLUTION);
    ledcAttachPin(BUZZER_PIN, BUZZER_PWM_CHANNEL);
}

void Buzzer:: buzzerON() {
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

void Buzzer::buzzerOFF(){
  digitalWrite(BUZZER_PIN, LOW);
  ledcWrite(BUZZER_PWM_CHANNEL, 0);
}