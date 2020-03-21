#include "uart.h"

void Timer0Init(void)
{
	AUXR |= 0x80;                   //定时器0为1T模式
	//AUXR &= 0x7F;                   //定时器0为12T模式
	TMOD &= 0xF8;                   //定时器0设置为定时方式，工作模式为16位自动重装模式
	TMOD &= 0xF7;                   //定时器0门控位GATE设置为0
	//TMOD |= 0x08;                   //定时器0门控位GATE设置为1
	TL0 = (65536-T1TMS);            //1T模式下初始装载值       
	TH0 = (65536-T1TMS) >> 8;       //1T模式下初始装载值  
	//TL0 = (65536-T12TMS);            //12T模式下初始装载值       
	//TH0 = (65536-T12TMS) >> 8;       //12T模式下初始装载值  
	TR0 = 1;                        //定时器0开始计时
	ET0 = 1;                        //使能定时器0的溢出中断允许位
}

void UartInit1(void)//115200bps@11.0592MHz
{
    SCON = 0x50;		//8位数据,可变波特率
    AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
    AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
    T2L = 0xE8;		//设定定时初值
    T2H = 0xFF;		//设定定时初值
    AUXR |= 0x10;		//启动定时器2

    ES = 1;     // 串口1中断打开
    IE2 |= 0x01;// 串口2中断打开
    IE2 |= 0x08;// 串口3中断打开
    IE2 |= 0x10;// 串口4中断打开
    EA = 1;     // 总中断打开
}

void UartInit2(void)//115200bps@11.0592MHz
{
//  P_SW2 = 0x00; // RXD3/P0.0, TXD3/P0.1
//  P_SW2 = 0x01;   //RXD2_2/P4.0, TXD2_2/P4.2
    S2CON = 0x50;		//8位数据,可变波特率
}

void UartInit3(void)//9600bps@11.0592MHz
{
    S3CON = 0x10;		//8位数据,可变波特率
    S3CON |= 0x40;		//串口3选择定时器3为波特率发生器
    T4T3M |= 0x02;		//定时器3时钟为Fosc,即1T
    T3L = 0xE0;		//设定定时初值
    T3H = 0xFE;		//设定定时初值
    T4T3M |= 0x08;		//启动定时器3
}

void UartInit4(void)//115200bps@11.0592MHz
{
    S4CON = 0x10;		//8位数据,可变波特率
    S4CON &= 0xBF;		//串口4选择定时器2为波特率发生器
}

void SendChar1(uint8 dat)
{
    SBUF = dat;                 //写数据到UART数据寄存器
    while(TI == 0);             //在停止位没有发送时，TI为0即一直等待
    TI = 0;                     //清除TI位（该位必须软件清零）
}

void SendString1(uint8 p[],uint8 len)
{
    uint8 i;
    for(i=0; i<len; i++)
    {
        SendChar1(p[i]);
    }
}

void SendChar2(uint8 dat)
{
    S2BUF = dat;                 //写数据到UART数据寄存器
    while(!(S2CON&S2TI));        //在停止位没有发送时，S2TI为0即一直等待
    S2CON&=~S2TI;                //清除S2CON寄存器对应S2TI位（该位必须软件清零）
}

void SendString2(uint8 p[],uint8 len)
{
    uint8 i;
//    IE2 &= 0xFE; 			          // 串口2中断关闭
    for(i=0; i<len; i++)
    {
        SendChar2(p[i]);
    }
//    IE2 |= 0x01;                // 串口2中断打开
}

void SendChar3(uint8 dat)
{
    S3BUF = dat;                 //写数据到UART数据寄存器
    while(!(S3CON&S3TI));        //在停止位没有发送时，S3TI为0即一直等待
    S3CON&=~S3TI;                //清除S3CON寄存器对应S3TI位（该位必须软件清零）
}

void SendString3(uint8 p[],uint8 len)
{
    uint8 i;
//    IE2 &= 0xF7; 			               // 串口3中断关闭
    for(i=0; i<len; i++)
    {
        SendChar3(p[i]);
    }
//    IE2 |= 0x08;                     // 串口3中断打开
}


void SendChar4(uint8 dat)
{
    S4BUF = dat;                 //写数据到UART数据寄存器
    while(!(S4CON&S4TI));        //在停止位没有发送时，S4TI为0即一直等待
    S4CON&=~S4TI;                //清除S4CON寄存器对应S4TI位（该位必须软件清零）
}

void SendString4(uint8 p[],uint8 len)
{
    uint8 i;
//    IE2 &= 0xEF; 			               //串口4中断关闭
    for(i=0; i<len; i++)
    {
        SendChar4(p[i]);
    }
//    IE2 |= 0x10;                     //串口4中断打开
}

void sendData(uint8 p[])
{
    while(*p != '\0')
    {
        SBUF = *p;							//发送第一个字符
        while(!TI);							//串口数据发送完毕判断
        p++;										//下一个字符
        TI = 0;									//发送标志位清零
    }

}

void sendData4(uint8 p[])
{
//    IE2 &= 0xEF; 			               //串口4中断关闭
    while(*p != '\0')
    {
        S4BUF = *p;							//发送第一个字符
        while(!(S4CON&S4TI));	  //串口数据发送完毕判断
        p++;										//下一个字符
        S4CON&=~S4TI;           //清除S4CON寄存器对应S4TI位（该位必须软件清零）
    }
//    IE2 |= 0x10;                     //串口4中断打开    
}


void SendEndl()
{
    SendChar1('\r');
    SendChar1('\n');
}
