#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "wifi.h"
#include "string.h"

 
/************************************************
 ALIENTEK ս��STM32F103������ʵ��13
 TFTLCD��ʾʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
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
		u8 lcd_id[12];			//���LCD ID�ַ���
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
		
		LED_Init();			     //LED�˿ڳ�ʼ��
		LCD_Init();
		POINT_COLOR=RED;
		sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣	
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
 		LCD_ShowString(30,110,200,16,16," ");		//��ʾLCD ID
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
