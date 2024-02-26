/*
 * MOTOR.h
 *
 *  Created on: 2024年1月24日
 *      Author: A
 */

#ifndef CODE_MOTOR_H_
#define CODE_MOTOR_H_


// 宏定义
#define motor_l    0
#define motor_r    1

//函数声明
void motor_init(void);
void motor_ctrl(uint32 duty_motor1, uint32 duty_motor2);
void motor_ctrl_v2(int motor,uint32 duty);

//全局变量
extern float SetSpeed1;
extern float SetSpeed2;
extern float ActSpeed1;
extern float ActSpeed2;
extern uint32 duty_A;
extern uint32 duty_B;



#endif /* CODE_MOTOR_H_ */
