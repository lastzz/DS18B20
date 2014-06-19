

#include  "stc12.h"
#include  "gui.h"
#include  "def.h"
#include  "tft.h"			
//#include  "bmp.h"			   //图片代码
#include  "hz16x16.h"		  //汉字16X16
#include  "zifu8x16.h"
#include  "zifu8x12.h"
#include  "hz32x32.h"
#include  "zm16x32.h"



/************************************
清屏
入口参数： b_color是背景颜色。
出口参数: 无
说明：使用背景颜色清除TFT模块屏幕的全部显示内容。
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
画点
入口参数： (x，y)是点的坐标，color 是点的颜色。
出口参数: 无
说明：用指定的颜色在指定的坐标位置上画出一个点。
**********************************************/
void GUI_Point(uchar x, uint y, uint color)
{  
	Address_setxy(x,y);
	Lcd_Write_Data16(color);
}





/**********************************************************
画横线
入口参数： (x，y)是横线起点坐标，length是横线长度，color 是横线颜色。
出口参数: 无
说明：用指定的颜色在指定位置上画出指定长度的一条横线。
************************************************************/
void GUI_HLine(uchar x, uint y, uchar length, uint color) 
{  
	Address_set(x,y,x+length-1,y);
	do
	{  
		Lcd_Write_Data16(color);//逐点显示，描出水平线
		length--;
	}while(length);
}


/**********************************************************
画竖线
入口参数： (x，y)是竖线起点坐标，high 竖线高度，color 是竖线颜色。
出口参数: 无
说明：用指定的颜色在指定位置上画出指定长度的一条竖线。
************************************************************/
void GUI_SLine(uchar x, uint y, uint high, uint color) 
{  
   Address_set(x,y,x,y+high-1);
   do
   {  
		Lcd_Write_Data16(color);// 逐点显示，描出垂直线
		high--;
   }while(high);	
}



