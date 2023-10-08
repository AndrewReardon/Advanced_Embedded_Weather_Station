/* use delay loop, 1 sec on 1 sec off
* default 16 MHz clock
* LD2 connects to PA5
*/

#include "stm32f446xx.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

// local libraries
#include "clkinit.h"
#include "serial_USART.h"

void delayMs(int n);

static uint8_t ch = 'a';

int main(void) {
	usart2Init();
	
	
	
//	// Blinks the Nucleo LED!
//	RCC->AHB1ENR |= 1; /* enable GPIOA clock */
//	
//	/*	RCC->CR &= ~0x00000001; set clock to 16MHz */

//	GPIOA->MODER &= ~0x00000C00; /* clear pin mode */
//	GPIOA->MODER |= 0x00000400; /* set pin to output mode */

//	while(1) {
//		GPIOA->BSRR = 0x00000020; /* turn on LED */
//		delayMs(500);
//		GPIOA->BSRR = 0x00200000; /* turn off LED */
//		delayMs(500);
//	}
	
	while(1) {
		//Make sure the transmit data register is empty
		while(!((USART2->SR) & (1 << 7)));

		//Write to transmit data register
		USART2->DR = (ch & 0xFF);
		delayMs(500);
	}
}


// 16 MHz SYSCLK
void delayMs(int n) {
	int i;
	for (; n > 0; n--)
	for (i = 0; i < 3195; i++) ;
}