#ifndef LOWPASS_FILTER_H
#define LOWPASS_FILTER_H

typedef  struct
{
    float Tf;
    float y_prev;
}LowPassFilter;

// ȫ�ֱ���
extern LowPassFilter lpf_current_gyro;

// ��������
void lpf_init(void);
float lpf_operator(LowPassFilter*LPF,float x,float dt);
float angle_calc(float angle_m,float gyro_m);

#endif
