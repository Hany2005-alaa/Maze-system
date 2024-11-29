#define F_CPU 1000000UL


#include <util/delay.h>
#include <avr/io.h>
void command(unsigned char cmd){//these functions are related to lcd intialization
	PORTC=0x02;
	PORTD=cmd;
	PORTC=0x00;
_delay_ms(15);	}
void lcd_data(unsigned char data){
	PORTC=0x03;
	PORTD=data;
	PORTC=0x01;
_delay_ms(15);	}

void lcd_print(char *p){
	while(*p){
	lcd_data(*p++);}}
	
	
	
	void lockdoors(){   //function to close all doors in case presence of more than player
		PORTB&=~(1<<6)&~(1<<7);//these pins connected to servo motors /leds and it will turned off in case of presence more than one player
		PORTA&=~(1<<4)&~(1<<5)&~(1<<6)&~(1<<7);
		
	}
	
	

	int main(void)
	{
		DDRC=0xFF; //This register is used to select the RS and RW pins
		DDRD=0xFF;//this register for lcd data 
		DDRB=0b11000000;//PB6 and PB7 output for leds...remaining bits for switches by which indicate presence of player or not 
		PORTB=0b00000000;
		DDRA=0b11110000;//first 4 bits for remaining leds ...second 4 bits for switches by whic i enter the answers of questions
		PORTA=0b00000000;
		uint8_t attempts=0;
		uint8_t door=1;
		command(0x38); //activiation 2 lines in 8 bit mode
		command(0x0F); //Display is on cursor is blinking
		command(0x01);//clearing display
		
		while(1){
			
	while(door==1){//all things related to door1....start of maze
				    if(PINB & (1<<0)){//if the related switch is press indicating to presence of object then display the related question
					command(0x80);//force cursor to first line first position
					lcd_print("Q1) 2 + 2 =");
					_delay_ms(1000);
					command(0xC0);//force cursor to second line first position
					lcd_print("1)2 2)3 3)4 4)5");
					while(door==1){
					if(PINA & (1<<2)){//if i enter the correct answer 
					command(0x01);
					command(0x80);
					lcd_print("correct answer");
					command(0xC0);
					lcd_print("opendoors 1");//displaying the open doors
					door++;//increment doors to move to the second door
					PORTB|=(1<<6);//related led to door1 is turned on (servo motor)
					_delay_ms(2000);
					command(0x01);}
					else if (PINA & (1<<0)||PINA & (1<<3) ||PINA & (1<<1)) {//in case entering wrong answers
					attempts++;
					if(attempts >=3){//in case the attempts exceed the 3 then end the maze and leds turn off and back to the start of maze as in code
					lockdoors();
					command(0x01);
					command(0x80);
					lcd_print("Failed go to ");
					command(0xC0);
					lcd_print("start of maze");
					_delay_ms(1000);
					command(0x01);
					attempts=0;
					break;}
					else{
						break;
							}	}}	}	}
							

while(door==2){//all things related to door2
			   	if(PINB & (1<<1)){//if the related switch is press indicating to presence of object then display the related question
				command(0x80);//force cursor to first line first position
				lcd_print("Q2) 2 * 3 =");
				_delay_ms(1000);
				command(0xC0);//force cursor to second line first position
				lcd_print("1)6 2)3 3)4 4)5");
				while(door==2){
				if(PINA & (1<<0)){//if i enter the correct answer 
				command(0x01);
				command(0x80);
				lcd_print("correct answer");
				command(0xC0);
				lcd_print("opendoors 2");//displaying the open doors
				attempts=0;
			    PORTB|=(1<<7);//related led to door2 is turned on (servo motor)
				_delay_ms(2000);
				command(0x01);
				
				door++; //increment doors to move to the second door
				}
				else if (PINA & (1<<2)||PINA & (1<<3)||PINA& (1<<1)) {//in case entering wrong answers
				attempts++;
				if(attempts >=3){//in case the attempts exceed the 3 then end the maze and leds turn off and back to the start of maze as in code
				lockdoors();
				command(0x01);
			    command(0x80);
												
		     	lcd_print("Failed go to ");
				command(0xC0);
			    lcd_print("start of maze");
				_delay_ms(1000);
				command(0x01);
				attempts=0;
				door=1;
				break;}
				else{
				break;
			     	}	}}	}	}
									
						  
while(door==3){//all things related to door3
      	if(PINB & (1<<2)){//if the related switch is press indicating to presence of object then display the related question
		command(0x80);//force cursor to first line first position
		lcd_print("Q3) 4 - 1 =");
		_delay_ms(1000);
		command(0xC0);//force cursor to second line first position
		lcd_print("1)6 2)4 3)2 4)3");
		while(door==3){
			if(PINA & (1<<3)){//if i enter the correct answer 
				command(0x01);
				command(0x80);
				lcd_print("correct answer");
				command(0xC0);
				lcd_print("opendoors 3");//displaying the open doors
				
				attempts=0;
				PORTA|=(1<<4);//related led to door3 is turned on (servo motor)
				_delay_ms(2000);
				
				command(0x01);
				
				door++;//increment doors to move to the second door
				
				
				
			}
			else if (PINA & (1<<1) ||PINA & (1<<2)||PINA & (1<<0)) {//in case entering wrong answers
				attempts++;
				if(attempts >=3){//in case the attempts exceed the 3 then end the maze and leds turn off and back to the start of maze as in code
					lockdoors();
					command(0x01);
					command(0x80);
					
					lcd_print("Failed go to ");
					command(0xC0);
					lcd_print("start of maze");
					_delay_ms(1000);
					command(0x01);
					door=1;
					attempts=0;
				break;}
				else{
					break;
				}	}}	}	}
														
															
															
while(door==4){//all things related to door4
																
				if(PINB & (1<<3)){//if the related switch is press indicating to presence of object then display the related question
					command(0x80);//force cursor to first line first position
					lcd_print("Q4) 9 / 3 =");
					_delay_ms(1000);
					command(0xC0);//force cursor to second line first position
					lcd_print("1)3 2)4 3)2 4)5");
					while(door==4){//if i enter the correct answer 
						if(PINA & (1<<0)){
							command(0x01);
							command(0x80);
							lcd_print("correct answer");
							command(0xC0);
							lcd_print("opendoors 4");//displaying the open doors
							
							attempts=0;
							PORTA|=(1<<5);//related led to door4 is turned on (servo motor)
							_delay_ms(2000);
							
							command(0x01);
							
							door++;//increment doors to move to the second door
							
							
							
						}
						else if (PINA & (1<<2)||PINA & (1<<3)||PINA& (1<<1)) {//in case entering wrong answers
							attempts++;
							if(attempts >=3){//in case the attempts exceed the 3 then end the maze and leds turn off and back to the start of maze as in code
								lockdoors();
								command(0x01);
								command(0x80);
								
								lcd_print("Failed go to ");
								command(0xC0);
								lcd_print("start of maze");
								_delay_ms(1000);
								command(0x01);
								attempts=0;
								door=1;
							break;}
							else{
								break;
							}	}}	}	}
							
																	
while(door==5){//all things related to door5
					if(PINB & (1<<4)){//if the related switch is press indicating to presence of object then display the related question
					command(0x80);//force cursor to first line first position
					lcd_print("Q5) 10 % 5 =");
					_delay_ms(1000);
					command(0xC0);//force cursor to second line first position
					lcd_print("1)3 2)4 3)0 4)3");
					while(door==5){
						if(PINA & (1<<2)){//if i enter the correct answer 
							command(0x01);
							command(0x80);
							lcd_print("correct answer");
							command(0xC0);
							lcd_print("opendoors 5");//displaying the open doors
							
							attempts=0;
							PORTA|=(1<<6);//related led to door5 is turned on (servo motor)
							_delay_ms(2000);
							
							command(0x01);
							
							door++;//increment doors to move to the second door
							
							
							
						}
						else if (PINA & (1<<0)||PINA & (1<<3)||PINA& (1<<1)) {//in case entering wrong answers
							attempts++;
							if(attempts >=3){//in case the attempts exceed the 3 then end the maze and leds turn off and back to the start of maze as in code
								lockdoors();
								command(0x01);
								command(0x80);
								
								lcd_print("Failed go to ");
								command(0xC0);
								lcd_print("start of maze");
								_delay_ms(1000);
								command(0x01);
								door=1;
								attempts=0;
							break;}
							else{
								break;
							}	}}	}	}
																								
while(door==6){//all things related to door6
				
				if(PINB & (1<<5)){//if the related switch is press indicating to presence of object then display the related question
					command(0x80);//force cursor to first line first position
					lcd_print("Q6) 1 * 7=");
					_delay_ms(1000);
					command(0xC0);//force cursor to second line first position
					lcd_print("1)3 2)7 3)0 4)3");
					while(door==6){
						if(PINA & (1<<1)){//if i enter the correct answer 
							command(0x01);
							command(0x80);
							lcd_print("correct answer");
							command(0xC0);
							lcd_print("opendoors 6");//displaying the open doors
							
							attempts=0;
							PORTA|=(1<<7);//related led to door6 is turned on (servo motor)
							_delay_ms(2000);
							
							
							
							command(0x01);
							lcd_print("congratulation!");//end of maze with success message
							command(0xC0);
							lcd_print("end of maze");
							_delay_ms(2000);
							
							
							
							
							
						}
						else if (PINA & (1<<0)||PINA & (1<<3)||PINA& (1<<2)) {//in case entering wrong answers
							attempts++;
							if(attempts >=3){//in case the attempts exceed the 3 then end the maze and leds turn off and back to the start of maze as in code
								lockdoors();
								command(0x01);
								command(0x80);
								
								lcd_print("Failed go to ");
								command(0xC0);
								lcd_print("start of maze");
								_delay_ms(1000);
								command(0x01);
								attempts=0;
								
							break;}
							else{
								break;
							}	}}	}	}
							
							
						}
						
					}
					
					
																									
																									

