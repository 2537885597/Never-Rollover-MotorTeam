/*
 * Screen.c
 *
 *  Created on: 2024��1��25��
 *      Author: A
 */

# include "zf_common_headfile.h"

// ��Ļ��ʼ��
void Screen_init(void)
{
    ips200_init(IPS200_TYPE_PARALLEL8);    // ����Һ����ʼ��
    ips200_show_string(0, 0, "ips initial"); // ��Ļ��ʾ�ַ��� ������Ļ
    mt9v03x_init();  // ���������ͷ��ʼ��
    ips200_show_string(0, 1, "camera OK"); // ��Ļ��ʾ�ַ��� ������Ļ
    system_delay_ms(500);  // �ʵ���ʱ����ȷ��ʾ
}

// ��Ļ��ʾ�Ҷ�ͼ��
void Screen_showimg(void)
{
    if(mt9v03x_finish_flag)
   {
       ips200_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
       mt9v03x_finish_flag = 0;
   }
}
