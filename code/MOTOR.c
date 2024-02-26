/*
 * MOTRO.c
 *
 *  Created on: 2024年1月23日
 *      Author: A
 */

#include "zf_common_headfile.h"

float SetSpeed1 = 2000;  // 期望的速度
float SetSpeed2 = 2000;
float ActSpeed1;         // 实际速度
float ActSpeed2;
uint32 duty_A=0;   // 左电机占空比
uint32 duty_B=0;   // 右电机占空比

void motor_init(void)
{
    pwm_init(ATOM0_CH0_P21_2, 17 * 1000, 0);
    pwm_init(ATOM0_CH1_P21_3, 17 * 1000, 0);
    pwm_init(ATOM0_CH2_P21_4, 17 * 1000, 0);
    pwm_init(ATOM0_CH3_P21_5, 17 * 1000, 0);
    ips200_show_string(0, 0, "motor OK");  // 电机初始化成功
    system_delay_ms(500);  // 适当延时以正确显示
}

//电机控制函数v1
//void motor_ctrl(uint32 duty_motor1, uint32 duty_motor2)
//{
//    // 实现正反转
//    if (duty_motor1 >= 0)  // 正转
//    {
//        pwm_set_duty(ATOM0_CH0_P21_2, duty_motor1);
//        pwm_set_duty(ATOM0_CH1_P21_3, 0);
//    }
//    else    // 反转
//    {
//        pwm_set_duty(ATOM0_CH0_P21_2, 0);
//        pwm_set_duty(ATOM0_CH1_P21_3, -(duty_motor1));
//    }
//
//    if (duty_motor2 >= 0)  // 正转
//    {
//        pwm_set_duty(ATOM0_CH2_P21_4, duty_motor2);
//        pwm_set_duty(ATOM0_CH3_P21_5, 0);
//    }
//    else    // 反转
//    {
//        pwm_set_duty(ATOM0_CH2_P21_4, 0);
//        pwm_set_duty(ATOM0_CH3_P21_5, -(duty_motor2));
//    }
//}

void motor_ctrl_v2(int motor,uint32 duty) //电机控制函数v2
{
    uint8 dir=(duty>0)?1:0;
    switch(motor)
    {
        case motor_l://左电机
            pwm_set_duty(ATOM0_CH0_P21_2,abs(duty)); //左电机占空比
            gpio_set_level(ATOM0_CH1_P21_3,dir);     //左电机旋转方向
            break;
        case motor_r://右电机
            pwm_set_duty(ATOM0_CH2_P21_4,abs(duty)); //右电机占空比
            gpio_set_level(ATOM0_CH3_P21_5,dir);     //右电机旋转方向
            break;
    }
}

void Swing_control(uint32 duty,float error)//后轮控制函数
{
    uint32 duty_dv=0;//电机差速
    uint8 ori=(error>=0)?1:0;//根据差速判断摆动方向
    duty_dv=(uint32)(abs(error));
    switch(ori)
    {
        case 1://向左摆
            duty_A=duty-duty_dv;
            duty_B=duty+duty_dv;
            break;
        case 0://向右摆
            duty_A=duty+duty_dv;
            duty_B=duty-duty_dv;
            break;
    }
    motor_ctrl_v2(motor_l,duty_A);//左电机占空比
    motor_ctrl_v2(motor_r,duty_B);//右电机占空比
}
