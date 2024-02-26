/*
 * Steering.h
 *
 *  Created on: 2024年1月24日
 *      Author: A
 */

#ifndef CODE_STEERING_H_
#define CODE_STEERING_H_

// 宏定义
#define SERVO_MOTOR_PWM             (ATOM1_CH1_P33_9)       // 定义主板上舵机对应引脚
#define SERVO_MOTOR_FREQ            (50)                    // 定义主板上舵机频率  请务必注意范围
#define SERVO_MOTOR_MID             (80)                    //中值75//可以通过修改中值的方式弥补机械误差79
#define SERVO_MOTOR_LMAX            (55)                    //左打死60
#define SERVO_MOTOR_RMAX            (105)                   //右打死100
// ------------------ 舵机占空比计算方式 ------------------
#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))


// 函数声明
void Steering_init(void);
void Steering_set(int angle);


// 变量声明
extern int angle;
extern int direction;
extern uint32 duty_steer;


#endif /* CODE_STEERING_H_ */
