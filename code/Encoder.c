/*
 * Encoder.c
 *
 *  Created on: 2024年1月25日
 *      Author: A
 */

# include "zf_common_headfile.h"

int16 speed1;
int16 speed2;

// 编码器初始化
void Encoder_init(void)
{
    encoder_quad_init(TIM2_ENCODER, TIM2_ENCODER_CH1_P33_7, TIM2_ENCODER_CH2_P33_6);  // 编码器3初始化
    encoder_quad_init(TIM4_ENCODER, TIM4_ENCODER_CH1_P02_8, TIM4_ENCODER_CH2_P00_9);  // 编码器4初始化
    ips200_show_string(0, 0, "Encoder OK");  // 编码器初始化成功
    system_delay_ms(500);  // 适当延时以正确显示
}

// 编码器获取速度数据
void Encoder_getv(void)
{
    speed1 = encoder_get_count(TIM2_ENCODER);   // 获取编码器3的数据
    speed2 = encoder_get_count(TIM4_ENCODER);   // 获取编码器4的数据

    encoder_clear_count(TIM2_ENCODER);          // 编码器3计数清除
    encoder_clear_count(TIM4_ENCODER);          // 编码器4计数清除

    ips200_show_int(0, 1, speed1, 10);          // 液晶显示32位有符号数
    ips200_show_int(0, 2, speed2, 10);          // 液晶显示32位有符号数

    system_delay_ms(100); // 适当延时以正确显示
}


