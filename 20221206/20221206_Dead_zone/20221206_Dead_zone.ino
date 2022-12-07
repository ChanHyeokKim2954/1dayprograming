#include <MsTimer2.h>
#define encodPinA1      2 
#define encodPinB1      3                       // Quadrature encoder B pin
#define DIR 4
#define PWM 5
volatile int32_t encoderPos = 0;
int pwm = 0, Dead_zone_pwm = 0, pwm_old = 0;

void encoder_read()  
{
  delayMicroseconds(5);
  if(digitalRead(encodPinB1)==LOW)    encoderPos++;           
  else                                 encoderPos--; 
}
void interrupt_setup(void)
{
  pinMode(encodPinA1, INPUT_PULLUP); 
  pinMode(encodPinB1, INPUT_PULLUP);  
  attachInterrupt(0, encoder_read, RISING);  
}

void timer()
{
  static boolean output = HIGH;

  output = !output;
  (fabs(encoderPos) <= 1) ? Dead_zone_pwm = pwm : Dead_zone_pwm = 0;
  pwm ++;
  //motor_control(1,pwm); //forward
  motor_control(-1,pwm); //backward
}

void motor_control(int Direction, int pwm)
{
  pwm = (pwm>=255) ? 255 : pwm;
  switch(Direction)
  {
    case 1:
      digitalWrite(DIR,HIGH);
      analogWrite(PWM,pwm);
      break;
      
    case 0:
      digitalWrite(DIR,LOW);
      analogWrite(PWM,0);
      break;
      
    case -1:
      digitalWrite(DIR,LOW);
      analogWrite(PWM,pwm);  
      break;  
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(DIR,OUTPUT);
  pinMode(PWM,OUTPUT);
  MsTimer2::set(50, timer); // 500ms period
  MsTimer2::start();
  interrupt_setup();
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(fabs(encoderPos) < 1){
    Serial.print("PWM : ");
    Serial.print(pwm);
    Serial.print("    ");
    Serial.print("Dead_Zone : ");
    Serial.print(Dead_zone_pwm);
    Serial.print("    ");
    Serial.print("encoderPos : ");
    Serial.println(encoderPos);
  }
 else pwm = 40;
}
