#include <MsTimer2.h>
#define encodPinA1      2 
#define encodPinB1      3                       // Quadrature encoder B pin
#define check_pin       11
#define DIR 4
#define PWM 5
volatile int32_t encoderPos = 0;
volatile int32_t encoderPos_old = 0;
int32_t target_Pos = 0;
int32_t pos_error = 0;
int32_t pos_error_d = 0;
int32_t pos_error_old = 0;

float P = 0.4;
float Pd = 1.0;
float Pi = 0.5;

int pid_pwm = 0;
float pos_error_sum = 0;

#if ARDUINO >= 100
const int led_pin = LED_BUILTIN;   // 1.0 built in LED pin var
#else
const int led_pin = 13;         // default to pin 13
#endif

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
  digitalWrite(check_pin, HIGH);
  digitalWrite(led_pin, output);
  //interrupt 실행 debuging
  output = !output;

  pos_error = target_Pos - encoderPos;
  pos_error_d = pos_error - pos_error_old;
  pos_error_sum += pos_error;
  pos_error_sum = (pos_error_sum > 50) ? 50 : pos_error_sum;
  pos_error_sum = (pos_error_sum < -50) ? -50 : pos_error_sum;
  pid_pwm = (P * pos_error) + (Pd * pos_error_d) + (Pi * pos_error_sum); 
  //pid_pwm = (pid_pwm>=255) ? 255 : pid_pwm;
  pid_pwm = Feedforward(pid_pwm,pos_error,0.1);
  
  if(fabs(pos_error)<=2) pos_error_sum = 0; 
  if(pid_pwm > 0) motor_control(1,pid_pwm);
  else if(pid_pwm <= 0) motor_control(-1,-pid_pwm);
  encoderPos_old = encoderPos;
  pos_error_old = pos_error;
  digitalWrite(check_pin, LOW); //항상 시작과 끝에 있어야됨
}

int Feedforward(int pwm,int32_t error_pos, double percent)
{
  pwm = (error_pos >= (double)target_Pos * percent) ? 255 : pwm;
  return pwm;
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

void setup()
{
  pinMode(led_pin, OUTPUT);
  pinMode(check_pin, OUTPUT);
  pinMode(DIR,OUTPUT);
  pinMode(PWM,OUTPUT);
  MsTimer2::set(50, timer); // 500ms period
  MsTimer2::start();
  interrupt_setup();
  Serial.begin(115200);
  Serial.println("Pos,pos_error,pwm");
  target_Pos = 1500;
}

void loop()
{
  if(fabs(pid_pwm) >= 0){
    Serial.print(encoderPos);
    Serial.print(", ");
    Serial.print(pos_error);
    Serial.print(", ");
    Serial.print(pid_pwm);
    Serial.print(", ");
    Serial.println(pos_error_sum);
  }
}
