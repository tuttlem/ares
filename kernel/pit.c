
#include <pit.h>

/* Initialize the timer to run at a frequency */
void pit_init(u32 freq) {

	/* calculate the divisor */
	u32 divisor = PIT_CLOCK_OSC / freq;

	/* send the command byte */
	outb(0x43, 0x36);

	/* before the divisor is sent, it needs to be split into
	   a high and low byte */
	u8 l = (u8)( divisor       & 0xff);
	u8 h = (u8)((divisor >> 8) & 0xff);

	/* send the frequency divisor */
	outb(0x40, l);
	outb(0x40, h);
}