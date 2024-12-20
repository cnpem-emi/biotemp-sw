#include "buzzer.hpp"
#include <Arduino.h>


void Buzzer:: buzzerConfig(){ 
    ledcSetup(BUZZER_PWM_CHANNEL, BUZZER_FREQUENCY, BUZZER_PWM_RESOLUTION);
    ledcAttachPin(BUZZER_PIN, BUZZER_PWM_CHANNEL);
}

void Buzzer:: buzzerON() {
  isBuzzerTriggered = true;
  if(!isEnabled) {return;};

  if (buzzerState == HIGH)
  {
    if ((millis() - rememberTime) >= ON_BUZZER_DURATION) {
      buzzerState = LOW; // Altera o estado do buzzer
      rememberTime = millis(); // Atualiza o tempo atual
      //ledcWrite(BUZZER_PWM_CHANNEL, 255); // Valor entre 0 e 255 (metade da resolução)
      ledcWriteTone(BUZZER_PWM_CHANNEL, BUZZER_FREQUENCY);
    }
  } 
  else 
  {
    if ((millis() - rememberTime) >= OFF_BUZZER_DURATION) {
      buzzerState = HIGH; // Altera o estado do buzzer
      rememberTime = millis(); // Atualiza o tempo atual
      //ledcWrite(BUZZER_PWM_CHANNEL, 0);
      ledcWriteTone(BUZZER_PWM_CHANNEL, 0);
    }
  }
  digitalWrite(BUZZER_PIN, buzzerState);
}

void Buzzer::buzzerOFF(){
  isBuzzerTriggered = false;
  digitalWrite(BUZZER_PIN, LOW);
  //ledcWrite(BUZZER_PWM_CHANNEL, 0);
  ledcWriteTone(BUZZER_PWM_CHANNEL, 0);
}

void Buzzer::toggle(bool enable){
  isEnabled = enable;
  if(!enable){
    buzzerOFF();
  }
}

void Buzzer::handleDisable(){
  if (isEnabled == false) {
    buzzerCounter++;
    if (buzzerCounter == (BUZZER_COUNTER_MAX -1)){
      isEnabled = true;
      buzzerCounter = 0;
    }
  }
}