
#include <pit.h>

/* Initialize the timer to run at a frequency */
void pit_init(uint32_t freq) {

	/* calculate the divisor */
	uint32_t divisor = PIT_CLOCK_OSC / freq;

	/* send the command byte */
	outb(0x43, 0x36);

	/* before the divisor is sent, it needs to be split into
	   a high and low byte */
	uint8_t l = (uint8_t)( divisor       & 0xff);
	uint8_t h = (uint8_t)((divisor >> 8) & 0xff);

	/* send the frequency divisor */
	outb(0x40, l);
	outb(0x40, h);
}
