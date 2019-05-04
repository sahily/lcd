/*
 * lcd.c
 *
 * Created: 5/2/2019 7:40:37 PM
 * Author : Sahil S. Mahajan
 * Description: Writes values to LCD
 *
 */

#include <REG51F.H>
#include <string.h>

sbit BK = P1^0;         //backlight
sbit RS = P1^1;         //control line
sbit RW = P1^2;         //control line
sbit EN = P1^3;         //enable

void initializeLCD(void);
void writeStringToLCD(void);
void configureRSRW(bit x,bit y);
void commandWrite(unsigned char value);
void dataWrite(unsigned char value);
void enable(void);
void delay(unsigned int k);

unsigned int length;                                            //length of string to be written to LCD
unsigned char string[] = "This is how to write to an LCD:)";    //string to be written to LCD


void main()
{
    initializeLCD();
    writeStringToLCD();
    while(1);
}


/* -----------------
 * Function: initializeLCD
 * -----------------
 *
 * send commands to LCD to initialize it, according to its factory settings
 *
 */

void initializeLCD(void)
{
    delay(15);
    commandWrite(0x03);
    delay(5);
    commandWrite(0x03);
    delay(5);
    commandWrite(0x03);
    delay(5);
    commandWrite(0x02);
    delay(5);
    commandWrite(0x28);
    delay(5);
    commandWrite(0x01);
    delay(5);
}


/* -----------------
 * Function: writeStringToLCD
 * -----------------
 *
 * writes a string to the LCD
 *
 */

void writeStringToLCD(void)
{
    unsigned int i;
    length = strlen(string);
    for(i=0;i<length;i++)
    {
        if(i==16)
        {
            commandWrite(0xC0);     //go to second line position 0 of LCD if the spaces in the first line are used up
        }
        dataWrite(string[i]);
        delay(50);
    }
}

/* -----------------
 * Function: configureRSRW
 * -----------------
 *
 * configures control signals of LCD to do a command write, a status read, a data write, or a data read
 *
 * Command write: RS = 0, R/W = 0
 * Status read:   RS = 0, R/W = 1
 * Data write:    RS = 1, R/W = 0
 * Data read:     RS = 1, R/W = 1
 *
 * x: value of RS command line
 * y: value of R/W command line
 *
 */

void configureRSRW(bit x,bit y)
{
    RS = x;
    RW = y;
}


/* -----------------
 * Function: commandWrite
 * -----------------
 *
 * writes command to LCD via 4 bit interfacing
 *
 * value: data to be sent to LCD
 *
 */

void commandWrite(unsigned char value)
{
    configureRSRW(0,0);                //set to command write mode
    P1 = (value & 0xF0) | (P1 & 0x0F);
    enable();
    value = value << 4;
    P1 = (value & 0xF0) | (P1 & 0x0F);
    enable();
}


/* -----------------
 * Function: dataWrite
 * -----------------
 *
 * writes data to LCD via 4 bit interfacing
 *
 * value: data to be sent to LCD
 *
 */

void dataWrite(unsigned char value)
{
    configureRSRW(1,0);                //set to data write mode
    P1 = (value & 0xF0) | (P1 & 0x0F);
    enable();
    value = value << 4;
    P1 = (value & 0xF0) | (P1 & 0x0F);
    enable();
}


/* -----------------
 * Function: enable
 * -----------------
 *
 * sets LCD's enable bit, then resets. Used to send data to LCD
 *
 */

void enable(void)
{
    EN = 1;
    delay(1);
    EN = 0;
}


/* -----------------
 * Function: delay
 * -----------------
 *
 * creates delay for a specificed number of milliseconds
 *
 * k: number of milliseconds (approximate)
 *
 */

void delay(unsigned int k)
{
   unsigned int i,j;
    
   for(i=0; i<k;i++)
   {
      for(j=0;j<120;j++); 
   }

}