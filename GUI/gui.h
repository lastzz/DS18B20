#ifndef GUI_H
#define GUI_H
#include "def.h"



/*GUI����*/
void GUI_Clear(uint color);	//����
void GUI_Point(uchar x, uint y, uint color);//����
void GUI_HLine(uchar x, uint y, uchar length, uint color);//������ 
void GUI_SLine(uchar x, uint y, uint high, uint color);//������
void GUI_line(uint x1,uint y1,uint x2,uint y2,uint color);//��ֱ��
//void GUI_DisPicture(uchar x, uint y, uchar length, uint high);//��ʾͼƬ(ͼ��)
void GUI_DisPicture(unsigned int x,unsigned int y,unsigned int width,unsigned int height,unsigned char pic[]); //��ʾͼƬ(ͼ��)
void GUI_sprintf_char(unsigned int x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor); //��ʾӢ�Ļ������ַ�
void GUI_sprintf_hz1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor);//��ʾ16x16��������
void GUI_sprintf_hzstr16s(unsigned int x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);//��ʾӢ���ַ�����16X16����
void GUI_sprintf_hz3232(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor);//��ʾ32x32��������
void GUI_sprintf_hz3232s(unsigned int x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);//��ʾ32x32���ִ�
void GUI_sprintf_ZM3216(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor);//��ʾ16x32��ĸ
void GUI_sprintf_ZM3216s(unsigned int x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);//��ʾ16x32��ĸ��
void GUI_box(uchar sx,uint sy,uchar ex,uint ey,uint color);//��ʵ�ľ���
void GUI_rectangle( uchar sx,uint sy,uchar ex,uint ey,uint color);//�����ľ���
void GUI_sprintf_chartodec(uchar x,uint y,uchar dat,uint color,uint b_color);//�޷����ַ�������ʮ������ʽ��ʾ
void GUI_wrlval(uchar x, uint y,unsigned long num,uchar bits,uchar dp,uint color,uint b_color);//��ʮ������ʽ��ʾ������
void GUI_sprintf_chartohex(uchar x, uint y,uchar dat, uint color,uint b_color);






/*���峣����ɫ����ɫ��*/
#define Red      0xf800	//��
#define Yellow   0xffe0	//��
#define Green    0x07e0	//��
#define Cyan     0x07ff	//��
#define Blue     0x001f	//��
#define Purple   0xf81f	//��
#define Black    0x0000	//��
#define White    0xffff	//��
#define Gray     0x7bef	//��
#endif
















