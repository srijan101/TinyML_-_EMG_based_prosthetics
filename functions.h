#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <Arduino.h>

#define pin_MW1 36
#define pin_MW2 39  // Added this line for the second channel

#define TIME             2    //seconds
#define FREQUENCY        500 //Hz 
#define DATA_PER_SENSOR  TIME*FREQUENCY

extern float mw_arr[100][2];  // Adjusted for two channels

float (*prelim_collection())[2];  // Adjusted for two channels

#endif  // FUNCTIONS_H_
