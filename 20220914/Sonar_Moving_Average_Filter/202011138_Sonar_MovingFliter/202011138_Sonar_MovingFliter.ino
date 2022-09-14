#include <NewPing.h>
#define MAX_DISTANCE 180
#define MASK_SIZE 5
#define TRIG 8
#define ECHO 9

NewPing sonar(TRIG , ECHO, MAX_DISTANCE);

double mask_array[MASK_SIZE+1] = {0.0, };
double calculation = 0.0;
int count = 0;

double MovingAverage(int mask)
{
  double sum = 0.0;
  for (int i = 0; i < mask ; i++) sum += mask_array[i];
  
  return sum / (double)mask;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Sonar,Filter");
}

void loop() {
  mask_array[count] = sonar.ping_cm();
  if (count < MASK_SIZE) {
     calculation = MovingAverage(MASK_SIZE);
  }
  else {
    for (int i = 0; i < MASK_SIZE; i++)  mask_array[i] = mask_array[i + 1];
    calculation = MovingAverage(MASK_SIZE);
    count = MASK_SIZE - 1;
  }
  count++;
  Serial.print(sonar.ping_cm());
  Serial.print(",");
  Serial.println(calculation);
  delay(200);
}
