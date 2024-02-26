/*
 * PID.h
 *
 *  Created on: 2024年1月25日
 *      Author: A
 */

#ifndef CODE_PID_H_
#define CODE_PID_H_

// 结构体参数
typedef struct
{
    float                SetVal;   // 设定值
    float                ActualVal;// 实际值
    float                err;        // 误差
    float                err_last; // 上一次误差值

    float                Kp;         // P系数
    float                Ki;         // I系数
    float                Kd;         // D系数
    float                imax;       // 积分限幅

    float                voltage;    // 电压值（控制执行器的变量）
    float                integral; // 积分值

    float                err_last_before;// 上上次误差
    unsigned long        last_t;     // 上次时间
}  pid_param;

typedef struct
{
    float                kp;         //P
    float                ki;         //I
    float                kd;         //D
    float                imax;       //积分限幅

    float                out_p;      //KP输出
    float                out_i;      //KI输出
    float                out_d;      //KD输出
    float                out;        //pid输出

    float                integrator; //< 积分值
    float                last_error; //< 上次误差
    float                last_derivative;//< 上次误差与上上次误差之差
    unsigned long        last_t;     //< 上次时间
}pid_param_t;

// 全局变量
extern pid_param pid_Steer;
extern pid_param pid_Motor_v1;
extern pid_param pid_Motor_v2;
extern pid_param pid_Motor_angv;
//*****************
extern pid_param_t PID_IMU;  // 惯性测量单元
extern pid_param_t PID_Init; // 初始化
extern pid_param_t PID_MOTOR;  // 直流电机

// 函数声明
void PidInit(pid_param* pid);
float PidCtrl_Pos_v(pid_param * pid, float Setspeed);
float PidCtrl_Pos_std(pid_param * pid, float angv);
float PidCtrl_Inc(pid_param * pid, float Setspeed);
//**********************
float constrain_float(float amt, float low, float high);
void PidInit_t(pid_param_t * pid);
float PidLocCtrl(pid_param_t * pid, float error);
float PidIncCtrl(pid_param_t * pid, float error);

#endif /* CODE_PID_H_ */
