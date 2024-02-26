/*********************************************************************************************************************
* TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� TC264 ��Դ���һ����
*
* TC264 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          cpu0_main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.9.4
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-15       pudding            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��

// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������

// **************************** �������� ****************************
int core0_main(void)
{
    clock_init();                   // ��ȡʱ��Ƶ��<��ر���>
    debug_init();                   // ��ʼ��Ĭ�ϵ��Դ���
    // �˴���д�û����� ���������ʼ�������

    Screen_init();  // ��Ļ������ͷ��ʼ��
    Key_init();     //������ʼ��
    adc_init(ADC0_CH8_A8 , ADC_8BIT); // ADC��ʼ��
    ips200_show_string(0, 0, "adc OK"); // ��Ļ��ʾ�ַ��� ������Ļ
    system_delay_ms(500);  // �ʵ���ʱ����ȷ��ʾ
    lpf_init(); // ��ͨ�˲���ʼ��

    // �����Ϣ��ʼ�����ٶȣ�����
    Encoder_init();// ��������ʼ��
    gyro_init();// �����ǳ�ʼ��
    motor_init();//�����ʼ��
    Screen_init();// ��Ļ��ʼ��
    Steering_init();//�����ʼ��

    PidInit(&pid_Motor_v1);  // �ٶ�pid��ʼ��
    PidInit(&pid_Motor_v2);

    // �˴���д�û����� ���������ʼ�������
    cpu_wait_event_ready();         // �ȴ����к��ĳ�ʼ�����
    while (TRUE)
    {
        Screen_showimg();// ��Ļ��ʾ�Ҷ�ͼ��
        // �˴���д��Ҫѭ��ִ�еĴ���
        Key_scan();  // ɨ�谴��
        if(key1_flag) duty_steer = 1500;  // ��������
        if(key2_flag) duty_steer = 2000;
        if(key3_flag) duty_steer = 2500;
        if(key4_flag) duty_steer = 3000;

        ips200_show_uint(0, 0, duty_steer, 4);      // ��Ļ��ʾռ�ձ�
        pwm_set_duty(ATOM0_CH1_P33_9, duty_steer);  // PWMռ�ձ�����



        ActSpeed1 = PidCtrl_Pos_v(&pid_Motor_v1, SetSpeed1);
        ActSpeed2 = PidCtrl_Pos_v(&pid_Motor_v2, SetSpeed2);

        // �������ת��
        motor_ctrl_v2(motor_l,(uint32)ActSpeed1);
        motor_ctrl_v2(motor_r,(uint32)ActSpeed2);

        Encoder_getv();    // ��ȡ����������
        gyro_getangv();    // �����ǻ�ȡ���ٶȡ����ٶ�
        Swing_control((uint32)ActSpeed1, (float)(speed1 - speed2));

        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

#pragma section all restore


// **************************** �������� ****************************
