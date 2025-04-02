#include "SevenSegment.h"

const byte digitPatterns[16] = {
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

SevenSegment::SevenSegment(const uint8_t* segmentPins, const uint8_t* digitPins, uint8_t ledEnPin) {
    _segmentPins = segmentPins;
    _digitPins = digitPins;
    _ledEnPin = ledEnPin;
    _showBinaryFlag = false;
    _currentDigit = 0;
    _lastUpdateTime = 0;
}

void SevenSegment::begin() {
    for (int i = 0; i < 8; i++) {
        pinMode(_segmentPins[i], OUTPUT);
        digitalWrite(_segmentPins[i], LOW);
    }
    for (int i = 0; i < 4; i++) {
        pinMode(_digitPins[i], OUTPUT);
        digitalWrite(_digitPins[i], HIGH);
    }
    pinMode(_ledEnPin, OUTPUT);
    digitalWrite(_ledEnPin, HIGH);
}

void SevenSegment::clearDigits() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(_digitPins[i], HIGH);
    }
}

byte SevenSegment::getPattern(char c) {
    if (c >= '0' && c <= '9') return digitPatterns[c - '0'];
    if (c >= 'A' && c <= 'F') return digitPatterns[c - 'A' + 10];
    if (c >= 'a' && c <= 'f') return digitPatterns[c - 'a' + 10];
    if (c == '-') return 0b01000000;
    return 0;
}

void SevenSegment::setDecimal(int number) {
    _showBinaryFlag = false;
    bool isNegative = number < 0;
    number = abs(number);

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

void SevenSegment::setHex(const char* hexNumber) {
    _showBinaryFlag = false;
    for (int i = 0; i < 4; i++) {
        _currentDisplay[i] = hexNumber[i];
    }
}

void SevenSegment::showBinary(int value) {
    _showBinaryFlag = true;
    _binaryValue = value;
}

void SevenSegment::updateDisplay() {
    if (millis() - _lastUpdateTime < 2) return;
    _lastUpdateTime = millis();

    clearDigits();

    if (_showBinaryFlag) {
        digitalWrite(_ledEnPin, LOW);
        for (int i = 0; i < 8; i++) {
            digitalWrite(_segmentPins[i], (_binaryValue >> i) & 0x01);
        }
    } else {
        digitalWrite(_ledEnPin, HIGH);
        char c = _currentDisplay[_currentDigit];
        byte pattern = getPattern(c);

        for (int i = 0; i < 7; i++) {
            digitalWrite(_segmentPins[i], (pattern >> i) & 0x01);
        }
        digitalWrite(_digitPins[_currentDigit], LOW);
        _currentDigit = (_currentDigit + 1) % 4;
    }
}