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
  Time-stamp: <2011-09-12 17:31:35 (hauspie)>
*/
#include <debug.h>
#include <drivers/uart.h>
#include <drivers/timer.h>

#include <printf.h>
#include <interrupt.h>
#include <clock.h>

#include <nxp/LPC17xx.h>


#define TIMER_TO_TEST RFLPC_TIMER3

int putchar(int c)
{
    rflpc_uart0_putchar(c);
    return c;
}

RFLPC_IRQ_HANDLER _uart_cb()
{
    char c = rflpc_uart0_getchar();

    switch (c)
    {
	case 's': 
	    rflpc_timer_stop(TIMER_TO_TEST);
	    break;
	case 'S': 
	    rflpc_timer_start(TIMER_TO_TEST);
	    break;
	case 'r': 
	    rflpc_timer_reset(TIMER_TO_TEST);
	    break;
    }
}

int main()
{
    uint32_t otc0, otc1, otc2, otc3;
    const char *toto = "Enabling timers\r\n";

    if (rflpc_uart0_init() == -1)
	RFLPC_STOP(RFLPC_LED_1 | RFLPC_LED_2, 1000000);

    rflpc_uart0_set_rx_callback(_uart_cb);

    printf("Enabling timers\r\n");

    rflpc_timer_enable(TIMER_TO_TEST);


    printf("Setting timer clock\r\n");
    rflpc_timer_set_clock(TIMER_TO_TEST, RFLPC_CCLK);

    printf("Setting pre scale register 1\r\n");
    rflpc_timer_set_pre_scale_register(TIMER_TO_TEST, rflpc_clock_get_system_clock());

    printf("Starting timers\r\n");
    rflpc_timer_start(TIMER_TO_TEST);


    printf("Press:\r\n");
    printf("- 's' to stop timer\r\n");
    printf("- 'S' to start timer\r\n");
    printf("- 'r' to reset timer\r\n");

    otc0 = rflpc_timer_get_counter(TIMER_TO_TEST);

    while (1)
    {
    	if (otc0 != rflpc_timer_get_counter(TIMER_TO_TEST))
    	    printf("TC: %d\r\n", otc0 = rflpc_timer_get_counter(TIMER_TO_TEST));
	
    }

    return 0;
}