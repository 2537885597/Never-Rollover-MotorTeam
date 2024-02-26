/*********************************************************************************************************************
* TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC264 开源库的一部分
*
* TC264 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          cpu0_main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.9.4
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-09-15       pudding            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设

// **************************** 代码区域 ****************************
int core0_main(void)
{
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口
    // 此处编写用户代码 例如外设初始化代码等

    Screen_init();  // 屏幕和摄像头初始化
    Key_init();     //按键初始化
    adc_init(ADC0_CH8_A8 , ADC_8BIT); // ADC初始化
    ips200_show_string(0, 0, "adc OK"); // 屏幕显示字符串 测试屏幕
    system_delay_ms(500);  // 适当延时以正确显示
    lpf_init(); // 低通滤波初始化

    // 输出信息初始化（速度，方向）
    Encoder_init();// 编码器初始化
    gyro_init();// 陀螺仪初始化
    motor_init();//电机初始化
    Screen_init();// 屏幕初始化
    Steering_init();//舵机初始化

    PidInit(&pid_Motor_v1);  // 速度pid初始化
    PidInit(&pid_Motor_v2);

    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();         // 等待所有核心初始化完毕
    while (TRUE)
    {
        Screen_showimg();// 屏幕显示灰度图像
        // 此处编写需要循环执行的代码
        Key_scan();  // 扫描按键
        if(key1_flag) duty_steer = 1500;  // 按键调向
        if(key2_flag) duty_steer = 2000;
        if(key3_flag) duty_steer = 2500;
        if(key4_flag) duty_steer = 3000;

        ips200_show_uint(0, 0, duty_steer, 4);      // 屏幕显示占空比
        pwm_set_duty(ATOM0_CH1_P33_9, duty_steer);  // PWM占空比设置



        ActSpeed1 = PidCtrl_Pos_v(&pid_Motor_v1, SetSpeed1);
        ActSpeed2 = PidCtrl_Pos_v(&pid_Motor_v2, SetSpeed2);

        // 调整电机转速
        motor_ctrl_v2(motor_l,(uint32)ActSpeed1);
        motor_ctrl_v2(motor_r,(uint32)ActSpeed2);

        Encoder_getv();    // 获取编码器数据
        gyro_getangv();    // 陀螺仪获取角速度、加速度
        Swing_control((uint32)ActSpeed1, (float)(speed1 - speed2));

        // 此处编写需要循环执行的代码
    }
}

#pragma section all restore


// **************************** 代码区域 ****************************
