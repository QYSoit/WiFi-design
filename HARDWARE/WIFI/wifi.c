#include "wifi.h"
#include "usart.h"
#include "delay.h"
#include "stdio.h"
char txt[20];
void wifi_init(){
	delay_ms(1000);
	UART_SENDSTRING(USART3,"AT+CIPMUX=1");
	UART_SENDSTRING(USART3,"\r\n");
	sprintf(txt,"open linking");
	delay_ms(500);
	UART_SENDSTRING(USART3,"AT+CIPSERVER=1,8080");
	UART_SENDSTRING(USART3,"\r\n");
	sprintf(txt,"open done");
}
