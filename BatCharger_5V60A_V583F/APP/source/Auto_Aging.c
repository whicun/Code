/**************************************************************************************/
// Copyright (C) Wuhan Jingneng Electronic Technology Co., Ltd. All Rights Reserved
//    Project: BatCharger_5V60A_V200
//  File name: Auto_Aging.c
// Created on: 2020-6-30
//     Author: LuoAnJiang
/**************************************************************************************/
#include "Headers_All.h"
//ȫ�ֱ�������
struct_Auto_Aging   Auto_Aging;
struct_Image        Image_Protect_Bak;
unsigned char Buff_To_Byte[128];

//ģ��1�ϻ�����
//250����-����30S
const unsigned char ubStep250A_Buffer[112] = {0x70,0x0A,0x00,0xFA,0x01,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x75,0x30,0x01,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xD6,0xD8,0x05,0x00,0x00,0x00,0x06,0x0C,0xF8,0x50,0x07,0x0C,0xF8,0x50,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0xFF,0xEB,0x0D};

//251����-��ѹ���5V 9000S 2.5Сʱ
const unsigned char ubStep251A_Buffer[112] = {0x70,0x0A,0x00,0xFB,0x03,0xFF,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0xC3,0x50,0xFF,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x89,0x54,0x40,0x01,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xD6,0xD8,0x05,0x00,0x88,0xB8,0x06,0x0C,0xF8,0x50,0x07,0x0C,0xF8,0x50,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0x36,0xAD,0x0D};

//251����-��ѹ���5V 60S
const unsigned char ubStep251A_Buffer_Test[112] = {0x70,0x0A,0x00,0xFB,0x03,0xFF,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0xC3,0x50,0xFF,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0xEA,0x60,0x01,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xA7,0xF8,0x05,0x00,0x6F,0x54,0x06,0x18,0x6D,0x20,0x07,0x18,0x6D,0x20,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0x6D,0x63,0x0D};

//252����-���� 15S
const unsigned char ubStep252A_Buffer[112] = {0x70,0x0A,0x00,0xFC,0x01,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x3A,0x98,0x01,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xD6,0xD8,0x05,0x00,0x88,0xB8,0x06,0x0C,0xF8,0x50,0x07,0x0C,0xF8,0x50,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0x17,0x74,0x0D};

//253����-�����ŵ�80A 8990S Լ2.5Сʱ
const unsigned char ubStep253A_Buffer_80A[112] = {0x70,0x0A,0x00,0xFD,0x05,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x03,0x00,0x0C,0x35,0x00,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x89,0x2D,0x30,0x03,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xD6,0xD8,0x05,0x00,0x88,0xB8,0x06,0x0C,0xF8,0x50,0x07,0x0C,0xF8,0x50,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0xD6,0x3A,0x0D};

//253����-�����ŵ�60A 8990S Լ2.5Сʱ
const unsigned char ubStep253A_Buffer_60A[112] = {0x70,0x0A,0x00,0xFD,0x05,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x03,0x00,0x09,0x27,0xC0,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x89,0x2D,0x30,0x03,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xD6,0xD8,0x05,0x00,0xAF,0xC8,0x06,0x0C,0xF8,0x50,0x07,0x0C,0xF8,0x50,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0x8E,0xD2,0x0D};

//253����-�����ŵ�40A 8990S Լ2.5Сʱ
const unsigned char ubStep253A_Buffer_40A[112] = {0x70,0x0A,0x00,0xFD,0x05,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x03,0x00,0x06,0x1A,0x80,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x89,0x2D,0x30,0x03,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xD6,0xD8,0x05,0x00,0xAF,0xC8,0x06,0x0C,0xF8,0x50,0x07,0x0C,0xF8,0x50,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0x0E,0x2F,0x0D};

//253����-�����ŵ�20A 8990S Լ2.5Сʱ
const unsigned char ubStep253A_Buffer_20A[112] = {0x70,0x0A,0x00,0xFD,0x05,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x03,0x00,0x03,0x0D,0x40,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x89,0x2D,0x30,0x03,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xA7,0xF8,0x05,0x00,0x6F,0x54,0x06,0x18,0x6D,0x20,0x07,0x18,0x6D,0x20,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0xCA,0xB0,0x0D};

