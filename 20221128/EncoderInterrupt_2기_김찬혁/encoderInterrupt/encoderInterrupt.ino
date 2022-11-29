#include <MsTimer2.h>

#define encoderA 2
#define encoderB 3

static volatile int32_t count = 0;

void setup() {
  Serial.begin(115200);
  MsTimer2::set(100,encoderInterrupt);
  MsTimer2::start();
}
void encoder()
{
  delayMicroseconds(10);
  if(digitalRead(encoderB) == LOW) count++;
  else                                count--;
}
void encoderInterrupt()
{
  pinMode(encoderA,INPUT_PULLUP);
  pinMode(encoderB,INPUT_PULLUP);
  attachInterrupt(0, encoder, RISING);
}
void loop() {
  Serial.print("encoder : ");
  Serial.println(count);
}
