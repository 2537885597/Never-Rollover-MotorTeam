/*
 * MOTOR.h
 *
 *  Created on: 2024��1��24��
 *      Author: A
 */

#ifndef CODE_MOTOR_H_
#define CODE_MOTOR_H_


// �궨��
#define motor_l    0
#define motor_r    1

//��������
void motor_init(void);
void motor_ctrl(uint32 duty_motor1, uint32 duty_motor2);
void motor_ctrl_v2(int motor,uint32 duty);

//ȫ�ֱ���
extern float SetSpeed1;
extern float SetSpeed2;
extern float ActSpeed1;
extern float ActSpeed2;
extern uint32 duty_A;
extern uint32 duty_B;



#endif /* CODE_MOTOR_H_ */
