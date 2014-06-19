

#include  "stc12.h"
#include  "gui.h"
#include  "def.h"
#include  "tft.h"			
//#include  "bmp.h"			   //ͼƬ����
#include  "hz16x16.h"		  //����16X16
#include  "zifu8x16.h"
#include  "zifu8x12.h"
#include  "hz32x32.h"
#include  "zm16x32.h"



/************************************
����
��ڲ����� b_color�Ǳ�����ɫ��
���ڲ���: ��
˵����ʹ�ñ�����ɫ���TFTģ����Ļ��ȫ����ʾ���ݡ�
*************************************/
void GUI_Clear(uint color)
{
	int i,j;
	Address_set(0,0,239,319);
    for(i=0;i<320;i++)
	 {
	  for (j=0;j<240;j++)
	   	{
        	 Lcd_Write_Data16(color);
	    }

	  }
}

/*********************************************
����
��ڲ����� (x��y)�ǵ�����꣬color �ǵ����ɫ��
���ڲ���: ��
˵������ָ������ɫ��ָ��������λ���ϻ���һ���㡣
**********************************************/
void GUI_Point(uchar x, uint y, uint color)
{  
	Address_setxy(x,y);
	Lcd_Write_Data16(color);
}





/**********************************************************
������
��ڲ����� (x��y)�Ǻ���������꣬length�Ǻ��߳��ȣ�color �Ǻ�����ɫ��
���ڲ���: ��
˵������ָ������ɫ��ָ��λ���ϻ���ָ�����ȵ�һ�����ߡ�
************************************************************/
void GUI_HLine(uchar x, uint y, uchar length, uint color) 
{  
	Address_set(x,y,x+length-1,y);
	do
	{  
		Lcd_Write_Data16(color);//�����ʾ�����ˮƽ��
		length--;
	}while(length);
}


/**********************************************************
������
��ڲ����� (x��y)������������꣬high ���߸߶ȣ�color ��������ɫ��
���ڲ���: ��
˵������ָ������ɫ��ָ��λ���ϻ���ָ�����ȵ�һ�����ߡ�
************************************************************/
void GUI_SLine(uchar x, uint y, uint high, uint color) 
{  
   Address_set(x,y,x,y+high-1);
   do
   {  
		Lcd_Write_Data16(color);// �����ʾ�������ֱ��
		high--;
   }while(high);	
}



/******************************************************************** 
��ֱ�ߣ����Ի����ⷽ��ֱ�ߣ��������ߡ����ߡ�б�ߣ���
��ڲ����� (x1,y1)���, (x2,y2)�յ�, color��ɫ��
���ڲ���: ��
˵������ָ������ɫ��ָ��������仭��һ��ֱ�ߡ�
***********************************************************************/
void GUI_line(uint x1,uint y1,uint x2,uint y2,uint color)  
{  
    uint t;  
    int xerr=0,yerr=0,delta_x,delta_y,distance;  
    int incx,incy;  
    uint row,col;  
    delta_x = x2-x1;//������������  
    delta_y = y2-y1;  
    col=x1;  
    row=y1;  
    if(delta_x>0) incx=1;//���õ�������  
    else   
    {  
        if(delta_x==0) incx=0;//��ֱ��  
        else {incx=-1;delta_x=-delta_x;}  
    }  
    if(delta_y>0)incy=1;  
    else  
    {  
        if(delta_y==0) incy=0;//ˮƽ��  
        else {incy=-1;delta_y=-delta_y;}  
    }  
    if(delta_x>delta_y) distance=delta_x;//ѡȡ��������������  
    else distance=delta_y;  

    for(t=0;t<=distance+1;t++)  
	{                                     //�������  
	    GUI_Point(col, row, color);
        xerr+=delta_x;  
        yerr+=delta_y;  
      	if(xerr>distance)  
        {  
            xerr-=distance;  
            col+=incx;  
        }  
        if(yerr>distance)  
        {  
            yerr-=distance;  
            row+=incy;  
        }  
    }  
}


