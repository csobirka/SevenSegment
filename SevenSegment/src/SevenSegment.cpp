// SevenSegment.cpp - Implementation file
#include "SevenSegment.h"

const int SevenSegment::digitCodes[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

SevenSegment::SevenSegment(const int *segmentPins, const int *digitPins, int ledPin)
    : segmentPins(segmentPins), digitPins(digitPins), ledPin(ledPin), currentDigit(0), number(0) {}

void SevenSegment::begin() {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);

    for (int i = 0; i < 7; i++) {
        pinMode(segmentPins[i], OUTPUT);
    }

    for (int i = 0; i < 4; i++) {
        pinMode(digitPins[i], OUTPUT);
        digitalWrite(digitPins[i], LOW);
    }
}

void SevenSegment::displayNumber(int number) {
    this->number = number;
    extractDigits();
}

void SevenSegment::extractDigits() {
    digits[0] = number / 1000;      // Thousands place
    digits[1] = (number / 100) % 10; // Hundreds place
    digits[2] = (number / 10) % 10;  // Tens place
    digits[3] = number % 10;         // Ones place
}

void SevenSegment::updateDisplay() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(digitPins[i], i == currentDigit ? LOW : HIGH);
    }

    setDigit(digits[currentDigit]);

     currentDigit++;
    if (currentDigit > 3) {
      currentDigit = 0; // Wrap around to the first display
    }
}

void SevenSegment::setDigit(int digit) {
    for (int i = 0; i < 7; i++) {
        digitalWrite(segmentPins[i], (digitCodes[digit] >> i) & 0x01);
    }
}