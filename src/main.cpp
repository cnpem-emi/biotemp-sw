/*! @mainpage Biotemp Temperature Monitoring System
 *
 * @section intro_sec Introduction
 *
 *  The Biotemp Instrumentation System is a user-friendly IoT device designed for collecting room temperature data.
 *  It is made to be effortless to set up and use, in a plug-and-play manner. Equipped with menus displayed on an LCD screen,
 *  it offers a straightforward interface for users to access and manage temperature information effectively.  
 */

#include "biotemp.hpp"

Biotemp biotemp;

void setup() {
   Serial.begin(9600);
   biotemp.setup();
   biotemp.biotempBoot();
}

void loop() {
  biotemp.mainLoop();
}

