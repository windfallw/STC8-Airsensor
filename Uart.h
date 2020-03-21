#ifndef __UART_H_
#define __UART_H_

#include "STC8.H"
//#include <intrins.h>  //�����ͷ�ļ���,��ʹ��_nop_�⺯��
#include <string.h>   //�����ͷ�ļ���,��ʹ��strstr�⺯��
#include <stdio.h>

#define MAIN_Fosc		11059200L	//������ʱ��

#define BAUD 115200//������
#define T_MS  5 //��ʱʱ�䳣������λms
#define T1TMS   (T_MS*MAIN_Fosc/1000)       //1Tģʽ��  
#define T12TMS  (T_MS*MAIN_Fosc/1000/12)    //12Tģʽ�� 

#define S2_S  0x01
#define S2RI 0x01
#define S2TI 0x02
#define S3RI 0x01
#define S3TI 0x02
#define S4RI 0x01
#define S4TI 0x02

sbit led=P0^7;     //RGB��ɫLED��IO��P07
uchar cnt = 0;

//51(8λ��Ƭ��)����
//int����ʾ-32768~+32767
//longռ�ĸ��ֽ� ��Χ:-2147483648~+2147483647
//floatռ�ĸ��ֽ� ��Χ:3.40E+38 ~ +3.40E+38
//doubleռ8���ֽ� ��Χ:-1.79E+308 ~ +1.79E+308

//*128�ֽ��ڲ�ֱ�ӷ���(DATA)
//*128�ֽ��ڲ���ӷ���(IDATA)
//*8192�ֽ��ڲ���չ(�ڲ�XDATA)
//*�ⲿ������չ64K�ֽ�RAM(�ⲿXDATA)

extern void Timer0Init(void);
extern void UartInit1(void);
extern void UartInit2(void);
extern void UartInit3(void);
extern void UartInit4(void);
extern void SendChar1(uint8 dat);
extern void SendString1(uint8 p[],uint8 len);
extern void SendChar2(uint8 dat);
extern void SendString2(uint8 p[],uint8 len);
extern void SendChar3(uint8 dat);
extern void SendString3(uint8 p[],uint8 len);
extern void SendChar4(uint8 dat);
extern void SendString4(uint8 p[],uint8 len);
extern void sendData(uint8 p[]);
extern void sendData4(uint8 p[]);
extern void SendEndl();

#endif