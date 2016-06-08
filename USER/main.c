//***********************************************************

#include "sys.h"
#include "plusc2c.h"
	
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"	
#include "led.h"  

//***********************************************************
#define GSM_RST PCout(11)
#define STR(A) 	(unsigned char*)(A)



int main ( void )
{
	//uint8_t static active= 0;
	//uint8_t static ledstat;
	SystemInit();//系统时钟等初始化

	if(SysTick_Config(72000*1))	 //配置错误返回1,max 16777216   默认72Mhz 时钟 ,1ms延时
	{							
		//LED4_ON; 	//错误处理 		
		while(1);
	}
	
	LED_Init();	 //LED端口初始化
	LED2_ON;
	NVIC_Configuration();//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	
	
	Uart1Init ( 115200 ); //串口初始化为115200

	GSM_RST = 0; //启动GSM模块
	
	delay_ms(1800);
	USB_Port_Set(0); 	//USB???
	delay_ms(700);
	USB_Port_Set(1);	//USB????
 	Set_USBClock();   
 	USB_Interrupts_Config();    
 	USB_Init();	
	
	
	Uart2Init ( 115200 ); //串口初始化为115200
	Uart3Init ( 115200 );//串口初始化为115200

	//Uart1SendStr(STR("uart1 init\r\n"));

	//Uart2SendStr(STR("uart2 init\r\n"));

	//Uart3SendStr(STR("uart3 init\r\n"));
	
	C_bt_init();
	C_bt_module_reset();
	C_bt_module_init();

	GSM_RST = 1; //启动GSM模块
	while(1)
	{
		
		if(C_bt_device_active())
		{
			LED2_ON;
			if(USB_USART_RX_STA&0x8000){
				//delay_ms(100);
				C_bt_sendBinary((char*)USB_USART_RX_BUF,USB_USART_RX_STA&0x3FFF);
				USB_USART_RX_STA=0;	
			}		
		}
		else
		{
			LED2_OFF;
		}
		
		if((ms_timer %2) == 0){
			C_bt_step();
		}
		
		//模块初始化
		if(C_bt_selftest()){
			LED2_OFF;
		}else{
			//LED2_ON;			
		}
	}
}
