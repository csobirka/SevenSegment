// SevenSegment.cpp - Implementation file
#include "SevenSegment.h"

const int SevenSegment::digitCodes[16] = {
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
    0b01110111, // A (10)
    0b01111100, // B (11)
    0b00111001, // C (12)
    0b01011110, // D (13)
    0b01111001, // E (14)
    0b01110001  // F (15)
};

SevenSegment::SevenSegment(const int *segmentPins, const int *digitPins, int ledPin)
    : segmentPins(segmentPins), digitPins(digitPins), ledPin(ledPin), currentDigit(0), number(0) {
    for (int i = 0; i < 4; i++) {
        letters[i] = ' '; // Initialize letters array with spaces
        digits[i] = 0;   // Initialize digits array with zeros
    }
}

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
    extractDigits(); // Extract individual digits from the number
}

void SevenSegment::displayHexNumber(const char *hexNumber) {
    for (int i = 0; i < 4; i++) {
        letters[i] = hexNumber[i]; // Store the hex characters
    }
    number = -1; // Indicate that we are displaying hex characters
}

void SevenSegment::displayDecimalAsHex(int decimalNumber) {
    char hexOutput[5]; // 4 characters + null terminator
    decimalToHex(decimalNumber, hexOutput); // Convert decimal to hex
    displayHexNumber(hexOutput); // Display the hex value
}

void SevenSegment::updateDisplay() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(digitPins[i], i == currentDigit ? LOW : HIGH);
    }

    if (number >= 0 && number <= 9999) {
        // Display a 4-digit number
        setDigit(digits[currentDigit]);
    } else {
        // Display letters or hex characters
        setLetter(letters[currentDigit]);
    }

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

void SevenSegment::setLetter(char letter) {
    int code = 0;
    switch (letter) {
        case '0': code = digitCodes[0]; break;
        case '1': code = digitCodes[1]; break;
        case '2': code = digitCodes[2]; break;
        case '3': code = digitCodes[3]; break;
        case '4': code = digitCodes[4]; break;
        case '5': code = digitCodes[5]; break;
        case '6': code = digitCodes[6]; break;
        case '7': code = digitCodes[7]; break;
        case '8': code = digitCodes[8]; break;
        case '9': code = digitCodes[9]; break;
        case 'A': case 'a': code = digitCodes[10]; break;
        case 'B': case 'b': code = digitCodes[11]; break;
        case 'C': case 'c': code = digitCodes[12]; break;
        case 'D': case 'd': code = digitCodes[13]; break;
        case 'E': case 'e': code = digitCodes[14]; break;
        case 'F': case 'f': code = digitCodes[15]; break;
        default: code = 0; break; // Blank for unknown characters
    }
    for (int i = 0; i < 7; i++) {
        digitalWrite(segmentPins[i], (code >> i) & 0x01);
    }
}

void SevenSegment::decimalToHex(int decimal, char *hexOutput) {
    // Convert decimal to 4-digit hexadecimal
    for (int i = 3; i >= 0; i--) {
        int remainder = decimal % 16;
        if (remainder < 10) {
            hexOutput[i] = '0' + remainder;
        } else {
            hexOutput[i] = 'A' + (remainder - 10);
        }
        decimal /= 16;
    }
    hexOutput[4] = '\0'; // Null-terminate the string
}

void SevenSegment::extractDigits() {
    digits[0] = number / 1000;        // Thousands place
    digits[1] = (number / 100) % 10; // Hundreds place
    digits[2] = (number / 10) % 10;  // Tens place
    digits[3] = number % 10;         // Ones place
}