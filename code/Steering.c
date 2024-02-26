/*
 * Steering.c
 *
 *  Created on: 2024��1��24��
 *      Author: A
 */

# include "zf_common_headfile.h"

int angle;
int direction;
uint32 duty_steer = 1000;

void Steering_init(void)
{
    pwm_init(ATOM0_CH1_P33_9, SERVO_MOTOR_FREQ,(uint32)SERVO_MOTOR_DUTY(SERVO_MOTOR_MID));   // PWM��ʼ��
    ips200_show_string(0, 0, "steer OK"); // ��Ļ��ʾ�ַ��� ������Ļ
    system_delay_ms(500);  // �ʵ���ʱ����ȷ��ʾ

}

void Steering_set(int angle)//�������
{
    // ����ת���Ƕ�
    if(angle<SERVO_MOTOR_LMAX){
        angle=SERVO_MOTOR_LMAX;
        direction = 1;
    }
    if(angle>SERVO_MOTOR_RMAX){
        angle=SERVO_MOTOR_RMAX;
        direction = -1;
    }
    // ����ռ�ձ�
    pwm_set_duty(ATOM0_CH1_P33_9, (uint32)SERVO_MOTOR_DUTY(angle));
}




