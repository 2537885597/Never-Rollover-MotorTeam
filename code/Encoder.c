/*
 * Encoder.c
 *
 *  Created on: 2024��1��25��
 *      Author: A
 */

# include "zf_common_headfile.h"

int16 speed1;
int16 speed2;

// ��������ʼ��
void Encoder_init(void)
{
    encoder_quad_init(TIM2_ENCODER, TIM2_ENCODER_CH1_P33_7, TIM2_ENCODER_CH2_P33_6);  // ������3��ʼ��
    encoder_quad_init(TIM4_ENCODER, TIM4_ENCODER_CH1_P02_8, TIM4_ENCODER_CH2_P00_9);  // ������4��ʼ��
    ips200_show_string(0, 0, "Encoder OK");  // ��������ʼ���ɹ�
    system_delay_ms(500);  // �ʵ���ʱ����ȷ��ʾ
}

// ��������ȡ�ٶ�����
void Encoder_getv(void)
{
    speed1 = encoder_get_count(TIM2_ENCODER);   // ��ȡ������3������
    speed2 = encoder_get_count(TIM4_ENCODER);   // ��ȡ������4������

    encoder_clear_count(TIM2_ENCODER);          // ������3�������
    encoder_clear_count(TIM4_ENCODER);          // ������4�������

    ips200_show_int(0, 1, speed1, 10);          // Һ����ʾ32λ�з�����
    ips200_show_int(0, 2, speed2, 10);          // Һ����ʾ32λ�з�����

    system_delay_ms(100); // �ʵ���ʱ����ȷ��ʾ
}


