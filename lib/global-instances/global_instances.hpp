/**
 * @file global_instaces.hpp
 * @brief This is a place to place all global variables, 
 * if something is in here, have a good enough explanation for why.
 */

#ifndef _GLOBAL_INSTANCES_HPP_
#define _GLOBAL_INSTANCES_HPP_

#include "graphicalViewHandler.hpp"

/* Making the handler global is necessary because the handler 
   is used in the callbacks for the interrupts. 
   Without it this feature would be kinda annoying to implement. */
extern GraphicalViewHandler handler;

#endif