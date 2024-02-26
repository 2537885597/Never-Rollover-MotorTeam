# include "zf_common_headfile.h"

int gyro_lpf=0; //角速度值
float Tduty; // 占空比
float gyro_pid[4]={0,0,0,4000};//角速度环参数 //gyro_pid[4]={0.67,0.047,18.55,4000};
pid_param_t AX;

//定时器1
void CH0_LOOP(void)
{
    // pass
}
