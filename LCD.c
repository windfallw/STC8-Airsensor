#include "LCD.h"

//void Busy()
//{
//  uint8 busy;
//  do
//  {
//      E = 0;           //0为关闭使能端,1为打开使能端
//      RS = 0;          //1为指令,0为数据
//      RW = 1;          //1为读,0为写
//      delay_100us(2);
//      E = 1;           //0为关闭使能端,1为打开使能端
//      P2M0=0x00;
//      P2M1=0x00;	     //设置P2.0~P2.7为准双向口
//      busy=P2;         //读取P2状态
//      delay_100us(2);
//      E = 0;           //0为关闭使能端,1为打开使能端
//  } 
//  while(busy&0x80);  //判断BUSY位是否工作:1为内部在工作,0为正常状态
//}

void delay_100us(uint16 t)
{
    uint16 i,j;
    for(i=0; i<t;  i++)
    {
        for(j=0; j<10; j++);
    }
}

void Write_Data(uint8 k)
{
//    Busy();
    E =1;         //0为关闭使能端,1为打开使能端
    RS=1;         //1为指令,0为数据
    RW=0;         //1为读,0为写
    P2M1 = 0;	    //设置P2.0~P2.7为推挽输出
    P2M0 = 0xff;	//设置P2.0~P2.7为推挽输出
    P2=k;         //输入数据K到DATA
    delay_100us(2);
    E =0;         //0为关闭使能端,1为打开使能端
    delay_100us(2);
}

void Write_Cmd(uint8 cmd)
{
//    Busy();
    E=1;          //0为关闭使能端,1为打开使能端
    RS=0;         //1为指令,0为数据
    RW=0;         //1为读,0为写
    P2M1 = 0;	    //设置P2.0~P2.7为推挽输出
    P2M0 = 0xff;	//设置P2.0~P2.7为推挽输出
    P2=cmd;       //输入命令cmd到DATA
    delay_100us(2);
    E=0;          //0为关闭使能端,1为打开使能端
    delay_100us(2);
}

void Disp(uint8 y,uint8 x,uint8 i,uint8 *z)
{
    uint8 Address;
    if(y==1)
    {
        Address=0x80+x;
    }
    //Y判断第几行,X判断第几列,0x80为液晶行初始地址
    if(y==2) {
        Address=0x90+x;
    }
    if(y==3) {
        Address=0x88+x;
    }
    if(y==4) {
        Address=0x98+x;
    }
    Write_Cmd(Address);           //写入地址命令到LCD12864
    while(i)                      //写入显示数据的大小
    {
        Write_Data(*(z++));         //写入显示数据到LCD12864
        i--;
    }
}

void DispS(uint8 y,uint8 x,uint8 p[])
{
    uint8 Address;
    if(y==1)
    {
        Address=0x80+x;
    }
    if(y==2)
    {
        Address=0x90+x;
    }
    if(y==3)
    {
        Address=0x88+x;
    }
    if(y==4)
    {
        Address=0x98+x;
    }
    Write_Cmd(Address);
    while(*p != '\0')
    {
        Write_Data(*p);
        p++;
    }
}

void Init_Lcd(void)
{
    Write_Cmd(0x30);   //基本指令集
    Write_Cmd(0x02);   // 地址归位
    Write_Cmd(0x0c);   //整体显示打开,游标关闭
    Write_Cmd(0x06);   //游标右移
    Write_Cmd(0x80);   //设定显示的起始地址
    Write_Cmd(0x01);   //清除显示
}