// -----------------------------------------------------------------------------
// config.c
// project : Kapla VERSION_009 
// -----------------------------------------------------------------------------

#define CONFIG_FILEPATH "./config.ini"

#include "config.h"


int get_value(char searchstring []) {
    FILE * fp;
    char key [MAX_CHAR];
    float value =0;

    if ((fp = fopen(CONFIG_FILEPATH, "r+")) == NULL) {
        perror("error reading config file : ");
        return -1;
    }

    while(1) {

        if (fscanf(fp, "%s = %f", key, & value) != 2) {
            if (feof(fp)) {
                // EOF FILE
                printf("error : reached end of file - \"%s\" not found\n", searchstring);
                break;
            }
            if (key[0] == COMMENT) {
                // COMMENT LINE --> SKIP LINE with fgetc
                while (fgetc(fp) != EOL) {
                    // just iterate until EOL
                }
                continue;
            }
            perror("fscanf()");
            break;
        }
        // KEY = VALUE LINE FOUND
        if (strcmp(key, searchstring) == 0) {
            // STOP HERE IF KEY = searchstring
            printf("found key: %s --> Value: %f\n", key,  value);
            break;
        }
    }

    fclose(fp);
    return value;
}

