/* use delay loop, 1 sec on 1 sec off
* default 16 MHz clock
* LD2 connects to PA5
*/

#include "stm32f4xx.h"
//#include "stm32f446.h"
#include "stdio.h"
#include "string.h"

void clkInit(void);
void usart2Init(void);
static uint16_t compute_uart_bd(uint32_t, uint32_t);
void delayMs(int n);


static uint8_t ch = 'a';

int main(void) {
	
	usart2Init();
	
	
	while(1) {
		//Make sure the transmit data register is empty
		while(!((USART2->SR) & (1 << 7)));

		//Write to transmit data register
		USART2->DR = (ch & 0xFF);
		delayMs(500);
	}
	
	
	
	
	
	
	
	
	
	
	
	
//	
////	ARM chips have two types of buses: APB (Advanced Peripheral Bus) and 
////	AHB (Advanced High-Performance Bank).
////	AHB is for memory for direct to CPU. APB is lower speed and lower power

////	According to Nucleo-64 MB1136: USART2 interface is on PA2 and PA3
////	Port A pin 2 Port A pin 3 (zero indexed)
////	USART Code
//	
//	RCC->APB1ENR |= ( RCC_APB1ENR_USART2EN );
//	RCC->APB2ENR |= 0x1;
//	// Configure pins A2, A3 for USART2
//	// A2 is the TX
//	// We should probably clear both PA2 and PA3before doing this
//	// The first 0x3 is the bit to write AKA 11 in binary. this is to clear!
//	// We need MODER to be in 10 "Alertante function mode"
//	GPIOA->MODER &= ~(	(0x3ul << (2*2) ) |
//										(0x3 << (3*2) ) );
//	GPIOA->MODER |= ( (0x2 << (2*2) ) |
//										(0x2 << (3*2) ) );
//	GPIOA->OSPEEDR &= ~(	(0x3ul << (2*2) ) |
//										(0x3 << (3*2) ) );	
//	GPIOA->OSPEEDR &= (	(0x2 << (2*2) ) |
//										(0x2 << (3*2) ) );
//	//Now need to set alternate function to USART2 for PA2 and PA3 (AF7)
//	GPIOA->AFR[0] &= ~( (0xFul << 2*4) | (0xF << 3 * 4));
//	GPIOA->AFR[0] |= (( 0x7 << 2*4) | (0x7 << 3*4));
//	
//	//Set the Baud Rate Register. The system clock is divided by this number to get the USART speed.
//	//USART2->BRR = 0x1A1; //potentially we're actually using a 4MHz clock. We'll see.
//	USART2->BRR = 0x683;
//	
//	USART2->CR1 |= ( USART_CR1_RE | USART_CR1_TE | USART_CR1_UE );
//										
//	

////	GPIOA->MODER &= ~0x000000F0ul;
////	GPIOA->MODER |=  0x00000010;
////	// A3 is the RX
////	GPIOA->MODER |= 0x
//	
//	RCC->AHB1ENR |= 1; // enable GPIOA clock

////	RCC->CR &= ~0x00000001; set clock to 16MHz

//	GPIOA->MODER &= ~0x00000C00ul; // clear pin mode
//	GPIOA->MODER |= 0x00000400ul; // set pin to output mode
//	
//	GPIOA->MODER &= ~(3ul << 0); // clear DHT11 data pin mode
//	GPIOA->MODER |= (1ul << 0); // set pin to output (which we can also use as input

//	char rxb = '\0';
//	while(1) {
//		while ( !(USART2->SR & USART_SR_RXNE) ) {}
//			rxb = USART2->DR;
//		while ( !(USART2->SR & USART_SR_TXE) ) {}
//			USART2->DR = ('a' & 0xFF);
//		
//		
//		
//		//printf("test");
//		

////		GPIOA->BSRR = 0x00000020; //turn on LED
////		delayMs(500);
////		/* GPIOA->BSRR = ~0x00000020; 
////		GPIOA->BSRR = 0x00200000; //turn off LED 
////		delayMs(500);
//			
//	}
}

// Enable the System SYSCLK to 16 MHz
// We will use the HSI (High Speed Internal) clock with no prescalers
// You can also use an extrnal clock or a crystal HSE (High Speed External), but not in this program.
void clkInit(void) {
	
}

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

// 16 MHz SYSCLK
void delayMs(int n) {
	int i;
	for (; n > 0; n--)
	for (i = 0; i < 3195; i++) ;
}





//#include <stdint.h>
////#include "stm32f4xx.h"
//#include "stm32f446.h"

//// Function Prototypes
//void uart2_tx_init(void);
//static uint16_t compute_uart_bd(uint32_t PCLK, uint32_t Baudrate);
//void uart2_write(int ch);

//// 

//int main(void)
//{
//	uart2_tx_init();

//	while(1)
//	{
//		uart2_write('Y');
//	}
//}


//void uart2_tx_init(void)
//{
//	//Turns on the clock for GPIO Port A
//	pRCC->AHB1ENR |= (1 << 0);

//	//Sets PA2 to alternate function mode
//	pGPIOA->MODER |= (0b10 << 4);

//	//Sets pin PA2 to USART2_TX
//	pGPIOA->AFRL |= (0b0111 << 8);



//	//Turn on USART2 clock
//	pRCC->APB1ENR |= (1 << 17);


//	pUSART2->BRR |= compute_uart_bd(APB1_CLK, USART_BAUDRATE);

//	//Enables transmitter
//	pUSART2->CR1 = (1 << 3);

//	//Enables the USART
//	pUSART2->CR1 |= (1 << 13);
//}


//static uint16_t compute_uart_bd(uint32_t PCLK, uint32_t Baudrate)
//{
//	return ((PCLK + (Baudrate/2))/Baudrate);
//}


//void uart2_write(int ch)
//{
//	//Make sure the transmit data register is empty
//	while(!((pUSART2->SR) & (1 << 7)));

//	//Write to transmit data register
//	pUSART2->DR= (ch & 0xFF);
//}
