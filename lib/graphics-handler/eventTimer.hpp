#ifndef _EVENTTIMER_HPP_
#define _EVENTTIMER_HPP_

#include <esp32-hal-timer.h>
#include "graphicalViewHandler.hpp"

#define PRESCALER 1000 // Scales down the APB clock (0 -> 65536)[16 bits]

extern GraphicalViewHandler handler;

/**! 
 * @brief This interrupt callback does the screensaver refresh scheduling
 *  for the graphical handler to actually refresh the screen.
 */
void IRAM_ATTR Timer0_ISR();

/******************************************************************/
/*!
    @brief Configures the event timer interrupt.
    @param t_out The time to set an interrupt in seconds.
*/
/******************************************************************/
void configTimer(int t_out);

#endif 