#include "zf_common_headfile.h"

/***************************************结构体定义*************************************************************************/
LowPassFilter lpf_current_gyro;
/***********************************************************************************************************************/
float acc_ratio=0.6;  //加速度计比例
float gyro_ratio=0.38;//陀螺仪比例
float dt=0.005;       //采样周期

void lpf_init(void)//低通滤波初始化
{
    lpf_current_gyro.Tf=0.08f;
    lpf_current_gyro.y_prev=0;
    ips200_show_string(0, 0, "lpf OK"); // 屏幕显示字符串 测试屏幕
    system_delay_ms(500);  // 适当延时以正确显示
}

float lpf_operator(LowPassFilter*LPF, float x, float dt)
{
    float alpha = 0;
    float y = 0;
    alpha = LPF->Tf/(LPF->Tf+dt);
    y = alpha*LPF->y_prev + (1.0f-alpha)*x;
    LPF->y_prev = y;
    return y;
}

float angle_calc(float angle_m,float gyro_m)//一阶互补滤波 angle_m加速度计数据 gyro_m陀螺仪数据 return数据融合后的角度
{
    float temp_angle;
    float gyro_now;
    float error_angle;
    static float last_angle;
    static uint8 first_angle;
    if(!first_angle)//判断是否为第一次运行本函数
    {
        //如果是第一次运行，则将上次角度值设置为与加速度值一致
        first_angle=1;
        last_angle=angle_m;
    }

    gyro_now=gyro_m*gyro_ratio;

    //根据测量到的加速度值转换为角度之后与上次的角度值求偏差
    error_angle=(angle_m-last_angle)*acc_ratio;

    //根据偏差与陀螺仪测量得到的角度值计算当前角度值
    temp_angle=last_angle+(error_angle+gyro_now)*dt;

    //保存当前角度值
    last_angle=temp_angle;
    return temp_angle;
}
