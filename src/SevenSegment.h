#ifndef SevenSegment_h
#define SevenSegment_h

#include <Arduino.h>

class SevenSegment {
public:
    SevenSegment(const uint8_t* segmentPins, const uint8_t* digitPins, uint8_t ledEnPin);
    void begin();
    void setDecimal(int number);
    void setDecimalAsHex(int decimal);
    void setHex(const char* hexNumber);
    void showBinary(int value);
    void updateDisplay();

private:
    const uint8_t* _segmentPins;
    const uint8_t* _digitPins;
    uint8_t _ledEnPin;
    char _currentDisplay[4];
    bool _showBinaryFlag;
    int _binaryValue;
    unsigned long _lastUpdateTime;
    uint8_t _currentDigit;

    void clearDigits();
    byte getPattern(char c);
};

#endif