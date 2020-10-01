 /*Header file for Arduino like Serial commands on STM8S
 * Website: https://circuitdigest.com/search/node/STM8S
 * Code by: Aswinth Raj
 * Github: https://github.com/CircuitDigest/STM8S103F3_SPL
 */
 
 /*Control on-board LED through USART
 * PD5 - UART1-Tx
 * PD6 - UART1-Rx
 */
 
 #include "stm8s.h"
 #include "stdio.h"

//Funtion Declarations 
 void Serial_begin(uint32_t); //pass baug rate and start serial communiaction 
 void Serial_print_int (int); //pass integer value to print it on screen
 void Serial_print_char (char); //pass char value to print it on screen 
 void Serial_print_string (char[]); //pass string value to print it 
 void Serial_newline(void); //move to next line
 bool Serial_available(void); //check if input serial data available return 1 is yes 
 char Serial_read_char(void); //read the incoming char byte and return it 
 

 char Serial_read_char(void)
 {
	 while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
	 UART1_ClearFlag(UART1_FLAG_RXNE);
	 return (UART1_ReceiveData8());
 }

 void Serial_print_char (char value)
 {
	 UART1_SendData8(value);
	 while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET); //wait for sending
 }
 
  void Serial_begin(uint32_t baud_rate)
 {
	 GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);
	 GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_IN_PU_NO_IT);
	 
	 UART1_DeInit(); //Deinitialize UART peripherals 
			
                
		UART1_Init(baud_rate, 
                UART1_WORDLENGTH_8D, 
                UART1_STOPBITS_1, 
                UART1_PARITY_NO, 
                UART1_SYNCMODE_CLOCK_DISABLE, 
                UART1_MODE_TXRX_ENABLE); //(BaudRate, Wordlegth, StopBits, Parity, SyncMode, Mode)
                
		UART1_Cmd(ENABLE);
 }
 
 void Serial_print_int (int number) //Funtion to print int value to serial monitor 
 {
	 char count = 0;
	 char digit[5] = "";
	 
	 while (number != 0) //split the int to char array 
	 {
		 digit[count] = number%10;
		 count++;
		 number = number/10;
	 }
	 
	 while (count !=0) //print char array in correct direction 
	 {
		UART1_SendData8(digit[count-1] + 0x30);
		while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET); //wait for sending 
		count--; 
	 }
 }
 
 void Serial_newline(void)
 {
	 UART1_SendData8(0x0a);
	while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET); //wait for sending 
 }
 
 void Serial_print_string (char string[])
 {

	 char i=0;

	 while (string[i] != 0x00)
	 {
		UART1_SendData8(string[i]);
		while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
		i++;
	}
 }
 
 bool Serial_available()
 {
	 if(UART1_GetFlagStatus(UART1_FLAG_RXNE) == TRUE)
	 return TRUE;
	 else
	 return FALSE;
 }
 
 
 