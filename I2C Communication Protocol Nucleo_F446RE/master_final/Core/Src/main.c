// List of Register Declarations
#define RCC_BASE   (0x40023800)
#define GPIOA_BASE (0x40020000)
#define GPIOB_BASE (0x40020400)
#define I2C1_BASE  (0x40005400)
#define TIM2_BASE  (0x40000000)

#define RCC_AHB1ENR (*(volatile unsigned int *)(RCC_BASE + 0x30))
#define RCC_APB1ENR (*(volatile unsigned int *)(RCC_BASE + 0x40))

#define GPIOA_MODER (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_OTYPER (*(volatile unsigned int *)(GPIOA_BASE + 0x04))
#define GPIOA_ODR   (*(volatile unsigned int *)(GPIOA_BASE + 0x14))

#define GPIOB_MODER (*(volatile unsigned int *)(GPIOB_BASE + 0x00))
#define GPIOB_OTYPER (*(volatile unsigned int *)(GPIOB_BASE + 0x04))
#define GPIOB_PUPDR (*(volatile unsigned int *)(GPIOB_BASE + 0x0C))
#define GPIOB_AFRH  (*(volatile unsigned int *)(GPIOB_BASE + 0x24))

#define I2C1_CR1 (*(volatile unsigned int *)(I2C1_BASE + 0x00))
#define I2C1_CR2 (*(volatile unsigned int *)(I2C1_BASE + 0x04))
#define I2C1_CCR (*(volatile unsigned int *)(I2C1_BASE + 0x1C))
#define I2C1_TRISE (*(volatile unsigned int *)(I2C1_BASE + 0x20))
#define I2C1_SR1 (*(volatile unsigned int *)(I2C1_BASE + 0x14))
#define I2C1_SR2 (*(volatile unsigned int *)(I2C1_BASE + 0x18))
#define I2C1_DR  (*(volatile unsigned int *)(I2C1_BASE + 0x10))

#define TIM2_PSC (*(volatile unsigned int *)(TIM2_BASE + 0x28))
#define TIM2_ARR (*(volatile unsigned int *)(TIM2_BASE + 0x2C))
#define TIM2_CR1 (*(volatile unsigned int *)(TIM2_BASE + 0x00))
#define TIM2_SR  (*(volatile unsigned int *)(TIM2_BASE + 0x10))

//function definition to reduce warning
void I2C1_Init();


//send function
void I2C1_Send(char saddr, int n, char* str);


//main function

int main(void) {
	I2C1_Init();
	while(1) {
		I2C1_Send(0x12, 6, "Shakil");
	}
}



void I2C1_Init() {

	/*Enable clock of GPIOB through AHB1ENR--144*/
	RCC_AHB1ENR |= (1<<1);

	/*Set PB8 & PB9 mode to alternate function through GPIOB_MODER , default input mode-- 187*/
	GPIOB_MODER |= (1<<19);
	GPIOB_MODER &= ~(1<<18);
	GPIOB_MODER |= (1<<17);
	GPIOB_MODER &= ~(1<<16);

	/*Set PB8 & PB9 output type to open-drain for high to low --188*/
	GPIOB_OTYPER |= (1<<8);
	GPIOB_OTYPER |= (1<<9);

	/*Set PB8 & PB9 to output pull-up for always high and take internal power -- 189*/
	GPIOB_PUPDR &= ~(1<<19);
	GPIOB_PUPDR |= (1<<18);
	GPIOB_PUPDR &= ~(1<<17);
	GPIOB_PUPDR |= (1<<16);


	/*Set PB8 & PB9 alternate function type to I2C (AF4) for handling multiple function -- 192*/
	GPIOB_AFRH &= ~(0xFF<<0);
	GPIOB_AFRH |= (1<<2);
	GPIOB_AFRH |= (1<<6);



	/*Enable clock of I2C1 --147*/
	RCC_APB1ENR |= (1<<21);


	/*Enter I2C peripheral reset mode -- 780*/
	I2C1_CR1 |= (1<<15);

	/*Come out of reset mode --780*/
	I2C1_CR1 &= ~(1<<15);


	/*Set I2C clock frequency (default 16 MHz) -- 782*/
	I2C1_CR2 |= (1<<4);

	/*Set I2C in standard mode, 100 KHz -- 790*/
	//	       CCR = f_PCLK1 / (2 * f_SCL)
	//	    	   = 16,000,000 / (2 * 100,000)
	//	    	   = 80


	I2C1_CCR = 80;

	/*Set rise time --- 761  & 791*/

	// 		   TRISE = (t_r * f_PCLK1) + 1
	// 		   		 = (1x10^-6 * 16x10^6) + 1
	// 		   		 = 17
	I2C1_TRISE = 17;

	/*Now finally enable the I2C1 -- 780*/
	I2C1_CR1 |= (1<<0);

}

void I2C1_Send(char saddr, int n, char* str) {
	/*Wait when bus is busy 789*/
	while(I2C1_SR2 & (1<<1)) {}

	/*Generate start condition and wait -- 780 & 785*/
	I2C1_CR1 |= (1<<8);
	while(!(I2C1_SR1 & (1<<0))) {}


	/*Send slave address + write (0) bit and wait for ACK -- 762 & 785*/
	I2C1_DR = (saddr<<1);
	while(!(I2C1_SR1 & (1<<1))) {}

	/*Clear ADDR flag to ensure address is sent -- 789*/
	(void)I2C1_SR2;

	for(int i = 0; i < n; i++) {

		/*Wait until transmitter is empty -- 785*/
		while(!(I2C1_SR1 & (1<<7))) {}

		/*Place the data to the data register one byte at time*/
		I2C1_DR = *str++;
	}

	/*Wait until transfer finished --788*/
	while(!(I2C1_SR1 & (1<<2))) {}

	/*Generate stop -- 780*/
	I2C1_CR1 |= (1<<9);
}
