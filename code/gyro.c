/*
 * gyro.c
 *
 *  Created on: 2024��1��25��
 *      Author: A
 */

# include "zf_common_headfile.h"

int16 gyro1;
int16 gyro2;
int16 gyro3;

int16 acc1;
int16 acc2;
int16 acc3;

// �����ǳ�ʼ��
void gyro_init(void)
{
    imu660ra_init();  // ICM��ʼ��
    ips200_show_string(0, 0, "imu660ra OK");  // ICM��ʼ���ɹ�
    system_delay_ms(500);  // �ʵ���ʱ����ȷ��ʾ
}

// �����ǻ�ȡ���ٶȡ����ٶ�
void gyro_getangv(void)
{
    imu660ra_get_gyro();   // ��ȡ ICM20602 �����ǵ�����
    imu660ra_get_acc();    // ��ȡ ICM20602 ���ٶȼƵ�����

    // ��¼ ICM20602 ������ �ĸ�������
    gyro1 = imu660ra_gyro_x;
    gyro2 = imu660ra_gyro_y;
    gyro3 = imu660ra_gyro_z;

    // ��¼ ICM20602 ���ٶȼ� �ĸ�������

    acc1 = imu660ra_acc_x;
    acc2 = imu660ra_acc_y;
    acc3 = imu660ra_acc_z;

    // ��ʾ ICM20602 ������ ���ٶȼ� �ĸ�������
    ips200_show_int(0, 1, gyro1, 5);
    ips200_show_int(0, 2, gyro2, 5);
    ips200_show_int(0, 3, gyro3, 5);

    ips200_show_int(0, 4, acc1, 5);
    ips200_show_int(0, 5, acc2, 5);
    ips200_show_int(0, 6, acc3, 5);

    system_delay_ms(100);  // �ʵ���ʱ����ȷ��ʾ
}



