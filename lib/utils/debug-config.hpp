#ifndef DEBUG_CONFIG_HPP
#define DEBUG_CONFIG_HPP

#ifdef DEBUG_CUSTOM
    #define DEBUG(x) x
#else
    #define DEBUG(x) 
#endif

#endif