#ifndef SevenSegment_h
#define SevenSegment_h

#include "Arduino.h"

class SevenSegment {
public:
    // Constructor
    SevenSegment(const int segmentPins[], const int digitPins[], int led_en);

    // Display control functions
    void updateDisplay();
    void clearAllDigits();
    void clearAllLeds();

    // Display modes
    void setDecimal(int number, int pointPosition = 0);
    void setDecimalAsHex(int decimal);
    void setHex(const char *hexNumber);
    void showBinary(int value);
    void writeToDigit(int number, int digit, int pointPosition = 0); // New function

private:
    const int *_segmentPins;
    const int *_digitPins;
    int _led_en;
    char _currentDisplay[4];
    bool _showBinaryFlag;
    int _binaryValue;
    bool _decimalPoint[4];
    
    // Segment patterns
    const byte _digitPatterns[16] = {
        0b00111111, // 0
        0b00000110, // 1
        0b01011011, // 2
        0b01001111, // 3
        0b01100110, // 4
        0b01101101, // 5
        0b01111101, // 6
        0b00000111, // 7
        0b01111111, // 8
        0b01101111, // 9
        0b01110111, // A
        0b01111100, // B
        0b00111001, // C
        0b01011110, // D
        0b01111001, // E
        0b01110001  // F
    };
};

#endif