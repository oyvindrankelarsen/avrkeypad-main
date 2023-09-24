#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "uart.h"
#include "keypad.h"

// WOKWI https://wokwi.com/projects/375118289884211201

int main()
{
  init_serial();
  keypadInit();

  char ch = ' ';
  uint8_t count = 0, sum = 0;
  while (count < 4)
  {
    char now = keypadScan();
    if (ch != now && now != ' ')
    {
      printf("%d\n", now);
      ch = now;
      sum += ch;
      count++;
    }
  }
  printf("Sum %d\n", sum);
  return 0;
}