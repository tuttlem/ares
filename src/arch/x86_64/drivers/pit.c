
#include <types.h>
#include <interrupt.h>
#include <drivers.h>

#include <pit.h>

volatile uint64_t _ares_ticks = 0;

void pit_clock_handler(struct _registers regs) {
    _ares_ticks++;
}

int pit_driver_init() {
    pit_init(100);
    interrupt_register_handler(IRQ0, pit_clock_handler);

    return 0;
}

driver_t _ares_pit_driver = {
    .name = "pit",
    .init = pit_driver_init,
    .term = NULL
};