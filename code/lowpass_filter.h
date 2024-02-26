#ifndef LOWPASS_FILTER_H
#define LOWPASS_FILTER_H

typedef  struct
{
    float Tf;
    float y_prev;
}LowPassFilter;

// 全局变量
extern LowPassFilter lpf_current_gyro;

// 函数声明
void lpf_init(void);
float lpf_operator(LowPassFilter*LPF,float x,float dt);
float angle_calc(float angle_m,float gyro_m);

#endif
