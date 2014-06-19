#ifndef GUI_H
#define GUI_H
#include "def.h"



/*GUI函数*/
void GUI_Clear(uint color);	//清屏
void GUI_Point(uchar x, uint y, uint color);//画点
void GUI_HLine(uchar x, uint y, uchar length, uint color);//画横线 
void GUI_SLine(uchar x, uint y, uint high, uint color);//画竖线
void GUI_line(uint x1,uint y1,uint x2,uint y2,uint color);//画直线
//void GUI_DisPicture(uchar x, uint y, uchar length, uint high);//显示图片(图标)
void GUI_DisPicture(unsigned int x,unsigned int y,unsigned int width,unsigned int height,unsigned char pic[]); //显示图片(图标)
void GUI_sprintf_char(unsigned int x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor); //显示英文或数字字符
void GUI_sprintf_hz1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor);//显示16x16单个汉字
void GUI_sprintf_hzstr16s(unsigned int x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);//显示英文字符串或16X16汉字
void GUI_sprintf_hz3232(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor);//显示32x32单个汉字
void GUI_sprintf_hz3232s(unsigned int x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);//显示32x32汉字串
void GUI_sprintf_ZM3216(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor);//显示16x32字母
void GUI_sprintf_ZM3216s(unsigned int x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);//显示16x32字母串
void GUI_box(uchar sx,uint sy,uchar ex,uint ey,uint color);//画实心矩形
void GUI_rectangle( uchar sx,uint sy,uchar ex,uint ey,uint color);//画空心矩形
void GUI_sprintf_chartodec(uchar x,uint y,uchar dat,uint color,uint b_color);//无符号字符型数以十进制形式显示
void GUI_wrlval(uchar x, uint y,unsigned long num,uchar bits,uchar dp,uint color,uint b_color);//以十进制形式显示长变量
void GUI_sprintf_chartohex(uchar x, uint y,uchar dat, uint color,uint b_color);






/*定义常用颜色的颜色码*/
#define Red      0xf800	//红
#define Yellow   0xffe0	//黄
#define Green    0x07e0	//绿
#define Cyan     0x07ff	//青
#define Blue     0x001f	//蓝
#define Purple   0xf81f	//紫
#define Black    0x0000	//黑
#define White    0xffff	//白
#define Gray     0x7bef	//灰
#endif
















