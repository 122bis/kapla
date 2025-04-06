// -----------------------------------------------------------------------------
// config.h 
// project : Kapla VERSION_009 
// -----------------------------------------------------------------------------


#ifndef CONFIG_H
    #define CONFIG_H

    #define MAX_CHAR 64 // config key tokens max length
    #define EOL '\n'     // mac EOL
    #define COMMENT '#'  // comment lines first character
    
    #include <stdio.h>
    #include <string.h>

    int get_value(char searchstring []);

#endif /* !CONFIG_H */

