#include "functions.h"

#define SAMPLING_FREC 100
#define WINDOW_SIZE   2000 //Window size in ms

// Declare the arrays as global variables
int mw1_arr[100];  // Adjusted for 100 data points
int mw2_arr[100];  // Added this line for the second channel
float mw_arr[100][2];  // Adjusted for two channels

// IIR filter parameters
const float alpha = 0.7; // Smoothing factor, adjust based on your needs
float filteredValue1 = 0.0;
float filteredValue2 = 0.0;  // Added this line for the second channel

// Normalization parameters
const int minOutput = 0;
const int maxOutput = 1023; // Arduino's ADC range

// Fixed baselines
const int baselineValue1 = 300; // Adjust based on your needs
const int baselineValue2 = 200; // Added this line for the second channel

float (*prelim_collection())[2]{  // Adjusted for two channels
  for (int arr_idx = 0; arr_idx < 100; arr_idx++){  // Adjusted for 100 data points
    // Read raw EMG values
    int emgValue1 = analogRead(pin_MW1);
    int emgValue2 = analogRead(pin_MW2);  // Added this line for the second channel

    // Subtract the fixed baseline
    emgValue1 -= baselineValue1;
    emgValue2 -= baselineValue2;  // Added this line for the second channel

    // Apply the IIR filter to smooth the values
    filteredValue1 = (alpha * emgValue1) + ((1 - alpha) * filteredValue1);
    filteredValue2 = (alpha * emgValue2) + ((1 - alpha) * filteredValue2);  // Added this line for the second channel

    // Ensure non-negative values
    filteredValue1 = max(0.0f, filteredValue1);
    filteredValue2 = max(0.0f, filteredValue2);  // Added this line for the second channel

    // Normalize the values
    int normalizedValue1 = map(int(filteredValue1), 0, 1023, minOutput, maxOutput);
    int normalizedValue2 = map(int(filteredValue2), 0, 1023, minOutput, maxOutput);  // Added this line for the second channel

    // Store the normalized values in the separate arrays
    mw1_arr[arr_idx] = normalizedValue1;
    mw2_arr[arr_idx] = normalizedValue2;  // Added this line for the second channel
  }

  // Stack the separate arrays into mw_arr along a new axis
  for (int i = 0; i < 100; i++) {  // Adjusted for 100 data points
    mw_arr[i][0] = mw1_arr[i];
    mw_arr[i][1] = mw2_arr[i];  // Added this line for the second channel
  }

  return mw_arr;
}
