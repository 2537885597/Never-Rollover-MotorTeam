/*
 * MOTRO.c
 *
 *  Created on: 2024��1��23��
 *      Author: A
 */

#include "zf_common_headfile.h"

float SetSpeed1 = 2000;  // �������ٶ�
float SetSpeed2 = 2000;
float ActSpeed1;         // ʵ���ٶ�
float ActSpeed2;
uint32 duty_A=0;   // ����ռ�ձ�
uint32 duty_B=0;   // �ҵ��ռ�ձ�

void motor_init(void)
{
    pwm_init(ATOM0_CH0_P21_2, 17 * 1000, 0);
    pwm_init(ATOM0_CH1_P21_3, 17 * 1000, 0);
    pwm_init(ATOM0_CH2_P21_4, 17 * 1000, 0);
    pwm_init(ATOM0_CH3_P21_5, 17 * 1000, 0);
    ips200_show_string(0, 0, "motor OK");  // �����ʼ���ɹ�
    system_delay_ms(500);  // �ʵ���ʱ����ȷ��ʾ
}

//������ƺ���v1
//void motor_ctrl(uint32 duty_motor1, uint32 duty_motor2)
//{
//    // ʵ������ת
//    if (duty_motor1 >= 0)  // ��ת
//    {
//        pwm_set_duty(ATOM0_CH0_P21_2, duty_motor1);
//        pwm_set_duty(ATOM0_CH1_P21_3, 0);
//    }
//    else    // ��ת
//    {
//        pwm_set_duty(ATOM0_CH0_P21_2, 0);
//        pwm_set_duty(ATOM0_CH1_P21_3, -(duty_motor1));
//    }
//
//    if (duty_motor2 >= 0)  // ��ת
//    {
//        pwm_set_duty(ATOM0_CH2_P21_4, duty_motor2);
//        pwm_set_duty(ATOM0_CH3_P21_5, 0);
//    }
//    else    // ��ת
//    {
//        pwm_set_duty(ATOM0_CH2_P21_4, 0);
//        pwm_set_duty(ATOM0_CH3_P21_5, -(duty_motor2));
//    }
//}

void motor_ctrl_v2(int motor,uint32 duty) //������ƺ���v2
{
    uint8 dir=(duty>0)?1:0;
    switch(motor)
    {
        case motor_l://����
            pwm_set_duty(ATOM0_CH0_P21_2,abs(duty)); //����ռ�ձ�
            gpio_set_level(ATOM0_CH1_P21_3,dir);     //������ת����
            break;
        case motor_r://�ҵ��
            pwm_set_duty(ATOM0_CH2_P21_4,abs(duty)); //�ҵ��ռ�ձ�
            gpio_set_level(ATOM0_CH3_P21_5,dir);     //�ҵ����ת����
            break;
    }
}

void Swing_control(uint32 duty,float error)//���ֿ��ƺ���
{
    uint32 duty_dv=0;//�������
    uint8 ori=(error>=0)?1:0;//���ݲ����жϰڶ�����
    duty_dv=(uint32)(abs(error));
    switch(ori)
    {
        case 1://�����
            duty_A=duty-duty_dv;
            duty_B=duty+duty_dv;
            break;
        case 0://���Ұ�
            duty_A=duty+duty_dv;
            duty_B=duty-duty_dv;
            break;
    }
    motor_ctrl_v2(motor_l,duty_A);//����ռ�ձ�
    motor_ctrl_v2(motor_r,duty_B);//�ҵ��ռ�ձ�
}
