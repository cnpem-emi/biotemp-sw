#include "eventTimer.hpp"

#define PRESCALER 1000 // Scales down the APB clock (0 -> 65536)[16 bits]

/**! 
 * @brief This interrupt callback does the screensaver refresh scheduling
 *  for the graphical handler to actually refresh the screen.
 */
void IRAM_ATTR Timer0_ISR() {
    if (handler.userRecentlyInteracted == true) {
        handler.userRecentlyInteracted = false;
    } else {
        handler.screenSaverEventScheduled = true;
    }

    handler.handleBuzzerDisable();
        
    
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
