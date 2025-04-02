#include <SevenSegment.h>

// Define pins
const uint8_t segmentPins[] = {14, 15, 16, 17, 18, 19, 20, 21};
const uint8_t digitPins[] = {0, 1, 2, 3};
const uint8_t ledEnPin = 4;

SevenSegment display(segmentPins, digitPins, ledEnPin);

void setup() {
  display.begin();
}

void loop() {
  display.setDecimal(1234);
  display.updateDisplay();
  delay(500);
  clearAllDigits();
  display.setDecimalAsHex(255); // Shows "00FF"
  display.updateDisplay();
  delay(500);
  clearAllDigits();
  display.setHex("9A6F");
  display.updateDisplay();
  clearAllDigits();
  showBinary(42);
  updateDisplay();
  clearAllleds();
}
