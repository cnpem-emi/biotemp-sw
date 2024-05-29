#ifndef _EVENTTIMER_HPP_
#define _EVENTTIMER_HPP_

#include <esp32-hal-timer.h>

#define PRESCALER 1000 // Scales down the APB clock (0 -> 65536)[16 bits]

extern GraphicalViewHandler handler;

// Interrupt callback
void IRAM_ATTR Timer0_ISR() {
    //Serial.println(handler.userRecentlyInteracted);
    if (handler.userRecentlyInteracted == true) {
        handler.userRecentlyInteracted = false;
    } else {
        handler.screenSaverEventScheduled = true;
    }

    //if (handler.isScreenSaverOn == true)
    //{
    //    handler.screenSaverEventScheduled = false;
    //}
}

/******************************************************************/
/*!
    @brief Configures the event timer interrupt.
    @param t_out The time to set an interrupt in seconds.
*/
/******************************************************************/
void configTimer(int t_out) {
    hw_timer_t *Timer0_Cfg = NULL;
    float timer_ticks;

    timer_ticks = t_out*APB_CLK_FREQ/PRESCALER;

    Timer0_Cfg = timerBegin(0, PRESCALER, true);
    timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
    timerAlarmWrite(Timer0_Cfg, timer_ticks, true);
    timerAlarmEnable(Timer0_Cfg);
}

#endif // _EVENTTIMER_HPP_