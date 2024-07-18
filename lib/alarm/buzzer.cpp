#include "buzzer.hpp"
#include <Arduino.h>



void Buzzer::alarm(){
    if(temperature_handler.isThresholdTrespassed){
        buzzerON();
        led.ledON();
    }
}

void Buzzer:: buzzerConfig(){ 
    ledcSetup(pwmChannel, frequency, resolution);
    ledcAttachPin(buzzerPin, pwmChannel);
}

void Buzzer:: buzzerON() {
  if (buzzerState == HIGH)
  {
    if ((millis() - rememberTime) >= onBuzzerDuration) {
      buzzerState = LOW; // Altera o estado do buzzer
      rememberTime = millis(); // Atualiza o tempo atual
      ledcWrite(pwmChannel, 128); // Valor entre 0 e 255 (metade da resolução)
    }
  } 
  else 
  {
    if ((millis() - rememberTime) >= offBuzzerDuration) {
      buzzerState = HIGH; // Altera o estado do buzzer
      rememberTime = millis(); // Atualiza o tempo atual
      ledcWrite(pwmChannel, 0);
    }
  }
  digitalWrite(buzzerPin, buzzerState);
}