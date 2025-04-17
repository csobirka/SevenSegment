#include "SevenSegment.h"

SevenSegment::SevenSegment(const int segmentPins[], const int digitPins[], int led_en) {
    _segmentPins = segmentPins;
    _digitPins = digitPins;
    _led_en = led_en;
    
    // Initialize all segment pins
    for (int i = 0; i < 8; i++) {
        pinMode(_segmentPins[i], OUTPUT);
        digitalWrite(_segmentPins[i], LOW);
    }
    
    // Initialize all digit pins
    for (int i = 0; i < 4; i++) {
        pinMode(_digitPins[i], OUTPUT);
        digitalWrite(_digitPins[i], HIGH); // Start with all digits off
    }
    
    pinMode(_led_en, OUTPUT);
    digitalWrite(_led_en, 1); // Disable LED row
    
    // Initialize display state
    for (int i = 0; i < 4; i++) {
        _currentDisplay[i] = ' ';
        _decimalPoint[i] = false;
    }
    _showBinaryFlag = false;
    _binaryValue = 0;
}

void SevenSegment::clearAllDigits() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(_digitPins[i], HIGH);
    }
    digitalWrite(_led_en, 1);
    delay(1);
}

void SevenSegment::clearAllLeds() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(_digitPins[i], HIGH);
    }
    digitalWrite(_led_en, 0);
    delay(2);
}

void SevenSegment::updateDisplay() {
    if (_showBinaryFlag) {
        // Binary display mode
        clearAllDigits();
        for (int i = 0; i < 8; i++) {
            digitalWrite(_segmentPins[i], (_binaryValue >> i) & 0x01);
        }
    } else {
        // Normal 7-segment display mode
        for (int digit = 0; digit < 4; digit++) {
            // Turn off all digits first
            clearAllDigits();
            
            // Get current character
            char c = _currentDisplay[digit];
            byte pattern = 0;
            
            // Determine pattern
            if (c >= '0' && c <= '9') pattern = _digitPatterns[c - '0'];
            else if (c >= 'A' && c <= 'F') pattern = _digitPatterns[c - 'A' + 10];
            else if (c >= 'a' && c <= 'f') pattern = _digitPatterns[c - 'a' + 10];
            else if (c == '-') pattern = 0b01000000;
            
            // Set segments (including decimal point if needed)
            for (int i = 0; i < 7; i++) {
                digitalWrite(_segmentPins[i], (pattern >> i) & 0x01);
            }
            // Set decimal point
            digitalWrite(_segmentPins[7], _decimalPoint[digit] ? HIGH : LOW);
            
            // Turn on only this digit
            digitalWrite(_digitPins[digit], LOW);
            
            // Display for 2ms (adjust as needed)
            delay(2);
        }
    }
}

void SevenSegment::setDecimal(int number, int pointPosition) {
    _showBinaryFlag = false;
    bool isNegative = number < 0;
    number = abs(number);
    
    // Reset all decimal points
    for (int i = 0; i < 4; i++) {
        _decimalPoint[i] = false;
    }
    
    // Set decimal point if specified (1-4)
    if (pointPosition >= 1 && pointPosition <= 4) {
        _decimalPoint[pointPosition - 1] = true;
    }
    
    for (int i = 3; i >= 0; i--) {
        if (number > 0 || i == 3) {
            _currentDisplay[i] = '0' + (number % 10);
            number /= 10;
        } else if (i == 0 && isNegative) {
            _currentDisplay[i] = '-';
        } else {
            _currentDisplay[i] = ' ';
        }
    }
}

void SevenSegment::setDecimalAsHex(int decimal) {
    _showBinaryFlag = false;
    for (int i = 0; i < 4; i++) {
        _decimalPoint[i] = false; // Reset decimal points
    }
    for (int i = 3; i >= 0; i--) {
        int remainder = decimal % 16;
        if (remainder < 10) {
            _currentDisplay[i] = '0' + remainder;
        } else {
            _currentDisplay[i] = 'A' + (remainder - 10);
        }
        decimal /= 16;
    }
}

void SevenSegment::setHex(const char *hexNumber) {
    _showBinaryFlag = false;
    for (int i = 0; i < 4; i++) {
        _decimalPoint[i] = false; // Reset decimal points
        _currentDisplay[i] = hexNumber[i];
    }
}

void SevenSegment::showBinary(int value) {
    _showBinaryFlag = true;
    _binaryValue = value;
}

// Add this new function implementation
void SevenSegment::writeToDigit(int number, int digit, int pointPosition) {
    _showBinaryFlag = false;
    
    // Reset all decimal points
    for (int i = 0; i < 4; i++) {
        _decimalPoint[i] = false;
    }
    
    // Set decimal point if specified (1-4)
    if (pointPosition >= 1 && pointPosition <= 4) {
        _decimalPoint[pointPosition - 1] = true;
    }
    
    // Validate digit position
    if (digit < 1 || digit > 4) return;
    
    // Determine pattern
    byte pattern = 0;
    if (number >= 0 && number <= 15) {
        pattern = _digitPatterns[number];
    } else if (number == '-') {
        pattern = 0b01000000;
    }
    
    // Update the current display array
    if (number >= 0 && number <= 9) {
        _currentDisplay[digit-1] = '0' + number;
    } else if (number >= 10 && number <= 15) {
        _currentDisplay[digit-1] = 'A' + (number - 10);
    } else if (number == '-') {
        _currentDisplay[digit-1] = '-';
    }
    
    // Set decimal point for this digit
    _decimalPoint[digit-1] = (pointPosition == digit);
}