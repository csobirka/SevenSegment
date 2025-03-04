 #include "SevenSegment.h"
 const int segmentPins[] = {14, 15, 16, 17, 18, 19, 20};
 const int digitPins[] = {0, 1, 2, 3};
 SevenSegment display(segmentPins, digitPins, 4);

 void setup() {
     display.begin();
 }

 void loop() {
     display.displayNumber(1234);
     display.updateDisplay();
     delay(5); // Refresh rate for multiplexing
 }
