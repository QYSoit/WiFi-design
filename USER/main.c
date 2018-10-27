#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "wifi.h"
#include "string.h"

 
/************************************************
 ALIENTEK 战舰STM32F103开发板实验13
 TFTLCD显示实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

extern char txt[];

u8 Find(char *a);
char* pch;
char* ech;
char dest[15];
char *TXT=" ";
 	
 int main(void)
 {	 
		
	  char TXT1[20];
		u8 lcd_id[12];			//存放LCD ID字符串
		delay_init();	    	 //延时函数初始化	  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
		uart_init(115200);	 	//串口初始化为115200
		
		LED_Init();			     //LED端口初始化
		LCD_Init();
		POINT_COLOR=RED;
		sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。	
		LCD_Clear(WHITE);
		POINT_COLOR=RED;	
		UART3_INIT(115200);
		wifi_init();
  	
		while(1) 
	{		 
		
		LCD_ShowString(30,10,210,24,16,txt); 
		LCD_ShowString(30,40,210,24,16,TXT); 
		LCD_ShowString(30,70,200,24,16,dest);		
		LCD_ShowString(30,90,200,24,16,pch+1);
 		LCD_ShowString(30,110,200,16,16," ");		//显示LCD ID
		LCD_ShowString(30,130,200,16,16," ");	   				   		 
		delay_ms(300);	
		if(Find("IPD"))
		{
			pch = strchr(USART3_BUF,':');
			memmove(dest, pch+1, 10);
			LCD_Clear(WHITE); 
			
		}
		if(Find("CONNECT"))
		{
				TXT="CONNECTED";
		}
		CLR_Buf3();

	} 
}
 
u8 Find(char *a)
{ 
  if(strstr(USART3_BUF,a)!=NULL)
	    return 1;
	else
			return 0;
}
