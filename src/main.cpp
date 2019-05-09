/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13

int st_pins [3] = { 13, 12, 11 };

void setup()
{
    // initialize LED digital pin as an output.
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
}

void loop()
{
    digitalWrite(11, HIGH);
    digitalWrite(13, LOW);
    delay(2000);

    digitalWrite(11, LOW);  
    digitalWrite(12, HIGH);
    delay(1000);

    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    delay(2000);

    digitalWrite(12, HIGH);
    delay(1000);

    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    delay(2000);
}