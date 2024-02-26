/*
 * PID.h
 *
 *  Created on: 2024��1��25��
 *      Author: A
 */

#ifndef CODE_PID_H_
#define CODE_PID_H_

// �ṹ�����
typedef struct
{
    float                SetVal;   // �趨ֵ
    float                ActualVal;// ʵ��ֵ
    float                err;        // ���
    float                err_last; // ��һ�����ֵ

    float                Kp;         // Pϵ��
    float                Ki;         // Iϵ��
    float                Kd;         // Dϵ��
    float                imax;       // �����޷�

    float                voltage;    // ��ѹֵ������ִ�����ı�����
    float                integral; // ����ֵ

    float                err_last_before;// ���ϴ����
    unsigned long        last_t;     // �ϴ�ʱ��
}  pid_param;

typedef struct
{
    float                kp;         //P
    float                ki;         //I
    float                kd;         //D
    float                imax;       //�����޷�

    float                out_p;      //KP���
    float                out_i;      //KI���
    float                out_d;      //KD���
    float                out;        //pid���

    float                integrator; //< ����ֵ
    float                last_error; //< �ϴ����
    float                last_derivative;//< �ϴ���������ϴ����֮��
    unsigned long        last_t;     //< �ϴ�ʱ��
}pid_param_t;

// ȫ�ֱ���
extern pid_param pid_Steer;
extern pid_param pid_Motor_v1;
extern pid_param pid_Motor_v2;
extern pid_param pid_Motor_angv;
//*****************
extern pid_param_t PID_IMU;  // ���Բ�����Ԫ
extern pid_param_t PID_Init; // ��ʼ��
extern pid_param_t PID_MOTOR;  // ֱ�����

// ��������
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
