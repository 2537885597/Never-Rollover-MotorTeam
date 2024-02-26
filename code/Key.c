/*
 * Key.c
 *
 *  Created on: 2024��1��24��
 *      Author: A
 */


#include "zf_common_headfile.h"

// ����״̬
uint8 key1_state = 1;                                                               // ��������״̬
uint8 key2_state = 1;                                                               // ��������״̬
uint8 key3_state = 1;                                                               // ��������״̬
uint8 key4_state = 1;                                                               // ��������״̬

// ������һ��״̬
uint8 key1_state_last = 0;                                                          // ��һ�ΰ�������״̬
uint8 key2_state_last = 0;                                                          // ��һ�ΰ�������״̬
uint8 key3_state_last = 0;                                                          // ��һ�ΰ�������״̬
uint8 key4_state_last = 0;                                                          // ��һ�ΰ�������״̬

// ������־λ
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;

void Key_init(void)//������LED��ʼ��
{
       gpio_init(Key1, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY1 ���� Ĭ�ϸߵ�ƽ ��������
       gpio_init(Key2, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY2 ���� Ĭ�ϸߵ�ƽ ��������
       gpio_init(Key3, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY3 ���� Ĭ�ϸߵ�ƽ ��������
       gpio_init(Key4, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY4 ���� Ĭ�ϸߵ�ƽ ��������
       ips200_show_string(0, 0, "key OK"); // ��Ļ��ʾ�ַ��� ������Ļ
       system_delay_ms(500);  // �ʵ���ʱ����ȷ��ʾ
}

void Key_scan(void)//����ɨ��
{
    //ʹ�ô˷����ŵ����ڣ�����Ҫʹ��while(1) �ȴ������⴦������Դ�˷�

    //���水��״̬
    key1_state_last = key1_state;
    key2_state_last = key2_state;
    key3_state_last = key3_state;
    key4_state_last = key4_state;

    //��ȡ��ǰ����״̬
    key1_state = gpio_get_level(Key1);
    key2_state = gpio_get_level(Key2);
    key3_state = gpio_get_level(Key3);
    key4_state = gpio_get_level(Key4);


    //��⵽��������֮�� ���ſ� ��λ��־λ
    if(key1_state && !key1_state_last)   {key1_flag = 1;}
    if(key2_state && !key2_state_last)   {key2_flag = 1;}
    if(key3_state && !key3_state_last)   {key3_flag = 1;}
    if(key4_state && !key4_state_last)   {key4_flag = 1;}

    //��־λ��λ֮�󣬿���ʹ�ñ�־λִ���Լ���Ҫ�����¼�

    system_delay_ms(10);//��ʱ����������Ӧ�ñ�֤����ʱ�䲻С��10ms

}

/*  УĦ����ѧ������
uint8  key2_last_status;
uint8  key2_status=1;
uint8  key2_flag=0;
uint32  duty = 1000;
int key_set2(gpio_pin_enum key)
{
    key2_last_status=key2_status;
    key2_status=gpio_get_level(key);
    if(key2_last_status&& !key2_status)
    {
        key2_flag=1;
    }
    if(key2_flag==1)
    {
        duty += 500;

        //pwm_set_duty(ATOM1_CH6_P02_6, 0);

        key2_flag=0;

        return 1;
    }
    return 0;
}
int key_set1(gpio_pin_enum key)
{
    key2_last_status=key2_status;
    key2_status=gpio_get_level(key);
    if(key2_last_status&& !key2_status)
    {
        key2_flag=1;
    }
    if(key2_flag==1)
    {
        //pwm_duty(ATOM1_CH4_P02_4, 0);
        //pwm_duty(ATOM1_CH6_P02_6, 0);//zuolun

        key2_flag=0;

        return 1;
    }
    return 0;
}
*/

