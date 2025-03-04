// SevenSegment.h - Header file
#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H

#include <Arduino.h>

class SevenSegment {
public:
    SevenSegment(const int *segmentPins, const int *digitPins, int ledPin);
    void begin();
    void displayNumber(int number);
    void updateDisplay();

private:
    const int *segmentPins;
    const int *digitPins;
    int ledPin;
    int currentDigit;
    int number;
    int digits[4];

    static const int digitCodes[10];
    void setDigit(int digit);
    void extractDigits();
};

#endif // SEVENSEGMENT_H
