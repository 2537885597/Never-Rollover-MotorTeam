#include "zf_common_headfile.h"

/***************************************�ṹ�嶨��*************************************************************************/
LowPassFilter lpf_current_gyro;
/***********************************************************************************************************************/
float acc_ratio=0.6;  //���ٶȼƱ���
float gyro_ratio=0.38;//�����Ǳ���
float dt=0.005;       //��������

void lpf_init(void)//��ͨ�˲���ʼ��
{
    lpf_current_gyro.Tf=0.08f;
    lpf_current_gyro.y_prev=0;
    ips200_show_string(0, 0, "lpf OK"); // ��Ļ��ʾ�ַ��� ������Ļ
    system_delay_ms(500);  // �ʵ���ʱ����ȷ��ʾ
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

float angle_calc(float angle_m,float gyro_m)//һ�׻����˲� angle_m���ٶȼ����� gyro_m���������� return�����ںϺ�ĽǶ�
{
    float temp_angle;
    float gyro_now;
    float error_angle;
    static float last_angle;
    static uint8 first_angle;
    if(!first_angle)//�ж��Ƿ�Ϊ��һ�����б�����
    {
        //����ǵ�һ�����У����ϴνǶ�ֵ����Ϊ����ٶ�ֵһ��
        first_angle=1;
        last_angle=angle_m;
    }

    gyro_now=gyro_m*gyro_ratio;

    //���ݲ������ļ��ٶ�ֵת��Ϊ�Ƕ�֮�����ϴεĽǶ�ֵ��ƫ��
    error_angle=(angle_m-last_angle)*acc_ratio;

    //����ƫ���������ǲ����õ��ĽǶ�ֵ���㵱ǰ�Ƕ�ֵ
    temp_angle=last_angle+(error_angle+gyro_now)*dt;

    //���浱ǰ�Ƕ�ֵ
    last_angle=temp_angle;
    return temp_angle;
}