//253����-�����ŵ�40A 50S
const unsigned char ubStep253A_Buffer_Test[112] = {0x70,0x0A,0x00,0xFD,0x05,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x03,0x00,0x06,0x1A,0x80,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0xC3,0x50,0x03,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xA7,0xF8,0x05,0x00,0x6F,0x54,0x06,0x18,0x6D,0x20,0x07,0x18,0x6D,0x20,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0x23,0x40,0x0D};

//ģ��2�ϻ�����
//250����-����35S
const unsigned char ubStep250B_Buffer[112] = {0x70,0x0A,0x00,0xFA,0x01,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x88,0xB8,0x01,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xD6,0xD8,0x05,0x00,0x00,0x00,0x06,0x0C,0xF8,0x50,0x07,0x0C,0xF8,0x50,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0xB4,0x64,0x0D};

//251����-�����ŵ�80A 8990S Լ2.5Сʱ
const unsigned char ubStep251B_Buffer_80A[112] = {0x70,0x0A,0x00,0xFB,0x05,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x03,0x00,0x0C,0x35,0x00,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x89,0x2D,0x30,0x01,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xA7,0xF8,0x05,0x00,0x6F,0x54,0x06,0x18,0x6D,0x20,0x07,0x18,0x6D,0x20,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0xF1,0x70,0x0D};

//251����-�����ŵ�60A 8990S Լ2.5Сʱ
const unsigned char ubStep251B_Buffer_60A[112] = {0x70,0x0A,0x00,0xFB,0x05,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x03,0x00,0x09,0x27,0xC0,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x89,0x2D,0x30,0x01,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xA7,0xF8,0x05,0x00,0x6F,0x54,0x06,0x18,0x6D,0x20,0x07,0x18,0x6D,0x20,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0x0D,0xA4,0x0D};

//251����-�����ŵ�40A 8990S Լ2.5Сʱ
const unsigned char ubStep251B_Buffer_40A[112] = {0x70,0x0A,0x00,0xFB,0x05,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x03,0x00,0x06,0x1A,0x80,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x89,0x2D,0x30,0x01,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xA7,0xF8,0x05,0x00,0x6F,0x54,0x06,0x18,0x6D,0x20,0x07,0x18,0x6D,0x20,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0x8D,0x59,0x0D};

//251����-�����ŵ�20A 8990S Լ2.5Сʱ
const unsigned char ubStep251B_Buffer_20A[112] = {0x70,0x0A,0x00,0xFB,0x05,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x03,0x00,0x03,0x0D,0x40,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x89,0x2D,0x30,0x01,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xA7,0xF8,0x05,0x00,0x6F,0x54,0x06,0x18,0x6D,0x20,0x07,0x18,0x6D,0x20,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0x73,0xC4,0x0D};

//251����-�����ŵ�40A 50S
const unsigned char ubStep251B_Buffer_Test[112] = {0x70,0x0A,0x00,0xFB,0x05,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x03,0x00,0x06,0x1A,0x80,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0xC3,0x50,0x01,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xA7,0xF8,0x05,0x00,0x6F,0x54,0x06,0x0C,0xF8,0x50,0x07,0x0C,0xF8,0x50,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0x45,0x36,0x0D};

//252����-���� 15S
const unsigned char ubStep252B_Buffer[112] = {0x70,0x0A,0x00,0xFC,0x01,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x3A,0x98,0x01,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xD6,0xD8,0x05,0x00,0x88,0xB8,0x06,0x0C,0xF8,0x50,0x07,0x0C,0xF8,0x50,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0x17,0x74,0x0D};

//253����-��ѹ���5V 9000S 2.5Сʱ
const unsigned char ubStep253B_Buffer[112] = {0x70,0x0A,0x00,0xFD,0x03,0xFF,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0xC3,0x50,0xFF,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x89,0x54,0x40,0x03,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xD6,0xD8,0x05,0x00,0x88,0xB8,0x06,0x0C,0xF8,0x50,0x07,0x0C,0xF8,0x50,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0x8F,0xD9,0x0D};

