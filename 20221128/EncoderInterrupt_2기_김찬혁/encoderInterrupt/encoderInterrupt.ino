#include <MsTimer2.h>

#define encoderPinA 2
#define encoderPinB 3

int count = 0;

void encoder()
{
  delayMicroseconds(100);
  if(digitalRead(encoderPinB) == LOW) count++;
  else                                count--;
}
void encoderInterrupt()
{
   attachInterrupt(digitalPinToInterrupt(encoderPinA), encoder, RISING);
}
void setup() {
  Serial.begin(115200);
  pinMode(encoderPinA,INPUT_PULLUP);
  pinMode(encoderPinB,INPUT_PULLUP);
  MsTimer2::set(100,encoderInterrupt);
  MsTimer2::start();
}

void loop() {
  Serial.print("encoder : ");
  Serial.println(count);
  
}
