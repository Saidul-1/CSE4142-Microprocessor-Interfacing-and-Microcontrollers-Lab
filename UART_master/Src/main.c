#define RCC_BASE (0x40023800)
#define GPIOA_BASE (0x40020000)
#define UART_BASE (0x40011000)

#define AHB1_ENR (*(volatile int*)(RCC_BASE+0x30))
#define APB2_ENR (*(volatile int*)(RCC_BASE+0x44))

#define GPIOA_MODER (*(volatile int*)(GPIOA_BASE+0x00))
#define GPIOA_AFRH (*(volatile int*)(GPIOA_BASE+0x24))

#define UART_BRR (*(volatile int*)(UART_BASE+0x08))
#define UART_CR1 (*(volatile int*)(UART_BASE+0x0C))
#define UART_SR (*(volatile int*)(UART_BASE+0x00))
#define UART_DR (*(volatile int*)(UART_BASE+0x04))

#define SYSCLK 16000000U
#define BAUDRATE 9600U

void uart_init() {
	AHB1_ENR |= (1<<0);


	GPIOA_MODER |= (1<<19);
	GPIOA_MODER &= ~(1<<18);

	GPIOA_AFRH &= ~(0xF<<4);
	GPIOA_AFRH |= (0x7<<4);

	APB2_ENR |= (1<<4);

	UART_BRR = (SYSCLK+BAUDRATE/2)/BAUDRATE;

	UART_CR1 |= (1<<3);
	UART_CR1 |= (1<<13);

}
void uart_send(int n, char* str) {
	for(int i = 0; i < n; i++) {
		while(!(UART_SR&(1<<7)));
		UART_DR = *str++;
	}
}
int main() {
	uart_init();
	while(1) {
		uart_send(6, "CSE_RU");
	}
}
