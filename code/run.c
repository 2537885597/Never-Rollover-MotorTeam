# include "zf_common_headfile.h"

int gyro_lpf=0; //���ٶ�ֵ
float Tduty; // ռ�ձ�
float gyro_pid[4]={0,0,0,4000};//���ٶȻ����� //gyro_pid[4]={0.67,0.047,18.55,4000};
pid_param_t AX;

//��ʱ��1
void CH0_LOOP(void)
{
    // pass
}
