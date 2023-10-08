#include "serial_USART.h"

void usart2Init(void) {
	//	ARM chips have two types of buses: APB (Advanced Peripheral Bus) and 
	//	AHB (Advanced High-Performance Bank).
	//	AHB is for memory for direct to CPU. APB is lower speed and lower power
	//
	//	According to Nucleo-64 MB1136: USART2 interface is on PA2 and PA3
	//	Port A pin 2 Port A pin 3 (zero indexed)
	
	// enable GPIOA clock; RCC (Reset Clock Control Register);
	RCC->AHB1ENR |= 1;
	
	// Clear PA2 and PA3 direction pins then set to alternate function 0b10
	GPIOA->MODER &= ~(	(0x3ul << (2*2) ) |
											(0x3 << (3*2) ) );
	GPIOA->MODER |= ( 	(0x2 << (2*2) ) |
											(0x2 << (3*2) ) );
	GPIOA->OSPEEDR &= ~(	(0x3ul << (2*2) ) |
										(0x3 << (3*2) ) );	
	GPIOA->OSPEEDR &= (	(0x3 << (2*2) ) |
										(0x3 << (3*2) ) );
	
	// Using Datasheet STM32F446xC/E Table 11
	// Set PA2 to USART2_TX (AF7) and PA3 to USART2_RX (AF7)
	GPIOA->AFR[0] &= ~( (0xFul << 2*4) | 
											(0xF << 3 * 4));
	GPIOA->AFR[0] |= (	(0x7 << 2*4) |
											(0x7 << 3*4));
	// Enable USART2 Clock
	RCC->APB1ENR |= ( RCC_APB1ENR_USART2EN );
	
	// Using Datasheet STM32F446xC/E Table 152
	// Set Baud Rate Register to 9600
	USART2->BRR = 0x683;
	//USART2->BRR = compute_uart_bd(16000000U, 9600);
	
	// Oversample by 16 rather than by 8; OVER8 = 0
	USART2->CR1 &= ~( USART_CR1_OVER8_Msk );
	// USART2 receive enable, transmit enable, USART enable
	USART2->CR1 |= ( USART_CR1_RE | USART_CR1_TE | USART_CR1_UE );
	
}


static uint16_t compute_uart_bd(uint32_t PCLK, uint32_t Baudrate)
{
	return ((PCLK + (Baudrate/2))/Baudrate);
}