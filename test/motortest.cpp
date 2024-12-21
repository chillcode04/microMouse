#include <Arduino.h>
#define in1 4
#define in2 16
#define in3 18
#define in4 19
void setup()
{
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(2, OUTPUT);
}
void loop () {
    // digitalWrite(in1, LOW);
    // digitalWrite(in2, HIGH);
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    delay(1000);
}