#include<avr/io.h>
#include<util/delay.h>
#include "LCD.h"



void toggle(){
PORTB &= ~(1<<E);
_delay_us(1);
PORTB |= (1<<E);
_delay_us(1);
PORTB &=~(1<<E);
_delay_us(100); // commands needs > 37 us to settle
}



void lcd_print(char sign){

//set to receive data instead of instructions
PORTB |= (1<<RS);
// set sign to send 
PORTD = sign;
toggle();
_delay_us(50);
}
void writeString(char word[])
{
     uint8_t i = 0;                     
    while (word[i] != 0)
    {
        lcd_print(word[i]);
        i++;
        _delay_us(80);  
      if(i==200){
        break;
      }         
    }
    _delay_us(50);
}
void lcd_init(){
  DDRB = 0xFF;
  DDRD=0xFF;
  _delay_ms(50);   // must wait at least 40
  PORTB &=~(1<<RS); //low to accept instructions (R/W is connected Ground)

  //Function set :DB5, DB4 -> 8BIT MODE , DB3-> 2 LINES DISPLAY
  PORTD = (1<<PD5) | (1<<PD4) | (1<<PD3);
  toggle();
  //entry mode , set cursor moving direction (left justify) , shift entire display off
  PORTD=(1<<PD3) | (1<<PD2);
  toggle();
   PORTD= (1<<PD0);
   toggle();
_delay_ms(2);

}


void ClearScreen(){
PORTD= (1<<PD0);
_delay_ms(2);
PORTB &=~(1<<RS);
toggle();
lcd_init();
}



void CursorOn(){
  PORTD=(1<<PD3) |(1<<PD2) | (1<<PD1) ;
   _delay_us(50);
   toggle();
  
}

void CursorOff(){
  PORTD=(1<<PD3) |(1<<PD2);
  PORTD&=~(1<<PD1) ;
   _delay_us(50);
   toggle();
  
}
void cursorBlink(){
PORTD=(1<<PD3) | (1<<PD2) | (1<<PD1) | (1<<PD0);
_delay_us(50);
toggle();
}
void SetCursor(int x, int y){  // x = col , y = row
if(y==1){
for(int i=0; i<x; i++){
PORTD = (1<<PD4) | (1 <<PD2);
_delay_us(40);
toggle();
  }
}
else if(y==2){
int num = 40+x;
for(int i=0; i<num; i++){
PORTD = (1<<PD4) | (1 <<PD2);
_delay_us(40);
toggle();
  }
}


}

