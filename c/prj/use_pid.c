#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "delay.h"
#include "segled.h"
#include "max6675.h"
#include "pid.h"


#define F_CPU 48000000
#define tick 1000
#define systick_ms 1
#define systick_val (F_CPU/tick)*systick_ms
#define button_ 1


/*! \brief P, I and D parameter values
 *
 * The K_P, K_I and K_D values (P, I and D gains)
 * need to be modified to adapt to the application at hand
 */
//! \xrefitem todo "Todo" "Todo list"
#define K_P     1.00
//! \xrefitem todo "Todo" "Todo list"
#define K_I     0.00
//! \xrefitem todo "Todo" "Todo list"
#define K_D     0.00

uint8_t stat;

/*! \brief Flags for status information
 */
struct GLOBAL_FLAGS {
  //! True when PID control loop should run one time
  uint8_t pidTimer:1;
  uint8_t dummy:7;
} gFlags = {0, 0};

//! Parameters for regulator
struct PID_DATA pidData;

struct flags
{
	unsigned led_indicator_delay : 1;
}flag;

struct buttons
{
	unsigned counter :16;
	unsigned current_state :1;
	unsigned last_state :1;
	unsigned min_press :6; 
	unsigned max_press :16;
	unsigned long_press :1;
	unsigned short_press :1; 
}button, encoder;

struct task
{
	unsigned counter :12;
	unsigned flag :1;
}pid;

void SysTick_Handler (void)
{
	
	//increment button's and encoder's counters 
	if (!(button.long_press||button.short_press))button.counter++;
	
	if (!(encoder.long_press||encoder.short_press))encoder.counter++;
	
	if (flag.led_indicator_delay)flag.led_indicator_delay = 0;
	else
	{
		led_number();
		flag.led_indicator_delay = 1;
	}
	if (pid.counter>400)
	{
		pid.flag = 1;
		pid.counter = 0;
	}
	else pid.counter++;
	//Cheking press button
	button.current_state = !(GPIOA->IDR&1 << button_);
	
	if (!(button.last_state&&button.current_state))button.counter = 0;;
	button.last_state = button.current_state;
	
	if (button.counter>button.min_press) button.short_press = 1;
}

void init_buttons(void)
{
	button.last_state = button.current_state = 0;
	button.min_press = 20;
	button.max_press = 1000;
}


int main ()
{
	int16_t referenceValue, measurementValue, inputValue;
	referenceValue = 40;
	pid_Init(K_P * SCALING_FACTOR, K_I * SCALING_FACTOR , K_D * SCALING_FACTOR , &pidData);
	segled_init ();
	SysTick_Config (systick_val);
	max6675_init();
	
	//buffer (6523);
	while (1)
	{
		if (pid.flag)
		{
			measurementValue = readCelsius();
			inputValue = pid_Controller(referenceValue, measurementValue, &pidData);
			segled_buffer (inputValue);
			pid.flag = 0;
		}
	}
	
	
}

