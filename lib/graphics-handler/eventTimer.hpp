#ifndef _EVENTTIMER_HPP_
#define _EVENTTIMER_HPP_

#include <esp32-hal-timer.h>

// Variáveis globais para o timer
hw_timer_t *timer = NULL;
volatile bool timerFlag = false;

// Função de callback para a interrupção do timer
void IRAM_ATTR onTimer() {
    timerFlag = true;
}

#endif // _EVENTTIMER_HPP_