/**********************************************************
��ʾͼƬ(ͼ��)
��ڲ�����(x��y)�ǿ�ʼ������꣬length��ͼƬ���ȣ�high��ͼƬ�߶ȡ�//pic ͼƬ�����ָ��
���ڲ���: ��
˵������ָ��λ������ʾ���ȶ����ͼƬ��
Ҫ��ʾ��ͼƬ���ȶ�����bmp.h�е�pic[]�����У�
������޸�ͼƬ��С�����ݣ����޸�bmp.h�е�pic[]���飬
������Image2Lcd��������Ҫ��ʾ��ͼ���Զ�ת��Ϊ�������ݡ� 
***********************************************************	 
//void GUI_DisPicture(uchar x, uint y, uchar length, uint high ,const uchar *pic)
void GUI_DisPicture(uchar x, uint y, uchar length, uint high)
{
   uint temp=0,tmp=0,num=0;
	Address_set(x,y,x+length-1,y+high-1);
	num=length*high*2;
	do
	{  
	   //temp=pic[tmp]|( pic[tmp+1]<<8);
	   temp=pic1[tmp+1];
	   temp=temp<<8;
	   temp=temp|pic1[tmp];
	  Lcd_Write_Data16(temp);//�����ʾ
	   tmp+=2;
	}while(tmp<num);
}
					   */
			  
void GUI_DisPicture(unsigned int x,unsigned int y,unsigned int width,unsigned int height,unsigned char pic[])
{
 unsigned int i,n;
 Address_set(x,y,x+width-1,y+height-1);
 n=width*height;
 for(i=0;i<n;i++)
 {
  Lcd_Write_Data(pic[i*2+1],pic[i*2]);
 }
}


/*********************************************
��ʾӢ�Ļ������ַ�
��ڲ�����(x��y) ����ʾ���ݵ����Ͻ����꣬c����ʾ��Ӣ���ַ���
          color:��ɫ,b_color:������ɫ��
���ڲ���: ��
˵������ָ��λ������ʾ����Ӣ���ַ��������ַ���
**********************************************/
void GUI_sprintf_char(unsigned int x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor)	
{  
	unsigned char i,j;
	unsigned char *temp=zifu816;    //temp��*temp�ĵ�ַ  ����temp����zifu���׵�ַ 
    Address_set(x,y,x+7,y+15); //��������      
	                    
	temp+=(value-32)*16;   //ȷ��Ҫ��ʾ��ֵ
				   //�����õ���ascii��  ǰ32��asciiû�д���zifu���� ����Ҫ��32
	               //���� ÿ���ַ���12���ֽ���ʾ �����ڳ���12  ���Ƕ�Ӧ����ʾλ���׵�ַ
	for(j=0;j<16;j++)
	{
		for(i=0;i<8;i++)		    //�Ⱥ�ɨ
		{ 		     
		 	if((*temp&(1<<(7-i)))!=0)					//��1 ���� Ȼ���Ӧλ�������� 
			{
				Lcd_Write_Data(dcolor>>8,dcolor);
			} 
			else
			{
				Lcd_Write_Data(bgcolor>>8,bgcolor);
			}  
 
		}
		temp++;
	 }
}


/*********************************************
��ʾ16x16��������
��ڲ�����(x��y) ����ʾ���ݵ����Ͻ����꣬*s��Ӣ���ַ���ָ�룬
          color:��ɫ,b_color:������ɫ��
���ڲ���: ��
˵������ָ��λ������ʾӢ���ַ�����
**********************************************/
void GUI_sprintf_hz1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor){
	unsigned int i,j,k;
																//c[2] ��Ҫ��ʾ���� �������ֽڵ���ʽ���� ����c��
	Address_set(x,y  ,x+16-1, y+16-1);       //ѡ������λ��

	for (k=0;k<64;k++) { //64��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����		  һ��������Ҫ�����ֽ�
	  if ((codeHZ_16[k].Index[0]==c[0])&&(codeHZ_16[k].Index[1]==c[1]))	    //Ѱ�Ҷ�Ӧ����
	  
	  { 
    	for(i=0;i<32;i++) {										  //32���ֽ� ÿ���ֽڶ�Ҫһ����һ���㴦�� �����Ǵ�����32X8��
		  unsigned short m=codeHZ_16[k].Msk[i];
		  for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {							//�ж��Ƿ���Ҫд��� 	 ����� ��������ɫ
				Lcd_Write_Data(dcolor>>8,dcolor);
				}
			else {											 //������� Ϊ��ɫ��  ����ɫ
				Lcd_Write_Data(bgcolor>>8,bgcolor);
				}
			m<<=1;												 //����һλ  �ж���һ��
			} 
		  }
		}  
	  }	
	}





