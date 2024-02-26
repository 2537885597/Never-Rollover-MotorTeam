/*
 * PID.c
 *
 *  Created on: 2024��1��25��
 *      Author: A
 */

# include "zf_common_headfile.h"

pid_param pid_Steer;
pid_param pid_Motor_v1;
pid_param pid_Motor_v2;
pid_param pid_Motor_angv;
//***************************
pid_param_t PID_IMU;  // ���Բ�����Ԫ
pid_param_t PID_Init; // ��ʼ��
pid_param_t PID_MOTOR;  // ֱ�����

/**********************************************
 *  �������ƣ�pid�㷨����
 *  ����˵��������ƽ�⼰����
 *  ����˵������������趨ֵ������ֵ��
 *  �޸�ʱ�䣺2024��1��28��
 *  ��   ע����Ҫ���в���������pid���趨����ֵ���ɱƽ�����ֵ
 *********************************************/
// pid������ʼ������
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
    ips200_show_string(0, 0, "pid OK"); // ��Ļ��ʾ�ַ��� ������Ļ
    system_delay_ms(500);  // �ʵ���ʱ����ȷ��ʾ
}

// λ��ʽpid �ٶȱջ�
float PidCtrl_Pos_v(pid_param * pid, float Setspeed)
{
    // �趨����
    pid->Kp          = 0.2;
    pid->Ki          = 0.015;
    pid->Kd          = 0.2;

    pid->SetVal = Setspeed;        // �趨�ٶ�ֵ
    // �������
    pid->err = pid->SetVal - pid->ActualVal;

    /* ����޷�*/
    //???

    // �����źŽ��
    pid->voltage = pid->Kp*pid->err+pid->Ki*pid->integral+pid->Kd*(pid->err-pid->err_last);

    //�������͵�ǰֵ
    pid->err_last = pid->err;
    pid->ActualVal=pid->voltage*1.0;

    /* �������� */
    // ??

    return pid->ActualVal;
    //printf("OUT:%d\n",pid->ActualVal);
}

// λ��ʽpid ���ٶȱջ� ֱ����
float PidCtrl_Pos_std(pid_param * pid, float Setangv)
{
    // �趨����
    pid->Kp          = 0.2;
    pid->Ki          = 0.015;
    pid->Kd          = 0.2;

    pid->SetVal = Setangv;  // �趨���ٶ�ֵ
    // �������
    pid->err = pid->SetVal - pid->ActualVal;

    // �����źŽ��
    pid->voltage = pid->Kp*pid->err + pid->Ki*pid->integral + pid->Kd*(pid->err-pid->err_last);

    // ��������뵱ǰֵ
    pid->err_last = pid->err;
    pid->ActualVal=pid->voltage*1.0;

    return pid->ActualVal;
    //printf("OUT:%d\n",pid->ActualVal);
}

// ����ʽpid �ٶȱջ�
float PidCtrl_Inc(pid_param * pid, float Setspeed)
{
    // ϵ������
    pid->Kp=110;
    pid->Ki=6;
    pid->Kd=5;

    pid->SetVal = Setspeed;  // �趨Ŀ��ֵ
    pid->err = pid->SetVal - pid->ActualVal; // �������

    // ��������
    float increment = pid->Kp * (pid->err - pid->err_last) +
            pid->Ki * pid->err + pid->Kd * (pid->err - 2*pid->err_last + pid->err_last_before);

    //���µ�ǰֵ �����
    pid->ActualVal += increment;
    pid->err_last_before = pid->err_last;
    pid->err_last = pid->err;
    return pid->ActualVal;
}

/**********************************************
 *  �������ƣ�pid�㷨����-version2
 *  ����˵��������ƽ�⼰����
 *  ����˵��������������ֵ
 *  �޸�ʱ�䣺2024��1��28��
 *  ��   ע���ܹ����л�������pid��ͬʱ�洢��p��i��d�����㷨���
 *********************************************/

// �޷�����
float constrain_float(float amt, float low, float high)
{
    return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

// pid������ʼ������
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


// pidλ��ʽ���������
float PidLocCtrl(pid_param_t * pid, float error)
{
    // ��������
//    PID_GPS.kp=1.1;
//    PID_GPS.kd=5;
//
//    PID_IMU.kp=1;//1.15
//    PID_IMU.kd=7;

    /* �ۻ���� */
    pid->integrator += error;

    /* ����޷� */
    constrain_float(pid->integrator, -pid->imax, pid->imax);

    // ����p��i��d���������
    pid->out_p = pid->kp * error;
    pid->out_i = pid->ki * pid->integrator;
    pid->out_d = pid->kd * (error - pid->last_error);

    // �������
    pid->last_error = error;

    // �����źŽ��
    pid->out = pid->out_p + pid->out_i + pid->out_d;

    // �ŷ������������Ƕ�����
//    if(pid->out>SERVO_MOTOR_LMAX)
//    {pid->out=SERVO_MOTOR_LMAX;}
//    if(pid->out<SERVO_MOTOR_RMIN)
//    {pid->out=SERVO_MOTOR_RMIN;}

    return pid->out;
//    printf("OUT:%d\n",pid->out);
}

// pid����ʽ���������
float PidIncCtrl(pid_param_t * pid, float error)
{
    // ��������
    PID_MOTOR.kp=110;
    PID_MOTOR.ki=6;
    PID_MOTOR.kd=5;

    // ����p��i��d���������
    pid->out_p = pid->kp * (error - pid->last_error);
    pid->out_i = pid->ki * error;
    pid->out_d = pid->kd * ((error - pid->last_error) - pid->last_derivative);

    // �������
    pid->last_derivative = error - pid->last_error;
    pid->last_error = error;

    // ��������
    pid->out += pid->out_p + pid->out_i + pid->out_d;
    return pid->out;
}



