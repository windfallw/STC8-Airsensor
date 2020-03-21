#ifndef __main_h_
#define __main_h_

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

//=======================================================
//����1 P3.0 P3.1 or P3.6 P3.7 or P1.6 P1.7 or P4.3 P4.4
//����2 P1.0 P1.1 or P4.0 P4.2
//����3 P0.0 P0.1 or P5.0 P5.1
//����4 P0.2 P0.3 or P5.2 P5.3
//=======================================================



//================�ⲿ�жϴ���ģ��================
sbit Switch=P5^5;
//----------������----------
char xdata Touch=0;
uchar ATK_GPS=0;
uchar Pms7003=0;
uchar ESP8266=0;
//--------------------------
uchar strTemp[50]="\0"; //�ݴ�
extern void DisPlay_LCD();
//================================================

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

//uchar UTC_date[20]="\0";//6 10 11 12
uchar year[10]= {'2','0'};
uchar month[10]="\0";
uchar day[10]="\0";

//uchar UTC_time[20]="\0";
uchar hour[10]="\0";
uchar minute[10]="\0";
uchar sec[10]="\0";

//uchar latitude[20]="\0";//γ��
uchar latitude_d[10]="\0";//�ȡ�
uchar latitude_m[10]="\0";//�֡�
uchar NS;

//uchar longitude[20]="\0";//����
uchar longitude_d[10]="\0";//�ȡ�
uchar longitude_m[10]="\0";//�֡�
uchar WE;

uint  Calsum=0;
uchar cCalsum[15]="\0";
uchar Chesum[15]="\0";
extern void deal_data();
//===================================================

//================����3AirSensorģ��================
uchar AirSensor[200];//Э���ܳ���32�ֽ�
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

//==================����4Esp8266ģ��==================
#define test "AT\r\n"
#define Connect_Server "AT+CIPSTART=\"TCP\",\"192.168.31.10\",80\r\n"
#define Set_Cip "AT+CIPMODE=1\r\n"
#define Enter_Cip "AT+CIPSEND\r\n"

#define GPS_Header \
				 "POST /api/gps HTTP/1.1\r\n" \
				 "Host: 192.168.31.10:80\r\n" \
			   "Content-Type: application/json\r\n" \
         "cache-control: no-cache\r\n" \
			   "content-length: %d\r\n\r\n"

#define Air_Header \
				 "POST /api/air HTTP/1.1\r\n" \
				 "Host: 192.168.31.10:80\r\n" \
			   "Content-Type: application/json\r\n" \
         "cache-control: no-cache\r\n" \
			   "content-length: %d\r\n\r\n"
               
#define GPS_data1 "{\"year\":\"%s\",\"month\":\"%s\",\"day\":\"%s\""
#define GPS_data2 "%s,\"lae1\":\"%s\",\"lae2\":\"%s\""
#define GPS_data3 "%s,\"loe1\":\"%s\",\"loe2\":\"%s\"}\r\n"

#define Air_data1 "{\"PM1_0CF1\":\"%s\",\"PM2_5CF1\":\"%s\""
#define Air_data2 "%s,\"PM10CF1\":\"%s\",\"PM1_0AE\":\"%s\""
#define Air_data3 "%s,\"PM2_5AE\":\"%s\",\"PM10AE\":\"%s\""
#define Air_data4 "%s,\"Gt0_3um\":\"%s\",\"Gt0_5um\":\"%s\""
#define Air_data5 "%s,\"Gt1_0um\":\"%s\",\"Gt2_5um\":\"%s\""
#define Air_data6 "%s,\"Gt5_0um\":\"%s\",\"Gt10um\":\"%s\"}\r\n"

uchar ESP[100]="\0";//���մ���4ESP8266WIFIģ����Ϣ
uchar ESP_UP_Header[150]="\0";
uchar ESP_UP_DATA[300]="\0";
//extern void ESP_Initialize();//��ʼ��
extern void ESP_SendGPS();
extern void ESP_SendAIR();
//====================================================



#endif