#ifndef __variable_h_
#define __variable_h_

//sprintf %d���� %u�޷�������
//b ����Ϊ��������Ϊ���������
//c ����Ϊ��������Ϊ�ַ���ʾ���(ASCII��)
//d ����Ϊ��������Ϊ�������
//e ����Ϊ���������
//f ����Ϊ˫���Ȳ���Ϊ���������
//o ����Ϊ��������Ϊ�˽��������
//s ����Ϊ�ַ�����Ϊ�ַ������
//u ����Ϊ�޷����������
//g �����Զ�ѡ����ʵı�ʾ��
//p ����Ϊָ���ֵ
//x ����Ϊ��������Ϊ����Сд��ĸa-f��ʮ�����������
//X ����Ϊ��������Ϊ���д�д��ĸA-F��ʮ�����������

//================�ⲿ�жϴ���ģ��================
sbit Switch=P5^5;
uchar Touch=0;
uchar ATK_GPS=0;
uchar Pms7003=0;
uchar Esp8266=0;
extern void DisPlay_LCD();
//================================================

//=======================================================
//����1 P3.0 P3.1 or P3.6 P3.7 or P1.6 P1.7 or P4.3 P4.4
//����2 P1.0 P1.1 or P4.0 P4.2
//����3 P0.0 P0.1 or P5.0 P5.1
//����4 P0.2 P0.3 or P5.2 P5.3
//=======================================================

//===================================================================================================
//����1�ӵ��ԵĴ��ڵ������������������� M(0-9)(0-9)\r\n �ܹ���λ,numΪM00-M99Ҳ����˵������100��ģʽ��
uchar Rec[10]="\0";
uchar Cmd[5]="\0";//��ȡǰ��λ������
uchar Com1=0;
uchar Com2=0;
uchar Com3=0;
uchar Com4=0;
//===================================================================================================

//=================����2GPSģ��======================
//===============��γ��γ��������====================
uchar GPSRMC[100]="\0";
uchar valid;

uchar UTC_date[20]="\0";//6 10 11 12
uchar year[10]={'2','0'};
uchar month[10]="\0";
uchar day[10]="\0";

uchar UTC_time[20]="\0";
uchar hour[10]="\0";
uchar minute[10]="\0";
uchar sec[10]="\0";

uchar latitude[20]="\0";//γ��
uchar latitude_d[10]="\0";//�ȡ�
uchar latitude_m[10]="\0";//�֡�
uchar NS;

uchar longitude[20]="\0";//����
uchar longitude_d[10]="\0";//�ȡ�
uchar longitude_m[10]="\0";//�֡�
uchar WE;

uint  Calsum=0;
uchar cCalsum[15]="\0";
uchar Chesum[15]="\0";    
extern void deal_data();
//===================================================

//================����3AirSensorģ��================
uchar AirSensor[50]="\0";//Э���ܳ���32�ֽ�
uchar strTemp[20]="\0"; //�ݴ�
uchar FrameHeader[2]= {0x42,0x4d}; //��ʼ��1 ��ʼ��2

uint FrameLen;//֡����=2x13+2(����+У��λ)
uchar cFrameLen[10]="\0";

uint PM1_0CF1=0;
uint PM2_5CF1=0;
uint PM10CF1=0;
uchar cPM1_0CF1[10]="\0";
uchar cPM2_5CF1[10]="\0";
uchar cPM10CF1[10]="\0";

uint PM1_0AE=0;
uint PM2_5AE=0;
uint PM10AE=0;
uchar cPM1_0AE[10]="\0";
uchar cPM2_5AE[10]="\0";
uchar cPM10AE[10]="\0";

uint Gt0_3um=0;
uint Gt0_5um=0;
uint Gt1_0um=0;
uint Gt2_5um=0;
uint Gt5_0um=0;
uint Gt10um=0;
uchar cGt0_3um[10]="\0";
uchar cGt0_5um[10]="\0";
uchar cGt1_0um[10]="\0";
uchar cGt2_5um[10]="\0";
uchar cGt5_0um[10]="\0";
uchar cGt10um[10]="\0";

uchar Version=0;
uchar ErrorCode=0;

uint Checksum=1;
uint CalChecksum=0;
uchar cChecksum[10]="\0";
uchar cCalChecksum[10]="\0";
extern void SendAirQuality();
//==================================================

uchar Esp[100]="\0";//���մ���4ESP8266WIFIģ����Ϣ

#endif