//253����-��ѹ���5V 60S
const unsigned char ubStep253B_Buffer_Test[112] = {0x70,0x0A,0x00,0xFD,0x03,0xFF,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0xC3,0x50,0xFF,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x03,0xE8,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0xEA,0x60,0x03,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x01,0x07,0xD0,0x02,0x01,0xDC,0x91,0x03,0x01,0xDC,0x91,0x04,0x00,0xA7,0xF8,0x05,0x00,0x6F,0x54,0x06,0x18,0x6D,0x20,0x07,0x18,0x6D,0x20,0x08,0x00,0x27,0x1A,0x01,0x09,0x00,0x27,0x10,0x01,0x0A,0x00,0x27,0x10,0x01,0x0B,0x00,0x27,0x10,0x01,0xD4,0x17,0x0D};

void WorkStep_Aging_WritetoFlash(void)
{
    switch(Auto_Aging.State_WritetoFalsh)
    {
    case 0:{
            if(Auto_Aging.Req_WR_M1==TRUE)
            {
                Auto_Aging.State_WritetoFalsh=10;
                EEPROM_Write_Char(cEepromParallMode,SINGLE);
                EEPROM_Write_Char(cEepromParallNum,1);
                Auto_Aging.Step_Aging=STEP_AGING_READY;
                EEPROM_Write_Uint16(cEepromStepAging,Auto_Aging.Step_Aging);
            }
            else if(Auto_Aging.Req_WR_M2==TRUE)
            {
                Auto_Aging.State_WritetoFalsh=20;
                EEPROM_Write_Char(cEepromParallMode,SINGLE);
                EEPROM_Write_Char(cEepromParallNum,1);
                Auto_Aging.Step_Aging=STEP_AGING_READY;
                EEPROM_Write_Uint16(cEepromStepAging,Auto_Aging.Step_Aging);
            }
            break;}

    case 10:{
            if(Qurey_SPI_Flash_Write(SERV_FLASH_DEBUG)==BUSY)
            {
                return;
            }
            SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(249)*0x1000,ubStep250A_Buffer[0],(unsigned char *)ubStep250A_Buffer);
            Auto_Aging.State_WritetoFalsh=11;
            break;}

    case 11:{
            if(Qurey_SPI_Flash_Write(SERV_FLASH_DEBUG)==BUSY)
            {
                return;
            }
            if(W5500_Service.SIPR[3]==100)
            {
                SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(250)*0x1000,ubStep251A_Buffer_Test[0],(unsigned char *)ubStep251A_Buffer_Test);
            }
            else
            {
                SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(250)*0x1000,ubStep251A_Buffer[0],(unsigned char *)ubStep251A_Buffer);
            }
                Auto_Aging.State_WritetoFalsh=12;
            break;}

    case 12:{
            if(Qurey_SPI_Flash_Write(SERV_FLASH_DEBUG)==BUSY)
            {
                return;
            }
            SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(251)*0x1000,ubStep252A_Buffer[0],(unsigned char *)ubStep252A_Buffer);
            Auto_Aging.State_WritetoFalsh=13;
            break;}

    case 13:{
            if(Qurey_SPI_Flash_Write(SERV_FLASH_DEBUG)==BUSY)
            {
                return;
            }

            if(W5500_Service.SIPR[3]==102)
            {
                SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(252)*0x1000,ubStep253A_Buffer_20A[0],(unsigned char *)ubStep253A_Buffer_20A);
            }
            else if(W5500_Service.SIPR[3]==104)
            {
                SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(252)*0x1000,ubStep253A_Buffer_40A[0],(unsigned char *)ubStep253A_Buffer_40A);
            }
            else if(W5500_Service.SIPR[3]==106)
            {
                SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(252)*0x1000,ubStep253A_Buffer_60A[0],(unsigned char *)ubStep253A_Buffer_60A);
            }
            else if(W5500_Service.SIPR[3]==108)
            {
                SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(252)*0x1000,ubStep253A_Buffer_80A[0],(unsigned char *)ubStep253A_Buffer_80A);
            }
            else
            {
                SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(252)*0x1000,ubStep253A_Buffer_Test[0],(unsigned char *)ubStep253A_Buffer_Test);
            }
            Auto_Aging.State_WritetoFalsh=30;
            Auto_Aging.Req_WR_M1=FALSE;
            break;}

    case 20:{
            if(Qurey_SPI_Flash_Write(SERV_FLASH_DEBUG)==BUSY)
            {
                return;
            }
            SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(249)*0x1000,ubStep250B_Buffer[0],(unsigned char *)ubStep250B_Buffer);
            Auto_Aging.State_WritetoFalsh=21;
            break;}

    case 21:{
            if(Qurey_SPI_Flash_Write(SERV_FLASH_DEBUG)==BUSY)
            {
                return;
            }

            if(W5500_Service.SIPR[3]==103)
            {
                SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(250)*0x1000,ubStep251B_Buffer_20A[0],(unsigned char *)ubStep251B_Buffer_20A);
            }
            else if(W5500_Service.SIPR[3]==105)
            {
                SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(250)*0x1000,ubStep251B_Buffer_40A[0],(unsigned char *)ubStep251B_Buffer_40A);
            }
            else if(W5500_Service.SIPR[3]==107)
            {
                SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(250)*0x1000,ubStep251B_Buffer_60A[0],(unsigned char *)ubStep251B_Buffer_60A);
            }
            else if(W5500_Service.SIPR[3]==109)
            {
                SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(250)*0x1000,ubStep251B_Buffer_80A[0],(unsigned char *)ubStep251B_Buffer_80A);
            }
            else
            {
                SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(250)*0x1000,ubStep251B_Buffer_Test[0],(unsigned char *)ubStep251B_Buffer_Test);
            }

            Auto_Aging.State_WritetoFalsh=22;
            break;}

    case 22:{
            if(Qurey_SPI_Flash_Write(SERV_FLASH_DEBUG)==BUSY)
            {
                return;
            }
            SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(251)*0x1000,ubStep252B_Buffer[0],(unsigned char *)ubStep252B_Buffer);
            Auto_Aging.State_WritetoFalsh=23;
            break;}

    case 23:{
            if(Qurey_SPI_Flash_Write(SERV_FLASH_DEBUG)==BUSY)
            {
                return;
            }

            if(W5500_Service.SIPR[3]==101)
            {
                SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(252)*0x1000,ubStep253B_Buffer_Test[0],(unsigned char *)ubStep253B_Buffer_Test);
            }
            else
            {
                SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(252)*0x1000,ubStep253B_Buffer[0],(unsigned char *)ubStep253B_Buffer);
            }
            Auto_Aging.State_WritetoFalsh=30;
            Auto_Aging.Req_WR_M2=FALSE;
            break;}

    case 30:{Uint16 Cnt;
            if(Qurey_SPI_Flash_Write(SERV_FLASH_DEBUG)==BUSY)
            {
                return;
            }

            for(Cnt=0;Cnt<128;Cnt++)
            {
                Buff_To_Byte[Cnt]=0xFF;
            }

            SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(300)*0x1000,128,Buff_To_Byte);
            Auto_Aging.State_WritetoFalsh=31;
            break;}

    case 31:{Uint16 Cnt;
            if(Qurey_SPI_Flash_Write(SERV_FLASH_DEBUG)==BUSY)
            {
                return;
            }

            for(Cnt=0;Cnt<128;Cnt++)
            {
                Buff_To_Byte[Cnt]=0xFF;
            }

            SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(301)*0x1000,128,Buff_To_Byte);

            Auto_Aging.State_WritetoFalsh=0;
            break;}
    }
}

