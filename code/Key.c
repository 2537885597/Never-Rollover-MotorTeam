/*
 * Key.c
 *
 *  Created on: 2024年1月24日
 *      Author: A
 */


#include "zf_common_headfile.h"

// 按键状态
uint8 key1_state = 1;                                                               // 按键动作状态
uint8 key2_state = 1;                                                               // 按键动作状态
uint8 key3_state = 1;                                                               // 按键动作状态
uint8 key4_state = 1;                                                               // 按键动作状态

// 按键上一次状态
uint8 key1_state_last = 0;                                                          // 上一次按键动作状态
uint8 key2_state_last = 0;                                                          // 上一次按键动作状态
uint8 key3_state_last = 0;                                                          // 上一次按键动作状态
uint8 key4_state_last = 0;                                                          // 上一次按键动作状态

// 按键标志位
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;

void Key_init(void)//按键与LED初始化
{
       gpio_init(Key1, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY1 输入 默认高电平 上拉输入
       gpio_init(Key2, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY2 输入 默认高电平 上拉输入
       gpio_init(Key3, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY3 输入 默认高电平 上拉输入
       gpio_init(Key4, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY4 输入 默认高电平 上拉输入
       ips200_show_string(0, 0, "key OK"); // 屏幕显示字符串 测试屏幕
       system_delay_ms(500);  // 适当延时以正确显示
}

void Key_scan(void)//按键扫描
{
    //使用此方法优点在于，不需要使用while(1) 等待，避免处理器资源浪费

    //保存按键状态
    key1_state_last = key1_state;
    key2_state_last = key2_state;
    key3_state_last = key3_state;
    key4_state_last = key4_state;

    //读取当前按键状态
    key1_state = gpio_get_level(Key1);
    key2_state = gpio_get_level(Key2);
    key3_state = gpio_get_level(Key3);
    key4_state = gpio_get_level(Key4);


    //检测到按键按下之后 并放开 置位标志位
    if(key1_state && !key1_state_last)   {key1_flag = 1;}
    if(key2_state && !key2_state_last)   {key2_flag = 1;}
    if(key3_state && !key3_state_last)   {key3_flag = 1;}
    if(key4_state && !key4_state_last)   {key4_flag = 1;}

    //标志位置位之后，可以使用标志位执行自己想要做的事件

    system_delay_ms(10);//延时，按键程序应该保证调用时间不小于10ms

}

/*  校摩托组学长代码
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

