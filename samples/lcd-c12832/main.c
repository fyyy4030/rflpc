/* This file is part of rflpc. Copyright 2010-2011 Michael Hauspie
 *
 * rflpc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rflpc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with rflpc.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
  Author: Michael Hauspie <michael.hauspie@univ-lille1.fr>
  Created:
  Time-stamp: <2014-05-29 21:03:48 (mickey)>
*/
#include <rflpc17xx/rflpc17xx.h>
#include "lcd-c12832.h"


uint8_t buffer[512];

#define COORD_TO_BYTE(x,y) ((((y)>>3) << 7) + (x))
#define COORD_TO_BIT(x,y) (((y) & 7))

void set_pixel(uint8_t x, uint8_t y)
{
   int byte_idx = COORD_TO_BYTE(x,y);
   buffer[byte_idx] |= (1 << COORD_TO_BIT(x,y));
}
void clr_pixel(uint8_t x, uint8_t y)
{
   int byte_idx = COORD_TO_BYTE(x,y);
   buffer[byte_idx] &= ~(1 << COORD_TO_BIT(x,y));
}

void clr_buffer(void)
{
   int i;
   memset(buffer, 0, 512);
}

int main()
{
#ifdef RFLPC_CONFIG_ENABLE_UART
    rflpc_uart_init(RFLPC_UART0);
#endif

#ifdef RFLPC_CONFIG_ENABLE_PRINTF
    printf("Hello World\r\n");
#endif
    
    printf("Start LCD Initialization\r\n");

    lcd_init(MBED_DIP6, MBED_DIP8, MBED_DIP11, RFLPC_SPI1);
    clr_buffer();
    printf("LCD Initialized\r\n");

    {
       int x,y,toggle = 0;
       for (y = 0 ; y < 32 ; ++y)
       {
          toggle = !toggle;
          for (x = 0 ; x < 128 ; ++x)
          {
             if ((x%32) == y)
                set_pixel(x,y);
             else
                clr_pixel(x,y);
             toggle = !toggle;
          }
       }
    }
    lcd_display_buffer(buffer);

    while (1)
       rflpc_idle;
    return 0;
}
