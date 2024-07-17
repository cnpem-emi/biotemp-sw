#include "buzzer.hpp"
#include <Arduino.h>

void Buzzer::alarm(){
    if(temperature_handler.isThresholdTrespassed){
        buzzerON();
        led.ledON();
    }
}

void Buzzer::buzzerON(){
    // Inicia o sinal PWM para gerar som
    ledcWrite(pwmChannel, 128); // Valor entre 0 e 255 (metade da resolução)
    delay(1000); // Mantém o buzzer ativo por 1 segundo
    // Para o sinal PWM para silenciar o buzzer
    ledcWrite(pwmChannel, 0);
    delay(1000); // Mantém o buzzer desativado por 1 segundo

}

void Buzzer::buzzerConfig(){ 
    ledcSetup(pwmChannel, frequency, resolution); // Configura o canal PWM
    ledcAttachPin(buzzerPin, pwmChannel); // Anexa o canal PWM ao pino do buzzer
}