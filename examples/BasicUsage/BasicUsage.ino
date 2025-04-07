#include <SevenSegment.h>

// Define your pin connections
const int segmentPins[] = {14, 15, 16, 17, 18, 19, 20, 21}; // a, b, c, d, e, f, g, dp
const int digitPins[] = {0, 1, 2, 3}; // Digit 1, 2, 3, 4
const int led_en = 4; // LED row enable

// Create display object
SevenSegment display(segmentPins, digitPins, led_en);

void setup() {
    // Nothing needed here for this example
}

void loop() {
    // Demo all functions
    
    // 1. Display decimal numbers with decimal points
    display.setDecimal(1234, 2); // Show 12.34
    for (int i = 0; i < 100; i++) {
        display.updateDisplay();
    }
    
    display.setDecimal(-255, 1); // Show -25.5
    for (int i = 0; i < 100; i++) {
        display.updateDisplay();
    }
    
    // 2. Display decimal as hex
    display.setDecimalAsHex(255); // Shows "00FF"
    for (int i = 0; i < 100; i++) {
        display.updateDisplay();
    }
    
    // 3. Display hex directly
    display.setHex("9A6F"); // Shows "9A6F"
    for (int i = 0; i < 100; i++) {
        display.updateDisplay();
    }
    // 5. Clear all digits
    display.clearAllDigits();
    delay(500);

    // 4. Show binary on segments
    display.showBinary(0b10101010); // Binary pattern (170 in decimal)
    for (int i = 0; i < 100; i++) {
        display.updateDisplay();
    }
    
    // 6. Clear all LEDs (different from clearAllDigits)
    display.clearAllLeds();
    delay(500);
}