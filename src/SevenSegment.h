// SevenSegment.h - Header file
#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H

#include <Arduino.h>

class SevenSegment {
public:
    SevenSegment(const int *segmentPins, const int *digitPins, int ledPin);
    void begin();
    void displayNumber(int number); // Display a 4-digit decimal number (0-9999)
    void displayHexNumber(const char *hexNumber); // Display a 4-character hex number (e.g., "9A6F")
    void displayDecimalAsHex(int decimalNumber); // Convert decimal to hex and display it
    void updateDisplay();

private:
    const int *segmentPins;
    const int *digitPins;
    int ledPin;
    int currentDigit;
    int number;
    char letters[4];
    int digits[4]; // Array to store individual digits of the number

    static const int digitCodes[16]; // 0-9 and A-F
    void setDigit(int digit);
    void setLetter(char letter);
    void clearDisplay();
    void decimalToHex(int decimal, char *hexOutput); // Helper function to convert decimal to hex
    void extractDigits(); // Helper function to extract digits from the number
};

#endif // SEVENSEGMENT_H