/******************************************************************** 
画直线（可以画任意方向直线，包括横线、竖线、斜线）。
入口参数： (x1,y1)起点, (x2,y2)终点, color颜色。
出口参数: 无
说明：用指定的颜色在指定的两点间画出一条直线。
***********************************************************************/
void GUI_line(uint x1,uint y1,uint x2,uint y2,uint color)  
{  
    uint t;  
    int xerr=0,yerr=0,delta_x,delta_y,distance;  
    int incx,incy;  
    uint row,col;  
    delta_x = x2-x1;//计算坐标增量  
    delta_y = y2-y1;  
    col=x1;  
    row=y1;  
    if(delta_x>0) incx=1;//设置单步方向  
    else   
    {  
        if(delta_x==0) incx=0;//垂直线  
        else {incx=-1;delta_x=-delta_x;}  
    }  
    if(delta_y>0)incy=1;  
    else  
    {  
        if(delta_y==0) incy=0;//水平线  
        else {incy=-1;delta_y=-delta_y;}  
    }  
    if(delta_x>delta_y) distance=delta_x;//选取基本增量坐标轴  
    else distance=delta_y;  

    for(t=0;t<=distance+1;t++)  
	{                                     //画线输出  
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
显示图片(图标)
入口参数：(x，y)是开始点的坐标，length是图片长度，high是图片高度。//pic 图片数组的指针
出口参数: 无
说明：用指定位置上显示事先定义的图片。
要显示的图片事先定义在bmp.h中的pic[]数组中，
如果想修改图片大小、内容，请修改bmp.h中的pic[]数组，
建议用Image2Lcd软件将你要显示的图象自动转换为数组数据。 
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
	  Lcd_Write_Data16(temp);//逐点显示
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
显示英文或数字字符
入口参数：(x，y) 是显示内容的左上角坐标，c：显示的英文字符，
          color:颜色,b_color:背景颜色。
出口参数: 无
说明：用指定位置上显示单个英文字符或数字字符。
**********************************************/
void GUI_sprintf_char(unsigned int x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor)	
{  
	unsigned char i,j;
	unsigned char *temp=zifu816;    //temp是*temp的地址  这里temp就是zifu的首地址 
    Address_set(x,y,x+7,y+15); //设置区域      
	                    
	temp+=(value-32)*16;   //确定要显示的值
				   //这里用的是ascii表  前32个ascii没有存入zifu库里 所以要减32
	               //并且 每个字符用12个字节显示 所以在乘以12  就是对应的显示位的首地址
	for(j=0;j<16;j++)
	{
		for(i=0;i<8;i++)		    //先横扫
		{ 		     
		 	if((*temp&(1<<(7-i)))!=0)					//将1 左移 然后对应位进行相与 
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
显示16x16单个汉字
入口参数：(x，y) 是显示内容的左上角坐标，*s：英文字符串指针，
          color:颜色,b_color:背景颜色。
出口参数: 无
说明：在指定位置上显示英文字符串。
**********************************************/
void GUI_sprintf_hz1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor){
	unsigned int i,j,k;
																//c[2] 把要显示的字 以两个字节的形式放入 数组c中
	Address_set(x,y  ,x+16-1, y+16-1);       //选择坐标位置

	for (k=0;k<64;k++) { //64标示自建汉字库中的个数，循环查询内码		  一个汉字需要两个字节
	  if ((codeHZ_16[k].Index[0]==c[0])&&(codeHZ_16[k].Index[1]==c[1]))	    //寻找对应汉字
	  
	  { 
    	for(i=0;i<32;i++) {										  //32个字节 每个字节都要一个点一个点处理 所以是处理了32X8次
		  unsigned short m=codeHZ_16[k].Msk[i];
		  for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {							//判断是否是要写入点 	 如果是 给字体颜色
				Lcd_Write_Data(dcolor>>8,dcolor);
				}
			else {											 //如果不是 为颜色点  给颜色
				Lcd_Write_Data(bgcolor>>8,bgcolor);
				}
			m<<=1;												 //左移一位  判断下一点
			} 
		  }
		}  
	  }	
	}





/*********************************************
显示英文字符串或16X16汉字
入口参数：(x，y) 是显示内容的左上角坐标，*s：英文字符串指针，
          color:颜色,b_color:背景颜色。
出口参数: 无
说明：在指定位置上显示英文字符串。
**********************************************/
void GUI_sprintf_hzstr16s(unsigned int x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor)	  
{  
	 unsigned char l=0;
	while(*str)
	{	
	  if(*str<0x80)		  //小于128   ascii 都在数组内
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
显示32x32单个汉字
入口参数：(x，y) 是显示内容的左上角坐标，*s：英文字符串指针，
          color:颜色,b_color:背景颜色。
出口参数: 无
说明：在指定位置上显示英文字符串。
**********************************************/

void GUI_sprintf_hz3232(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor)
{
	unsigned int i,j,k;

	Address_set(x,y,x+32-1, y+32-1);     //选择坐标位置

	for (k=0;k<40;k++) { //15标示自建汉字库中的个数，循环查询内码
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
显示32x32汉字串
入口参数：(x，y) 是显示内容的左上角坐标，*s：英文字符串指针，
          color:颜色,b_color:背景颜色。
出口参数: 无
说明：在指定位置上显示英文字符串。
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
显示16x32字母
入口参数：(x，y) 是显示内容的左上角坐标，*s：英文字符串指针，
          color:颜色,b_color:背景颜色。
出口参数: 无
说明：在指定位置上显示英文字符串。
**********************************************/
void GUI_sprintf_ZM3216(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor){
	unsigned int i,j,k;

	Address_set(x,y,x+16-1, y+32-1);     //选择坐标位置

	for (k=0;k<19;k++) { //15标示自建汉字库中的个数，循环查询内码
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
显示16x32字母串
入口参数：(x，y) 是显示内容的左上角坐标，*s：英文字符串指针，
          color:颜色,b_color:背景颜色。
出口参数: 无
说明：在指定位置上显示英文字符串。
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
画实心矩形
入口参数： (sx,sy)左上角顶点坐标, (ex,ey)右下角顶点坐标, color颜色
出口参数: 无
说明：在指定位置上画出实心矩形。
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
画空心矩形
入口参数： (sx,sy)左上角顶点坐标, (ex,ey)右下角顶点坐标, color颜色
出口参数: 无
说明：在指定位置上画出空心矩形。
**********************************************/
void GUI_rectangle( uchar sx,uint sy,uchar ex,uint ey,uint color)
{
	GUI_line(sx,sy,ex,sy,color);
	GUI_line(sx,sy,sx,ey,color);
	GUI_line(ex,sy,ex,ey,color);
	GUI_line(sx,ey,ex,ey,color);
}

/*********************************************
以十进制形式显示长变量
入口参数： 
   x，y ----是显示内容的右上角坐标 
    num ----欲显示的长变量
   bits ----允许显示的位数
     dp ----小数点位置
  color ----颜色
b_color ----背景颜色
出口参数: 无
说明： 
将一个长变量的数值以十进制形式显示在TFT屏上，可以根据需要确定
是否显示小数点以及小数点位置，也可以确定在TFT屏幕上显示的位数。
注意：
1、要显示的数据比规定的显示位数多，规定的位全部写－，表示数据溢出。
2、本函数实际上相当于GUI_wrul函数的增强版，如果我们指定bits=10 dp=0，
如下所示：
GUI_wrlval(20，239，tp，10，0,WHITE,BLACK);
那么，其作用和GUI_wrul函数完全一样。
**********************************************/
void GUI_wrlval(uchar x, uint y,unsigned long num,uchar bits,uchar dp,uint color,uint b_color)
{
	char str[10];/*无符号长整型数转换为字符串是10个，所以需要10个单元存储*/	
	unsigned long temp; 
	uchar i;
	//LCD_wrcmd(CUR_AUTO_L);/*设置光标在文字插入后自动左移*/
	for(i=0;i<bits;i++)
	{
		if(num!=0)
		{
			temp=num/10;
			str[i]=num-temp*10+'0';
			num=temp;
		}
		else/*往前写*/
		{
			if(i>=dp)str[i]=0x20;/*小数点前零都变空格*/
			else str[i]='0';/*小数点后零保留*/
		}
	}
	i=0;
	if (num!=0)/*要显示的数据比规定的显示位数多，数据显示溢出*/
	{
		while(i<bits)/*往前写满规定的位数，也就是前面都写空格，直到规定的位数*/
		{
			GUI_sprintf_char(x-7,y,'-',color,b_color);/*规定的位全部写-，表示数据溢出*/
			i++;
			x=x-8;
			if (i==dp) 
			{
				GUI_sprintf_char(x-7,y,'.',color,b_color);/*插入小数点*/
				x=x-8;
			}
		}
	}
	else
	{
		while(i<bits)/*显示前面的有效数字*/
		{
			if ((i==dp)&(str[dp]==0x20))
			{
				GUI_sprintf_char(x-7,y,'.',color,b_color);/*插入小数点*/
				x=x-8;
				GUI_sprintf_char(x-7,y,'0',color,b_color);/*小数点前为0时要补写0*/
				x=x-8;
			}
			else
			{
				if ((i==dp)&(i!=0)) 
				{
					GUI_sprintf_char(x-7,y,'.',color,b_color);/*插入小数点*/
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
无符号字符型数以十进制形式显示
入口参数：(x，y)是显示内容的左上角坐标，dat是欲显示的无符号字符型数，
          color 是显示字符的颜色，b_color是背景颜色。
出口参数: 无
说明：无符号字符型数用指定的颜色和背景颜色在指定的坐标位置上
      以十进制形式显示出来。
************************************************************/
void GUI_sprintf_chartodec(uchar x,uint y,uchar dat,uint color,uint b_color)
{
	GUI_sprintf_char(x,y,dat/100+'0',color,b_color);
	GUI_sprintf_char(x+8,y,dat/10%10+'0',color,b_color);
	GUI_sprintf_char(x+16,y,dat%10+'0',color,b_color);
}

/*********************************************
显示1位16进制数
入口参数： (x，y) 是显示内容的左上角坐标，c：欲显示的1位16进制数，color:颜色,b_color:背景颜色。
出口参数: 无
说明：用指定位置上显示1位16进制数。
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
无符号字符型数以十六进制形式显示
入口参数：(x，y)是显示内容的左上角坐标，dat 是欲显示的无符号字符型数，
          color 是显示字符的颜色，b_color是背景颜色。
出口参数: 无
说明：无符号字符型数用指定的颜色和背景颜色在指定的坐标位置上
      以十六进制形式显示出来。
************************************************************/
void GUI_sprintf_chartohex(uchar x, uint y,uchar dat, uint color,uint b_color)
{  
//	unsigned char i ;
	GUI_sprintf_nu(x,y,dat>>4,color,b_color) ;
	x+=8 ;
	GUI_sprintf_nu(x,y,dat&0x0f,color,b_color) ;
}





