Uint16 Bit_To_Fault_Code_Global[32]={};
Uint16 Bit_To_Fault_Code_Step[32]  ={};
Uint16 Bit_To_Fault_Code_Alarm[32] ={};

Uint16 Bit_To_Fault_Code(void)
{
 Uint16 Cnt,Code;
 Uint32 Mask;
 if(Fault_Code.Err_Global!=0)
 {
     Cnt=0;
     Code=0;
     Mask=0x00000001;
     while((Fault_Code.Err_Global&Mask)==0)
     {
        Mask=Mask<<1;
        Cnt++;
     };
     Code=Bit_To_Fault_Code_Global[Cnt];
 }
 else if(Fault_Code.Err_Step!=0)
 {
     Cnt=0;
     Code=0;
     Mask=0x00000001;
     while((Fault_Code.Err_Step&Mask)==0)
     {
        Mask=Mask<<1;
        Cnt++;
     };
     Code=Bit_To_Fault_Code_Step[Cnt];
 }
 else if(Fault_Code.Alarm!=0)
 {
     Cnt=0;
     Code=0;
     Mask=0x00000001;
     while((Fault_Code.Alarm&Mask)==0)
     {
        Mask=Mask<<1;
        Cnt++;
     };
     Code=Bit_To_Fault_Code_Alarm[Cnt];
 }
 return(Code);
}

