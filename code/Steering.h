/*
 * Steering.h
 *
 *  Created on: 2024��1��24��
 *      Author: A
 */

#ifndef CODE_STEERING_H_
#define CODE_STEERING_H_

// �궨��
#define SERVO_MOTOR_PWM             (ATOM1_CH1_P33_9)       // ���������϶����Ӧ����
#define SERVO_MOTOR_FREQ            (50)                    // ���������϶��Ƶ��  �����ע�ⷶΧ
#define SERVO_MOTOR_MID             (80)                    //��ֵ75//����ͨ���޸���ֵ�ķ�ʽ�ֲ���е���79
#define SERVO_MOTOR_LMAX            (55)                    //�����60
#define SERVO_MOTOR_RMAX            (105)                   //�Ҵ���100
// ------------------ ���ռ�ձȼ��㷽ʽ ------------------
#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))


// ��������
void Steering_init(void);
void Steering_set(int angle);


// ��������
extern int angle;
extern int direction;
extern uint32 duty_steer;


#endif /* CODE_STEERING_H_ */
