/*
 * PID.c
 *
 *  Created on: 2024年1月25日
 *      Author: A
 */

# include "zf_common_headfile.h"

pid_param pid_Steer;
pid_param pid_Motor_v1;
pid_param pid_Motor_v2;
pid_param pid_Motor_angv;
//***************************
pid_param_t PID_IMU;  // 惯性测量单元
pid_param_t PID_Init; // 初始化
pid_param_t PID_MOTOR;  // 直流电机

/**********************************************
 *  函数名称：pid算法函数
 *  功能说明：用于平衡及控速
 *  参数说明：传入的是设定值（期望值）
 *  修改时间：2024年1月28日
 *  备   注：需要自行参数整定的pid，设定参数值即可逼近期望值
 *********************************************/
// pid参数初始化函数
void PidInit(pid_param * pid)
{
    //printf("PID_init begin \n");
    pid->SetVal      = 0;
    pid->ActualVal   = 0;
    pid->err         = 0;
    pid->err_last    = 0;

    pid->Kp          = 0;
    pid->Ki          = 0;
    pid->Kd          = 0;
    pid->imax        = 0;

    pid->voltage     = 0;
    pid->integral    = 0;

    pid->err_last_before = 0;
    pid->last_t  = 0;
    //printf("PID_init end \n");
    ips200_show_string(0, 0, "pid OK"); // 屏幕显示字符串 测试屏幕
    system_delay_ms(500);  // 适当延时以正确显示
}

// 位置式pid 速度闭环
float PidCtrl_Pos_v(pid_param * pid, float Setspeed)
{
    // 设定参数
    pid->Kp          = 0.2;
    pid->Ki          = 0.015;
    pid->Kd          = 0.2;

    pid->SetVal = Setspeed;        // 设定速度值
    // 计算误差
    pid->err = pid->SetVal - pid->ActualVal;

    /* 误差限幅*/
    //???

    // 计算信号结果
    pid->voltage = pid->Kp*pid->err+pid->Ki*pid->integral+pid->Kd*(pid->err-pid->err_last);

    //更新误差和当前值
    pid->err_last = pid->err;
    pid->ActualVal=pid->voltage*1.0;

    /* 死区问题 */
    // ??

    return pid->ActualVal;
    //printf("OUT:%d\n",pid->ActualVal);
}

// 位置式pid 角速度闭环 直立环
float PidCtrl_Pos_std(pid_param * pid, float Setangv)
{
    // 设定参数
    pid->Kp          = 0.2;
    pid->Ki          = 0.015;
    pid->Kd          = 0.2;

    pid->SetVal = Setangv;  // 设定角速度值
    // 计算误差
    pid->err = pid->SetVal - pid->ActualVal;

    // 计算信号结果
    pid->voltage = pid->Kp*pid->err + pid->Ki*pid->integral + pid->Kd*(pid->err-pid->err_last);

    // 更新误差与当前值
    pid->err_last = pid->err;
    pid->ActualVal=pid->voltage*1.0;

    return pid->ActualVal;
    //printf("OUT:%d\n",pid->ActualVal);
}

// 增量式pid 速度闭环
float PidCtrl_Inc(pid_param * pid, float Setspeed)
{
    // 系数设置
    pid->Kp=110;
    pid->Ki=6;
    pid->Kd=5;

    pid->SetVal = Setspeed;  // 设定目标值
    pid->err = pid->SetVal - pid->ActualVal; // 计算误差

    // 计算增量
    float increment = pid->Kp * (pid->err - pid->err_last) +
            pid->Ki * pid->err + pid->Kd * (pid->err - 2*pid->err_last + pid->err_last_before);

    //更新当前值 与误差
    pid->ActualVal += increment;
    pid->err_last_before = pid->err_last;
    pid->err_last = pid->err;
    return pid->ActualVal;
}

/**********************************************
 *  函数名称：pid算法函数-version2
 *  功能说明：用于平衡及控速
 *  参数说明：传入的是误差值
 *  修改时间：2024年1月28日
 *  备   注：能够自行积累误差的pid，同时存储了p、i、d各个算法输出
 *********************************************/

// 限幅函数
float constrain_float(float amt, float low, float high)
{
    return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

// pid参数初始化函数
void PidInit_t(pid_param_t * pid)
{
    pid->kp        = 0;
    pid->ki        = 0;
    pid->kd        = 0;
    pid->imax      = 0;
    pid->out_p     = 0;
    pid->out_i     = 0;
    pid->out_d     = 0;
    pid->out       = 0;
    pid->integrator= 0;
    pid->last_error= 0;
    pid->last_derivative   = 0;
    pid->last_t    = 0;
}


// pid位置式控制器输出
float PidLocCtrl(pid_param_t * pid, float error)
{
    // 参数设置
//    PID_GPS.kp=1.1;
//    PID_GPS.kd=5;
//
//    PID_IMU.kp=1;//1.15
//    PID_IMU.kd=7;

    /* 累积误差 */
    pid->integrator += error;

    /* 误差限幅 */
    constrain_float(pid->integrator, -pid->imax, pid->imax);

    // 计算p、i、d各自输出量
    pid->out_p = pid->kp * error;
    pid->out_i = pid->ki * pid->integrator;
    pid->out_d = pid->kd * (error - pid->last_error);

    // 更新误差
    pid->last_error = error;

    // 计算信号结果
    pid->out = pid->out_p + pid->out_i + pid->out_d;

    // 伺服电机（舵机）角度限制
//    if(pid->out>SERVO_MOTOR_LMAX)
//    {pid->out=SERVO_MOTOR_LMAX;}
//    if(pid->out<SERVO_MOTOR_RMIN)
//    {pid->out=SERVO_MOTOR_RMIN;}

    return pid->out;
//    printf("OUT:%d\n",pid->out);
}

// pid增量式控制器输出
float PidIncCtrl(pid_param_t * pid, float error)
{
    // 参数设置
    PID_MOTOR.kp=110;
    PID_MOTOR.ki=6;
    PID_MOTOR.kd=5;

    // 计算p、i、d各自输出量
    pid->out_p = pid->kp * (error - pid->last_error);
    pid->out_i = pid->ki * error;
    pid->out_d = pid->kd * ((error - pid->last_error) - pid->last_derivative);

    // 更新误差
    pid->last_derivative = error - pid->last_error;
    pid->last_error = error;

    // 计算增量
    pid->out += pid->out_p + pid->out_i + pid->out_d;
    return pid->out;
}



