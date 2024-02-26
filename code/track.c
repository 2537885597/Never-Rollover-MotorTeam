/*
 * track.c
 *
 *  Created on: 2024��1��26��
 *      Author: A
 */

#include "zf_common_headfile.h"

// ��ֵ������
 void Image_Binarization(uint8 *dst, uint8 *src, uint8 threshold)
 {
     for (int i = 0; i < CAMERA_SIZE; i++)
     {
         *(dst + i) = (*(src + i) >= threshold) ? White : Black;
     }
 }