/*********************************************
��ʾӢ���ַ�����16X16����
��ڲ�����(x��y) ����ʾ���ݵ����Ͻ����꣬*s��Ӣ���ַ���ָ�룬
          color:��ɫ,b_color:������ɫ��
���ڲ���: ��
˵������ָ��λ������ʾӢ���ַ�����
**********************************************/
void GUI_sprintf_hzstr16s(unsigned int x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor)	  
{  
	 unsigned char l=0;
	while(*str)
	{	
	  if(*str<0x80)		  //С��128   ascii ����������
	  {
		GUI_sprintf_char(x1,y1,*str,dcolor,bgcolor);
		x1+=8;
		str++;
		}
	  else
	  {
	   GUI_sprintf_hz1616(x1+l*8,y1,(unsigned char*)str,dcolor, bgcolor);
			str+=2;l+=2;
	  }
	}	
}	



/*********************************************
��ʾ32x32��������
��ڲ�����(x��y) ����ʾ���ݵ����Ͻ����꣬*s��Ӣ���ַ���ָ�룬
          color:��ɫ,b_color:������ɫ��
���ڲ���: ��
˵������ָ��λ������ʾӢ���ַ�����
**********************************************/

void GUI_sprintf_hz3232(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor)
{
	unsigned int i,j,k;

	Address_set(x,y,x+32-1, y+32-1);     //ѡ������λ��

	for (k=0;k<40;k++) { //15��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
	  if ((codeHZ_32[k].Index[0]==c[0])&&(codeHZ_32[k].Index[1]==c[1])){ 
    	for(i=0;i<128;i++) {
		  unsigned short m=codeHZ_32[k].Msk[i];
		  for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {
				Lcd_Write_Data(dcolor>>8,dcolor);
				}
			else {
			    Lcd_Write_Data(bgcolor>>8,bgcolor);
				}
			m<<=1;
			}    
		  }
		}  
	  }	
	}

/*********************************************
��ʾ32x32���ִ�
��ڲ�����(x��y) ����ʾ���ݵ����Ͻ����꣬*s��Ӣ���ַ���ָ�룬
          color:��ɫ,b_color:������ɫ��
���ڲ���: ��
˵������ָ��λ������ʾӢ���ַ�����
**********************************************/
void GUI_sprintf_hz3232s(unsigned int x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor)	 
     {  unsigned char l=0;
        while(*str)
           {
     	   GUI_sprintf_hz3232(x1+l*16,y1,(unsigned char*)str,dcolor, bgcolor);
			str+=2;l+=2;
      }
    }



/*********************************************
��ʾ16x32��ĸ
��ڲ�����(x��y) ����ʾ���ݵ����Ͻ����꣬*s��Ӣ���ַ���ָ�룬
          color:��ɫ,b_color:������ɫ��
���ڲ���: ��
˵������ָ��λ������ʾӢ���ַ�����
**********************************************/
void GUI_sprintf_ZM3216(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor){
	unsigned int i,j,k;

	Address_set(x,y,x+16-1, y+32-1);     //ѡ������λ��

	for (k=0;k<19;k++) { //15��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
	  if (codeZM_32[k].Index[0]==c[0]){ 
    	for(i=0;i<64;i++) {
		  unsigned short m=codeZM_32[k].Msk[i];
		  for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {
				Lcd_Write_Data(dcolor>>8,dcolor);
				}
			else {
			    Lcd_Write_Data(bgcolor>>8,bgcolor);
				}
			m<<=1;
			}    
		  }
		}  
	  }	
	}

