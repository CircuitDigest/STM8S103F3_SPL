
 /*LCD Header file to interface 16x2 LCD with STM8S103F
 * Website: https://circuitdigest.com
 * Code by: Aswinth Raj
 */

/* //MUST BE DEFINED IN CODE
 #define LCD_RS     GPIOA, GPIO_PIN_1
 #define LCD_EN      GPIOA, GPIO_PIN_2
 #define LCD_DB4    GPIOD, GPIO_PIN_1
 #define LCD_DB5    GPIOD, GPIO_PIN_2
 #define LCD_DB6    GPIOD, GPIO_PIN_3
 #define LCD_DB7    GPIOD, GPIO_PIN_4
 */

 void delay_ms(int ms);
 void Lcd_SetBit(char data_bit);
 void Lcd_Cmd(char a);
 void Lcd_Begin(void);
 void Lcd_Print_Char(char data);
 void Lcd_Clear(void);
 void Lcd_Set_Cursor(char a, char b);
 void Lcd_Print_String(char *a);


 
void delay_ms (int ms) //Function Definition 
{
int i =0 ;
int j=0;
for (i=0; i<=ms; i++)
{
for (j=0; j<120; j++) // Nop = Fosc/4
_asm("nop"); //Perform no operation //assembly code <span style="white-space:pre"> </span>
}
}

 void Lcd_SetBit(char data_bit) //Based on the Hex value Set the Bits of the Data Lines
{
    if(data_bit& 1) 
        GPIO_WriteHigh(LCD_DB4); //D4 = 1
    else
        GPIO_WriteLow(LCD_DB4); //D4=0

    if(data_bit& 2)
        GPIO_WriteHigh(LCD_DB5); //D5 = 1
    else
        GPIO_WriteLow(LCD_DB5); //D5=0

    if(data_bit& 4)
        GPIO_WriteHigh(LCD_DB6); //D6 = 1
    else
        GPIO_WriteLow(LCD_DB6); //D6=0

    if(data_bit& 8) 
        GPIO_WriteHigh(LCD_DB7); //D7 = 1
    else
        GPIO_WriteLow(LCD_DB7); //D7=0
}

void Lcd_Cmd(char a)
{
    GPIO_WriteLow(LCD_RS); //RS = 0          
    Lcd_SetBit(a); //Incoming Hex value
    GPIO_WriteHigh(LCD_EN); //EN  = 1         
		delay_ms(2);
		GPIO_WriteLow(LCD_EN); //EN  = 0      
}


 
 void Lcd_Begin(void)
 {
	 //Initialize all GPIO pins as Output 
	 GPIO_Init(LCD_RS, GPIO_MODE_OUT_PP_HIGH_FAST);
	 GPIO_Init(LCD_EN, GPIO_MODE_OUT_PP_HIGH_FAST);
	 GPIO_Init(LCD_DB4, GPIO_MODE_OUT_PP_HIGH_FAST);
	 GPIO_Init(LCD_DB5, GPIO_MODE_OUT_PP_HIGH_FAST);
	 GPIO_Init(LCD_DB6, GPIO_MODE_OUT_PP_HIGH_FAST);
	 GPIO_Init(LCD_DB7, GPIO_MODE_OUT_PP_HIGH_FAST);
	 delay_ms(10);
	 
	Lcd_SetBit(0x00);
	delay_ms(1000);  //for(int i=1065244; i<=0; i--)  

	
  Lcd_Cmd(0x03);
	delay_ms(5);
	
  Lcd_Cmd(0x03);
	delay_ms(11);
	
  Lcd_Cmd(0x03); 
  Lcd_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  Lcd_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  Lcd_Cmd(0x08); //Select Row 1
  Lcd_Cmd(0x00); //Clear Row 1 Display
  Lcd_Cmd(0x0C); //Select Row 2
  Lcd_Cmd(0x00); //Clear Row 2 Display
  Lcd_Cmd(0x06);
 }
 

void Lcd_Clear(void)
{
    Lcd_Cmd(0); //Clear the LCD
    Lcd_Cmd(1); //Move the curser to first position
}


void Lcd_Set_Cursor(char a, char b)
{
    char temp,z,y;
    if(a== 1)
    {
      temp = 0x80 + b - 1; //80H is used to move the curser
        z = temp>>4; //Lower 8-bits
        y = temp & 0x0F; //Upper 8-bits
        Lcd_Cmd(z); //Set Row
        Lcd_Cmd(y); //Set Column
    }
    else if(a== 2)
    {
        temp = 0xC0 + b - 1;
        z = temp>>4; //Lower 8-bits
        y = temp & 0x0F; //Upper 8-bits
        Lcd_Cmd(z); //Set Row
        Lcd_Cmd(y); //Set Column
    }
}



 void Lcd_Print_Char(char data)  //Send 8-bits through 4-bit mode
{
   char Lower_Nibble,Upper_Nibble;
   Lower_Nibble = data&0x0F;
   Upper_Nibble = data&0xF0;
   GPIO_WriteHigh(LCD_RS);             // => RS = 1
	 
   Lcd_SetBit(Upper_Nibble>>4);             //Send upper half by shifting by 4
   GPIO_WriteHigh(LCD_EN); //EN = 1
   delay_ms(5); //for(int i=2130483; i<=0; i--)  NOP(); 
   GPIO_WriteLow(LCD_EN); //EN = 0
	 
   Lcd_SetBit(Lower_Nibble); //Send Lower half
   GPIO_WriteHigh(LCD_EN); //EN = 1
   delay_ms(5); //for(int i=2130483; i<=0; i--)  NOP();
   GPIO_WriteLow(LCD_EN); //EN = 0
}



void Lcd_Print_String(char *a)
{
    int i;
    for(i=0;a[i]!='\0';i++)
       Lcd_Print_Char(a[i]);  //Split the string using pointers and call the Char function 
}
