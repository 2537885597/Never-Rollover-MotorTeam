/*
 * Screen.c
 *
 *  Created on: 2024年1月25日
 *      Author: A
 */

# include "zf_common_headfile.h"

// 屏幕初始化
void Screen_init(void)
{
    ips200_init(IPS200_TYPE_PARALLEL8);    // 并口液晶初始化
    ips200_show_string(0, 0, "ips initial"); // 屏幕显示字符串 测试屏幕
    mt9v03x_init();  // 总钻风摄像头初始化
    ips200_show_string(0, 1, "camera OK"); // 屏幕显示字符串 测试屏幕
    system_delay_ms(500);  // 适当延时以正确显示
}

// 屏幕显示灰度图像
void Screen_showimg(void)
{
    if(mt9v03x_finish_flag)
   {
       ips200_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
       mt9v03x_finish_flag = 0;
   }
}
