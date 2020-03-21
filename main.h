#ifndef __main_h_
#define __main_h_

//sprintf %d整数 %u无符号整数
//b 解释为整数并作为二进制输出
//c 解释为整数并作为字符表示输出(ASCII码)
//d 解释为整数并作为整数输出
//e 解释为浮点数输出
//f 解释为双精度并作为浮点数输出
//o 解释为整数并作为八进制数输出
//s 解释为字符串并为字符串输出
//u 解释为无符号整数输出
//g 解释自动选择合适的表示法
//p 解释为指针的值
//x 解释为整数并作为带有小写字母a-f的十六进制数输出
//X 解释为整数并作为带有大写字母A-F的十六进制数输出

//=======================================================
//串口1 P3.0 P3.1 or P3.6 P3.7 or P1.6 P1.7 or P4.3 P4.4
//串口2 P1.0 P1.1 or P4.0 P4.2
//串口3 P0.0 P0.1 or P5.0 P5.1
//串口4 P0.2 P0.3 or P5.2 P5.3
//=======================================================



//================外部中断触控模块================
sbit Switch=P5^5;
//----------计数用----------
char xdata Touch=0;
uchar ATK_GPS=0;
uchar Pms7003=0;
uchar ESP8266=0;
//--------------------------
uchar strTemp[50]="\0"; //暂存
extern void DisPlay_LCD();
//================================================

//===================================================================================================
//串口1接电脑的串口调试助手用来接收命令 M(0-9)(0-9)\r\n 总共五位,num为M00-M99也就是说可以有100个模式。
uchar Rec[10]="\0";
uchar Cmd[5]="\0";//截取前三位并保存
uchar Com1=0;
uchar Com2=0;
uchar Com3=0;
uchar Com4=0;
//===================================================================================================

//=================串口2GPS模块======================
//===============北纬南纬东经西经====================
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

//uchar latitude[20]="\0";//纬度
uchar latitude_d[10]="\0";//度°
uchar latitude_m[10]="\0";//分′
uchar NS;

//uchar longitude[20]="\0";//经度
uchar longitude_d[10]="\0";//度°
uchar longitude_m[10]="\0";//分′
uchar WE;

uint  Calsum=0;
uchar cCalsum[15]="\0";
uchar Chesum[15]="\0";
extern void deal_data();
//===================================================

//================串口3AirSensor模块================
uchar AirSensor[200];//协议总长度32字节
uchar FrameHeader[2]= {0x42,0x4d}; //起始符1 起始符2

uint FrameLen;//帧长度=2x13+2(数据+校验位)
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

//==================串口4Esp8266模块==================
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

uchar ESP[100]="\0";//接收串口4ESP8266WIFI模块信息
uchar ESP_UP_Header[150]="\0";
uchar ESP_UP_DATA[300]="\0";
//extern void ESP_Initialize();//初始化
extern void ESP_SendGPS();
extern void ESP_SendAIR();
//====================================================



#endif