/*********************************************
��ʾ16x32��ĸ��
��ڲ�����(x��y) ����ʾ���ݵ����Ͻ����꣬*s��Ӣ���ַ���ָ�룬
          color:��ɫ,b_color:������ɫ��
���ڲ���: ��
˵������ָ��λ������ʾӢ���ַ�����
**********************************************/
void GUI_sprintf_ZM3216s(unsigned int x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor)	 
     {  unsigned char l=0;
        while(*str)
           {
     	   GUI_sprintf_ZM3216(x1+l*8,y1,(unsigned char*)str,dcolor, bgcolor);
			str+=1;l+=2;
      }
    }






/*********************************************
��ʵ�ľ���
��ڲ����� (sx,sy)���ϽǶ�������, (ex,ey)���½Ƕ�������, color��ɫ
���ڲ���: ��
˵������ָ��λ���ϻ���ʵ�ľ��Ρ�
**********************************************/
void GUI_box(uchar sx,uint sy,uchar ex,uint ey,uint color)
{ 
	uint temp;   
	Address_set(sx,sy,ex,ey); 
   sx=ex-sx+1;
	sy=ey-sy+1;

	while(sx--)
	{
	 	temp=sy;
		while(temp--)
	 	{	
			Lcd_Write_Data16(color);
		}
	}
}


/*********************************************
�����ľ���
��ڲ����� (sx,sy)���ϽǶ�������, (ex,ey)���½Ƕ�������, color��ɫ
���ڲ���: ��
˵������ָ��λ���ϻ������ľ��Ρ�
**********************************************/
void GUI_rectangle( uchar sx,uint sy,uchar ex,uint ey,uint color)
{
	GUI_line(sx,sy,ex,sy,color);
	GUI_line(sx,sy,sx,ey,color);
	GUI_line(ex,sy,ex,ey,color);
	GUI_line(sx,ey,ex,ey,color);
}

/*********************************************
��ʮ������ʽ��ʾ������
��ڲ����� 
   x��y ----����ʾ���ݵ����Ͻ����� 
    num ----����ʾ�ĳ�����
   bits ----������ʾ��λ��
     dp ----С����λ��
  color ----��ɫ
b_color ----������ɫ
���ڲ���: ��
˵���� 
��һ������������ֵ��ʮ������ʽ��ʾ��TFT���ϣ����Ը�����Ҫȷ��
�Ƿ���ʾС�����Լ�С����λ�ã�Ҳ����ȷ����TFT��Ļ����ʾ��λ����
ע�⣺
1��Ҫ��ʾ�����ݱȹ涨����ʾλ���࣬�涨��λȫ��д������ʾ���������
2��������ʵ�����൱��GUI_wrul��������ǿ�棬�������ָ��bits=10 dp=0��
������ʾ��
GUI_wrlval(20��239��tp��10��0,WHITE,BLACK);
��ô�������ú�GUI_wrul������ȫһ����
**********************************************/
void GUI_wrlval(uchar x, uint y,unsigned long num,uchar bits,uchar dp,uint color,uint b_color)
{
	char str[10];/*�޷��ų�������ת��Ϊ�ַ�����10����������Ҫ10����Ԫ�洢*/	
	unsigned long temp; 
	uchar i;
	//LCD_wrcmd(CUR_AUTO_L);/*���ù�������ֲ�����Զ�����*/
	for(i=0;i<bits;i++)
	{
		if(num!=0)
		{
			temp=num/10;
			str[i]=num-temp*10+'0';
			num=temp;
		}
		else/*��ǰд*/
		{
			if(i>=dp)str[i]=0x20;/*С����ǰ�㶼��ո�*/
			else str[i]='0';/*С������㱣��*/
		}
	}
	i=0;
	if (num!=0)/*Ҫ��ʾ�����ݱȹ涨����ʾλ���࣬������ʾ���*/
	{
		while(i<bits)/*��ǰд���涨��λ����Ҳ����ǰ�涼д�ո�ֱ���涨��λ��*/
		{
			GUI_sprintf_char(x-7,y,'-',color,b_color);/*�涨��λȫ��д-����ʾ�������*/
			i++;
			x=x-8;
			if (i==dp) 
			{
				GUI_sprintf_char(x-7,y,'.',color,b_color);/*����С����*/
				x=x-8;
			}
		}
	}
	else
	{
		while(i<bits)/*��ʾǰ�����Ч����*/
		{
			if ((i==dp)&(str[dp]==0x20))
			{
				GUI_sprintf_char(x-7,y,'.',color,b_color);/*����С����*/
				x=x-8;
				GUI_sprintf_char(x-7,y,'0',color,b_color);/*С����ǰΪ0ʱҪ��д0*/
				x=x-8;
			}
			else
			{
				if ((i==dp)&(i!=0)) 
				{
					GUI_sprintf_char(x-7,y,'.',color,b_color);/*����С����*/
					x=x-8;
				}
				GUI_sprintf_char(x-7,y,str[i],color,b_color);
				x=x-8;
			}
			i++;				
		}
	}
}

