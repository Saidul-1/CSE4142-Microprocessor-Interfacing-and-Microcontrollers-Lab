#define RCC_BASE (0x40023800)
#define GPIOB_BASE (0x40020400)
#define I2C1_BASE (0x40005400)

#define RCC_AHB1ENR (*(volatile int*)(RCC_BASE+0x30))
#define RCC_APB1ENR (*(volatile int*)(RCC_BASE+0x40))

#define GPIOB_MODER (*(volatile int*)(GPIOB_BASE+0x00))
#define GPIOB_OTYPER (*(volatile int*)(GPIOB_BASE+0x04))
#define GPIOB_PUPDR (*(volatile int*)(GPIOB_BASE+0x0C))
#define GPIOB_AFRH (*(volatile int*)(GPIOB_BASE+0x24))

#define I2C1_CR1 (*(volatile int*)(I2C1_BASE+0x00))
#define I2C1_CR2 (*(volatile int*)(I2C1_BASE+0x04))
#define I2C1_CCR (*(volatile int*)(I2C1_BASE+0x1C))
#define I2C1_TRISE (*(volatile int*)(I2C1_BASE+0x20))

#define I2C1_SR1 (*(volatile int*)(I2C1_BASE+0x14))
#define I2C1_SR2 (*(volatile int*)(I2C1_BASE+0x18))

#define I2C1_DR (*(volatile int*)(I2C1_BASE+0x10))

void i2c1_init() {
	RCC_AHB1ENR |= (1<<1);

	GPIOB_MODER |= (1<<19);
	GPIOB_MODER &= ~(1<<18);
	GPIOB_MODER |= (1<<17);
	GPIOB_MODER &= ~(1<<16);

	GPIOB_OTYPER |= (1<<9);
	GPIOB_OTYPER |= (1<<8);

	GPIOB_PUPDR &= ~(1<<19);
	GPIOB_PUPDR |= (1<<18);
	GPIOB_PUPDR &= ~(1<<17);
	GPIOB_PUPDR |= (1<<16);

	GPIOB_AFRH &= ~(0xFF);
	GPIOB_AFRH |= (1<<6);
	GPIOB_AFRH |= (1<<2);

	RCC_APB1ENR |= (1<<21);


	I2C1_CR1 |= (1<<15);
	I2C1_CR1 &= ~(1<<15);

	I2C1_CR2 |= (1<<4);

	I2C1_CCR = 80;
	I2C1_TRISE = 17;

	I2C1_CR1 |= (1<<0);
}
void i2c1_send(char saddr, int n, char* str) {
	while(I2C1_SR2&(1<<1));
	I2C1_CR1 |= (1<<8);
	while(!(I2C1_SR1&(1<<0)));
	I2C1_DR = (saddr<<1);
	while(!(I2C1_SR1&(1<<1)));
	(void)I2C1_SR2;
	for(int i = 0; i < n; i++) {
		while(!(I2C1_SR1&(1<<7)));
		I2C1_DR = *str++;
	}
	while(!(I2C1_SR1&(1<<2)));
	I2C1_CR1 |= (1<<9);
}
int main(void) {
	i2c1_init();
	while(1) {
		i2c1_send(0x12, 6, "CSE-RU");
	}
}
