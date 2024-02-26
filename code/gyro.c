/*
 * gyro.c
 *
 *  Created on: 2024年1月25日
 *      Author: A
 */

# include "zf_common_headfile.h"

int16 gyro1;
int16 gyro2;
int16 gyro3;

int16 acc1;
int16 acc2;
int16 acc3;

// 陀螺仪初始化
void gyro_init(void)
{
    imu660ra_init();  // ICM初始化
    ips200_show_string(0, 0, "imu660ra OK");  // ICM初始化成功
    system_delay_ms(500);  // 适当延时以正确显示
}

// 陀螺仪获取角速度、加速度
void gyro_getangv(void)
{
    imu660ra_get_gyro();   // 获取 ICM20602 陀螺仪的数据
    imu660ra_get_acc();    // 获取 ICM20602 加速度计的数据

    // 记录 ICM20602 陀螺仪 的各个数据
    gyro1 = imu660ra_gyro_x;
    gyro2 = imu660ra_gyro_y;
    gyro3 = imu660ra_gyro_z;

    // 记录 ICM20602 加速度计 的各个数据

    acc1 = imu660ra_acc_x;
    acc2 = imu660ra_acc_y;
    acc3 = imu660ra_acc_z;

    // 显示 ICM20602 陀螺仪 加速度计 的各个数据
    ips200_show_int(0, 1, gyro1, 5);
    ips200_show_int(0, 2, gyro2, 5);
    ips200_show_int(0, 3, gyro3, 5);

    ips200_show_int(0, 4, acc1, 5);
    ips200_show_int(0, 5, acc2, 5);
    ips200_show_int(0, 6, acc3, 5);

    system_delay_ms(100);  // 适当延时以正确显示
}



