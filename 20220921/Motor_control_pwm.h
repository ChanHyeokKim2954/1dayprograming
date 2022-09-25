
#ifndef MOTOR_CONTROL_PWM_H_
#define MOTOR_CONTROL_PWM_H_

//CC6_PWM_Capture
void init_CCU6_ICU(void);                       /* Function to configure the CCU6                                   */
void init_PWM_signal_generation(void);          /* Function to configure the port pin for PWM generation            */
int generate_PWM_signal(int);
void DCmotor(int);
int PWM_map(int, int, int, int, int);

#endif /* MOTOR_CONTROL_PWM_H_ */