void Auto_Aging_Run(void)
{
    switch(Auto_Aging.State)
    {
    case 0:{
            if((W5500_Service.SIPR[3]==100)||(W5500_Service.SIPR[3]==102)||(W5500_Service.SIPR[3]==104)||(W5500_Service.SIPR[3]==106)||(W5500_Service.SIPR[3]==108)||\
               (W5500_Service.SIPR[3]==101)||(W5500_Service.SIPR[3]==103)||(W5500_Service.SIPR[3]==105)||(W5500_Service.SIPR[3]==107)||(W5500_Service.SIPR[3]==109))
            {
                if(Auto_Aging.Step_Aging==STEP_AGING_ERR)
                {
                    Uint32 Temp3=0,Temp2=0,Temp1=0,Temp0=0;

                    SPI_Flash_Read(SERV_FLASH_DEBUG,(Uint32)(300)*0x1000,128);
                    while(Qurey_SPI_Flash_Read(SERV_FLASH_DEBUG)==BUSY);

                    Temp3=Interface_SPI_Flash[SERV_FLASH_DEBUG].Data[4]&0x00FF;
                    Temp2=Interface_SPI_Flash[SERV_FLASH_DEBUG].Data[5]&0x00FF;
                    Temp1=Interface_SPI_Flash[SERV_FLASH_DEBUG].Data[6]&0x00FF;
                    Temp0=Interface_SPI_Flash[SERV_FLASH_DEBUG].Data[7]&0x00FF;
                    Temp0=(Temp3<<24)+(Temp2<<16)+(Temp1<<8)+Temp0;
                    Fault_Code.Err_Global=Temp0;
                    Fault_Code.Err_Global_Bak=0;

                    Temp3=Interface_SPI_Flash[SERV_FLASH_DEBUG].Data[8]&0x00FF;
                    Temp2=Interface_SPI_Flash[SERV_FLASH_DEBUG].Data[9]&0x00FF;
                    Temp1=Interface_SPI_Flash[SERV_FLASH_DEBUG].Data[10]&0x00FF;
                    Temp0=Interface_SPI_Flash[SERV_FLASH_DEBUG].Data[11]&0x00FF;
                    Temp0=(Temp3<<24)+(Temp2<<16)+(Temp1<<8)+Temp0;
                    Fault_Code.Err_Step=Temp0;
                    Fault_Code.Err_Step_Bak=0;

                    Temp3=Interface_SPI_Flash[SERV_FLASH_DEBUG].Data[12]&0x00FF;
                    Temp2=Interface_SPI_Flash[SERV_FLASH_DEBUG].Data[13]&0x00FF;
                    Temp1=Interface_SPI_Flash[SERV_FLASH_DEBUG].Data[14]&0x00FF;
                    Temp0=Interface_SPI_Flash[SERV_FLASH_DEBUG].Data[15]&0x00FF;
                    Temp0=(Temp3<<24)+(Temp2<<16)+(Temp1<<8)+Temp0;
                    Fault_Code.Alarm=Temp0;
                    Fault_Code.Alarm_Bak=0;

                    Auto_Aging.State=6;
                }
                else if(Auto_Aging.Step_Aging==STEP_AGING_READY)
                {
                    Auto_Aging.State=1;
                }
                else
                {
                    Auto_Aging.State=6;
                }
            }
            else
            {
                Auto_Aging.State=6;
            }
            Auto_Aging.Cnt_Delay=0;
            break;}

    case 1:{
            if(++Auto_Aging.Cnt_Delay>=750)//30S
            {
                Auto_Aging.Cnt_Delay=0;
                Auto_Aging.State=2;
            }
            break;}

    case 2:{
            if((WorkStep_Service.Step_State==cWorkStepRunStatus)||(WorkStep_Service.Step_State==cPauseStatus))
            {
                WorkStep_Service.Req_CMD=WORKSTEP_STOP;
            }
            Auto_Aging.Cnt_Delay=0;
            Auto_Aging.State=3;
            break;}

    case 3:{
            if(++Auto_Aging.Cnt_Delay>=4)
            {
                Auto_Aging.Cnt_Delay=0;
                Auto_Aging.State=4;
            }
            break;}

    case 4:{
                Interface_DCDC.Req_Aging=TRUE;

                Protect_Global.Cur_Diff_Over.Num_Check=250;
                if(Auto_Aging.CurDiff_Aging>50000)
                {
                    Auto_Aging.CurDiff_Aging=50000;
                }


                Protect_Global.Cur_Diff_Over.Ref_Value_Diff=Auto_Aging.CurDiff_Aging;

                Protect_Global.Vol_Diff_Over.Ref_Value=50000;
                Protect_Global.Vol_Diff_Over.Num_Check=50;
                Protect_Global.Vol_Diff_Over.Ref_Value_Diff=10000;

                Fault_Code.Err_Global =0;
                Fault_Code.Err_Global_Bak=0;
                Fault_Code.Err_Step=0;
                Fault_Code.Err_Step_Bak=0;
                Fault_Code.Alarm=0;
                Fault_Code.Alarm_Bak=0;

                WorkStep_Service.Req_WorkStep_Index=250;
                WorkStep_Service.Req_CMD=WORKSTEP_RUN;
                Auto_Aging.Cnt_Delay=0;
                Auto_Aging.State=5;
                Auto_Aging.Step_Aging=STEP_AGING_RUN;
                EEPROM_Write_Uint16(cEepromStepAging,Auto_Aging.Step_Aging);
                break;}

        case 5:{
                /*if(DCDC_Service.Now_Mode==DCDC_DCC)
                {
                    Protect_Global.Cur_Diff_Over.Now_Value=Image_Protect.Record.dwOutPutCurrentNew_UP;
                    Protect_Value_Diff(&Protect_Global.Cur_Diff_Over);

                    if(Image_Protect.Record.wOutPutVoltNew_UP<35000)
                    {
                        if(++Auto_Aging.Cnt_CV_Fail>=25)
                        {
                            Auto_Aging.Cnt_CV_Fail=25;
                            Auto_Aging.Flag_CV_Fail=TRUE;
                        }
                    }
                    else
                    {
                        Auto_Aging.Cnt_CV_Fail=0;
                    }
                }*/


                if((DCDC_Service.Now_Mode==DCDC_CV)||(DCDC_Service.Now_Mode==DCDC_DCC))
                {
                    Protect_Global.Vol_Diff_Over.Ref_Value=50000;
                    Protect_Global.Vol_Diff_Over.Protect_EN=TRUE;
                    Protect_Global.Vol_Diff_Over.Now_Value=Data_Sum.Vol_Out;//Image_Protect.Record.wOutPutVoltNew_UP;
                    Protect_Value_Diff(&Protect_Global.Vol_Diff_Over);


                    if((W5500_Service.SIPR[3]==100)||(W5500_Service.SIPR[3]==101)||(W5500_Service.SIPR[3]==102)||(W5500_Service.SIPR[3]==103))
                    {
                        Protect_Global.Cur_Diff_Over.Ref_Value=200000;
                    }
                    else if((W5500_Service.SIPR[3]==104)||(W5500_Service.SIPR[3]==105))
                    {
                        Protect_Global.Cur_Diff_Over.Ref_Value=400000;
                    }
                    else if((W5500_Service.SIPR[3]==106)||(W5500_Service.SIPR[3]==107))
                    {
                        Protect_Global.Cur_Diff_Over.Ref_Value=600000;
                    }
                    else if((W5500_Service.SIPR[3]==108)||(W5500_Service.SIPR[3]==109))
                    {
                        Protect_Global.Cur_Diff_Over.Ref_Value=800000;
                    }

                    Protect_Global.Cur_Diff_Over.Protect_EN=TRUE;
                    Protect_Global.Cur_Diff_Over.Now_Value=Parall_Master.Now_Cur_Total;//Image_Protect.Record.dwOutPutCurrentNew_UP;
                    Protect_Value_Diff(&Protect_Global.Cur_Diff_Over);
                }


                if(WorkStep_Service.Step_State!=cWorkStepRunStatus)
                {
                    if(++Auto_Aging.Cnt_Delay>=50)
                    {
                        Auto_Aging.Cnt_Delay=0;
                        Buff_To_Byte[0]=Bit_To_Fault_Code();
                        Buff_To_Byte[1]=Auto_Aging.Step_Aging;
                        Buff_To_Byte[2]=WorkStep_Service.Step_State;
                        Buff_To_Byte[3]=DCDC_Service.Now_Mode;

                        Buff_To_Byte[4]=(Fault_Code.Err_Global>>24)&0x000000FF;
                        Buff_To_Byte[5]=(Fault_Code.Err_Global>>16)&0x000000FF;
                        Buff_To_Byte[6]=(Fault_Code.Err_Global>>8)&0x000000FF;
                        Buff_To_Byte[7]=(Fault_Code.Err_Global)&0x000000FF;

                        Buff_To_Byte[8]=(Fault_Code.Err_Step>>24)&0x000000FF;
                        Buff_To_Byte[9]=(Fault_Code.Err_Step>>16)&0x000000FF;
                        Buff_To_Byte[10]=(Fault_Code.Err_Step>>8)&0x000000FF;
                        Buff_To_Byte[11]=(Fault_Code.Err_Step)&0x000000FF;

                        Buff_To_Byte[12]=(Fault_Code.Alarm>>24)&0x000000FF;
                        Buff_To_Byte[13]=(Fault_Code.Alarm>>16)&0x000000FF;
                        Buff_To_Byte[14]=(Fault_Code.Alarm>>8)&0x000000FF;
                        Buff_To_Byte[15]=(Fault_Code.Alarm)&0x000000FF;

                        Buff_To_Byte[16]=(DCDC_Service.Fault_Module>>24)&0x000000FF;
                        Buff_To_Byte[17]=(DCDC_Service.Fault_Module>>16)&0x000000FF;
                        Buff_To_Byte[18]=(DCDC_Service.Fault_Module>>8)&0x000000FF;
                        Buff_To_Byte[19]=(DCDC_Service.Fault_Module)&0x000000FF;



                        while(Qurey_SPI_Flash_Write(SERV_FLASH_DEBUG)==BUSY);
                        SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(300)*0x1000,32,Buff_To_Byte);

                        sReplyRecondDataCommand((struct_Image *)&Image_Protect_Bak,CH_TX_UPDATA);

                        while(Qurey_SPI_Flash_Write(SERV_FLASH_DEBUG)==BUSY);
                        SPI_Flash_Write(SERV_FLASH_DEBUG,(Uint32)(301)*0x1000,112,&TCP_Socket[SERV_TCP_WORK].Data_TX[CH_TX_UPDATA].Data[0]);

                        if((Fault_Code.Err_Global!=0)||(Fault_Code.Err_Step!=0)||(Fault_Code.Alarm!=0)||(DCDC_Service.Fault_Module!=0))
                        {
                            //if((Auto_Aging.Flag_CV_Fail==TRUE)&&((Fault_Code.Err_Global&cOPCOverDiffFault)!=0))
                            //{
                                //CVģ�鹤������������DCCģ����ϣ�DCCģ���ж�Ϊ�ϻ�δ��ɣ�����ģ���ϻ����ϱ�־
                            //    Auto_Aging.Step_Aging=STEP_AGING_ERR_SOURCE;
                            //    EEPROM_Write_Uint16(cEepromStepAging,Auto_Aging.Step_Aging);
                            //}
                            //else
                            {
                                //�������ϣ���ģ���ϻ����ϱ�־
                                Auto_Aging.Step_Aging=STEP_AGING_ERR;
                                EEPROM_Write_Uint16(cEepromStepAging,Auto_Aging.Step_Aging);
                            }
                        }
                        else
                        {
                            //�ϻ�������������
                            Auto_Aging.Step_Aging=STEP_AGING_OK;
                            EEPROM_Write_Uint16(cEepromStepAging,Auto_Aging.Step_Aging);
                        }
                        Auto_Aging.State=6;
                    }
                }
                else
                {
                    Auto_Aging.Cnt_Delay=0;
                }

                break;}

        case 6:{
                break;}
        }
}



void Auto_Aging_Init(void)
{
    Auto_Aging.State=0;
    Auto_Aging.Cnt_Delay=0;
    Auto_Aging.Req_WR_M1=FALSE;
    Auto_Aging.Req_WR_M2=FALSE;
    Auto_Aging.State_WritetoFalsh=0;
    Auto_Aging.Flag_CV_Fail=FALSE;
    Auto_Aging.Cnt_CV_Fail=0;
    Auto_Aging.Step_Aging=EEPROM_Read_Uint16(cEepromStepAging);
    Auto_Aging.CurDiff_Aging=EEPROM_Read_Uint16(cEepromCurDiffAging);
}

//File end



