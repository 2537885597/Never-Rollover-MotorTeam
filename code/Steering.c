/*
 * Steering.c
 *
 *  Created on: 2024年1月24日
 *      Author: A
 */

# include "zf_common_headfile.h"

int angle;
int direction;
uint32 duty_steer = 1000;

void Steering_init(void)
{
    pwm_init(ATOM0_CH1_P33_9, SERVO_MOTOR_FREQ,(uint32)SERVO_MOTOR_DUTY(SERVO_MOTOR_MID));   // PWM初始化
    ips200_show_string(0, 0, "steer OK"); // 屏幕显示字符串 测试屏幕
    system_delay_ms(500);  // 适当延时以正确显示

}

void Steering_set(int angle)//舵机驱动
{
    // 限制转动角度
    if(angle<SERVO_MOTOR_LMAX){
        angle=SERVO_MOTOR_LMAX;
        direction = 1;
    }
    if(angle>SERVO_MOTOR_RMAX){
        angle=SERVO_MOTOR_RMAX;
        direction = -1;
    }
    // 设置占空比
    pwm_set_duty(ATOM0_CH1_P33_9, (uint32)SERVO_MOTOR_DUTY(angle));
}