/**********************************************************
�޷����ַ�������ʮ������ʽ��ʾ
��ڲ�����(x��y)����ʾ���ݵ����Ͻ����꣬dat������ʾ���޷����ַ�������
          color ����ʾ�ַ�����ɫ��b_color�Ǳ�����ɫ��
���ڲ���: ��
˵�����޷����ַ�������ָ������ɫ�ͱ�����ɫ��ָ��������λ����
      ��ʮ������ʽ��ʾ������
************************************************************/
void GUI_sprintf_chartodec(uchar x,uint y,uchar dat,uint color,uint b_color)
{
	GUI_sprintf_char(x,y,dat/100+'0',color,b_color);
	GUI_sprintf_char(x+8,y,dat/10%10+'0',color,b_color);
	GUI_sprintf_char(x+16,y,dat%10+'0',color,b_color);
}

/*********************************************
��ʾ1λ16������
��ڲ����� (x��y) ����ʾ���ݵ����Ͻ����꣬c������ʾ��1λ16��������color:��ɫ,b_color:������ɫ��
���ڲ���: ��
˵������ָ��λ������ʾ1λ16��������
**********************************************/
void GUI_sprintf_nu(uchar x, uint y,uchar nu, uint color,uint b_color)
{  
  	uchar  s_x=0 ,s_y=0, temp=0 ;
  	uint j;
   if (nu>9)
  	{nu=nu+7;} 
   nu=nu+16;
   for(s_y=0;s_y<16;s_y++)
   {
	 	if(s_y+y<320)
	   {
			j=nu;
		   j=j*16+s_y;
		   temp=zifu816[j];
	      //temp = font16x8[nu*16+s_y] ;
	  	   for( s_x=0 ; s_x<8 ; s_x++ )
	      {
		     	if(x+s_x<240)
		      {
			     	if((temp&(0x80>>(s_x))) == (0x80>>(s_x))  )
			      {
				   	GUI_Point(x+s_x, y+s_y,color) ;
			      }
			     	else
			      {
				     	GUI_Point(x+s_x, y+s_y,b_color) ;
				   }
			   }
		   }
	   }
	}
}

/**********************************************************
�޷����ַ�������ʮ��������ʽ��ʾ
��ڲ�����(x��y)����ʾ���ݵ����Ͻ����꣬dat ������ʾ���޷����ַ�������
          color ����ʾ�ַ�����ɫ��b_color�Ǳ�����ɫ��
���ڲ���: ��
˵�����޷����ַ�������ָ������ɫ�ͱ�����ɫ��ָ��������λ����
      ��ʮ��������ʽ��ʾ������
************************************************************/
void GUI_sprintf_chartohex(uchar x, uint y,uchar dat, uint color,uint b_color)
{  
//	unsigned char i ;
	GUI_sprintf_nu(x,y,dat>>4,color,b_color) ;
	x+=8 ;
	GUI_sprintf_nu(x,y,dat&0x0f,color,b_color) ;
}




















