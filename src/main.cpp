#include "Arduino.h"
#include <WString.h>

#define OPDRACHT 15
#define SEPERATOR Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

#if OPDRACHT == 8
int pins[] = {8,9,10,11,12,13};
#endif

#if OPDRACHT == 15
int pins[] = {8,9,10,11,12,13};
#endif
#if OPDRACHT == 16
int pins [] = {8,9,10,11,12,13};

int currLED = 0;
bool sub;
#endif

void setup()
{
    Serial.begin(9600);

#if OPDRACHT == TEST
   
 
    SEPERATOR
    String test = "Hello";
    test += " test";
    test += " sdsdas";
    test += " sdffgd";
    Serial.println(test);

    SEPERATOR

#endif
#if OPDRACHT == 7
    Serial.begin(9600);
 
    SEPERATOR
    Serial.println("A");
    Serial.println(M_PI * sq(4));
    SEPERATOR
    
    SEPERATOR
    Serial.println("B");
    for(int i = 1; i <= 10; i++){
        Serial.println(M_PI * sq(i));
    }
    SEPERATOR

    SEPERATOR
    Serial.println("C");
    Serial.println(sqrt(sq(6 - 3) + sq(8 - 4) + sq(4 - 2)));
    SEPERATOR
#endif

#if OPDRACHT == 8
    for (int i = 0; i < (sizeof(pins) / sizeof(pins[0])); i++){
      pinMode(pins[i], OUTPUT);
    }
#endif

#if OPDRACHT == 10
     pinMode(11, OUTPUT);
#endif

#if OPDRACHT == 16 || OPDRACHT == 15
DDRB = 0x3f;
#endif
}

void loop()
{
#if OPDRACHT == 8
    for (int i = 0; i < (sizeof(pins) / sizeof(pins[0])); i++){
        digitalWrite(pins[i], HIGH);
        delay(100);
        digitalWrite(pins[i], LOW);
        delay(100);
    }
    PORTB = 0x3F;
    delay(1000);
    PORTB = 0x0;
    delay(1000);
#endif


#if OPDRACHT == 10
    for (int i = 0; i < 255; i++){
        analogWrite(11, i);
        Serial.println(i);
        delay(10);
    }
    delay(1000);
#endif

#if OPDRACHT == 11
    Serial.println(analogRead(A0));          // debug value
    delay(100);
#endif


#if OPDRACHT == 15
  PORTB = B00000000;
  for (int i = 0; i < (analogRead(A0) / 113); i++){
    digitalWrite(pins[i], HIGH);
  }
#endif


#if OPDRACHT == 16
  if(sub)
    currLED--;
  else
    currLED++;

  PORTB = B00000000;
  digitalWrite(pins[currLED] , HIGH);
  
  if(currLED >= 5)
    sub = true;
  if(currLED <= 0)
    sub = false;
  
  delay(100);
#endif
}