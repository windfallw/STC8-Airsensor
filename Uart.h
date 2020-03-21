#ifndef __UART_H_
#define __UART_H_

#include "STC8.H"
//#include <intrins.h>  //加入此头文件后,可使用_nop_库函数
#include <string.h>   //加入此头文件后,可使用strstr库函数
#include <stdio.h>

#define MAIN_Fosc		11059200L	//定义主时钟

#define BAUD 115200//波特率
#define T_MS  5 //定时时间常量，单位ms
#define T1TMS   (T_MS*MAIN_Fosc/1000)       //1T模式下  
#define T12TMS  (T_MS*MAIN_Fosc/1000/12)    //12T模式下 

#define S2_S  0x01
#define S2RI 0x01
#define S2TI 0x02
#define S3RI 0x01
#define S3TI 0x02
#define S4RI 0x01
#define S4TI 0x02

sbit led=P0^7;     //RGB蓝色LED用IO口P07
uchar cnt = 0;

//51(8位单片机)里面
//int最大表示-32768~+32767
//long占四个字节 范围:-2147483648~+2147483647
//float占四个字节 范围:3.40E+38 ~ +3.40E+38
//double占8个字节 范围:-1.79E+308 ~ +1.79E+308

//*128字节内部直接访问(DATA)
//*128字节内部间接访问(IDATA)
//*8192字节内部扩展(内部XDATA)
//*外部最大可扩展64K字节RAM(外部XDATA)

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