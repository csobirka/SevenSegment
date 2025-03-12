#include "SevenSegment.h"

const int segmentPins[] = {14, 15, 16, 17, 18, 19, 20};
const int digitPins[] = {0, 1, 2, 3};
SevenSegment display(segmentPins, digitPins, 4);

void setup() {
    display.begin();
}

void loop() {
    // Display a decimal number (e.g., 1234)
    display.displayNumber(1234);
    for (int j = 0; j < 100; j++) { // Display for a short time
        display.updateDisplay();
        delay(5); // Refresh rate for multiplexing
    }

    // Display a hexadecimal number (e.g., 9A6F)
    display.displayHexNumber("9A6F");
    for (int j = 0; j < 100; j++) { // Display for a short time
        display.updateDisplay();
        delay(5); // Refresh rate for multiplexing
    }

    // Display a decimal number as hexadecimal (e.g., 16 -> 0010)
    display.displayDecimalAsHex(16);
    for (int j = 0; j < 100; j++) { // Display for a short time
        display.updateDisplay();
        delay(5); // Refresh rate for multiplexing
    }
}