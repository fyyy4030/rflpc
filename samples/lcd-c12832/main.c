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
  Time-stamp: <2014-05-29 00:50:08 (mickey)>
*/
#include <rflpc17xx/rflpc17xx.h>

extern void lcd_init(rflpc_pin_t reset_pin, rflpc_pin_t a0, rflpc_spi_t port);
    
int main()
{
#ifdef RFLPC_CONFIG_ENABLE_UART
    rflpc_uart_init(RFLPC_UART0);
#endif

#ifdef RFLPC_CONFIG_ENABLE_PRINTF
    printf("Hello World\r\n");
#endif
    
    lcd_init(MBED_DIP6, MBED_DIP8, RFLPC_SPI1);
    

    while (1)
       rflpc_idle;
    return 0;
}