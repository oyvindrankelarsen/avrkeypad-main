#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "uart.h"
#include "keypad.h"
// https://wokwi.com/projects/376753312998681601 min
// WOKWI https://wokwi.com/projects/375118289884211201

int main()
{
  init_serial();
  keypadInit();
  printf("Press a key\n");
  char ch = 'X';
  uint8_t count = 0, sum = 0;
  while (count < 4)
  {
    char now = keypadScan();
    // printf("%d\n", now);
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