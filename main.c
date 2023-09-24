#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "uart.h"

#define keypadDirectionRegisterR DDRB
#define keypadPortControlR PORTB
#define keypadPortValueR PINB

#define keypadDirectionRegisterC DDRC
#define keypadPortControlC PORTC
#define keypadPortValueC PINC

#define ctrl PORTD // We are using port D
#define en 2       // enable signal pin 2
#define rw 1       // read/write signal pin 1
#define rs 0       // register select signal pin 0

// WOKWI https://wokwi.com/projects/375118289884211201

char keypadScan(void);

int main() {
	init_serial();

  DDRD = 0xFF; // Setting DDRD to output // setting for port D
  _delay_ms(30);

  printf("Press a key\n"); // Print the text

  // Keypad initialization
  keypadDirectionRegisterR = (1<<0) | (1<<1) | (1<<2) | (1<<3);
  keypadDirectionRegisterC = (0<<0) | (0<<1) | (0<<2) | (0<<3);

  keypadPortControlR = (0<<0) | (0<<1) | (0<<2) | (0<<3);
  keypadPortControlC = (1<<0) | (1<<1) | (1<<2) | (1<<3);
  
  char ch = ' ';
  while (1) {
    char now = keypadScan();
	if(ch != now && now != ' '){
		printf("%c\n",now);
		ch = now;
	}
  };

  return 0;
}

char keypadScan(){
  
  // Store value for column
  uint8_t keyPressCodeC = keypadPortValueC;
  
      keypadDirectionRegisterC ^= (1<<0) | (1<<1) | (1<<2) | (1<<3);
      keypadDirectionRegisterR ^= (1<<0) | (1<<1) | (1<<2) | (1<<3); 
  
      keypadPortControlC ^= (1<<0) | (1<<1) | (1<<2) | (1<<3);
      keypadPortControlR ^= (1<<0) | (1<<1) | (1<<2) | (1<<3);
      
      _delay_ms(5);
  
      // Store value for row
      int temp = keypadPortValueR;
      uint8_t keyPressCodeR = temp << 4;
  
      // Add value for column and row
      uint8_t keyPressCode = keyPressCodeC | keyPressCodeR;
  
      uint8_t blinkDuration = 0;
  
      // Comparison and resultant action
  
      // Column one
      if(keyPressCode == 0b11101110){
        return '1';
      }
      if(keyPressCode == 0b11011110){
        return '4';      
	}
      if(keyPressCode == 0b10111110){
        return '7';
      }
      if(keyPressCode == 0b01111110){
        return '*';
      }
  
      // Column two
      if(keyPressCode == 0b11101101){
        return '2';
      }
      if(keyPressCode == 0b11011101){
        return '5';
      }
      if(keyPressCode == 0b10111101){
        return '8';
      }
      if(keyPressCode == 0b01111101){
        return '0';
      }
  
      // Column three
      if(keyPressCode == 0b11101011){
        return '3';
      }
      if(keyPressCode == 0b11011011){
        return '6';
      }
      if(keyPressCode == 0b10111011){
        return '9';
      }
      if(keyPressCode == 0b01111011){
        return '#';
      }
  
      // Column four
      if(keyPressCode == 0b11100111){
        return 'A';
      }
      if(keyPressCode == 0b11010111){
        return 'B';
      }
      if(keyPressCode == 0b10110111){
        return 'C';
      }
      if(keyPressCode == 0b01110111){
        return 'D';
      }
	  return ' ';
  
}

// Function moving to a given position on the LCD screen
