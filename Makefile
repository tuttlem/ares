CC 	    := gcc
CFLAGS 	:= -m64 -mcmodel=kernel -ffreestanding -nostdlib -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow -Ikernel/include
AS	    := nasm
AFLAGS	:= -felf64
LD	    := ld
LFLAGS	:= -nostdlib -z nodefaultlib -z max-page-size=0x1000
ISO     := os.iso
OUTPUT  := kernel.sys

OBJS := boot/boot.o kernel/asm/isr.o init/main.o kernel/io.o kernel/idt.o kernel/interrupt.o kernel/pit.o kernel/console.o kernel/string.o kernel/panic.o kernel/printf.o kernel/cpuid.o

all: $(ISO)

$(ISO): $(OUTPUT)
	cp $(OUTPUT) iso/boot
	grub-mkrescue -o $@ iso

$(OUTPUT): $(OBJS) linker.ld
	$(LD) $(LFLAGS) -Tlinker.ld -o $@ $(OBJS)

.s.o:
	$(AS) $(AFLAGS) $< -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(OUTPUT) $(ISO) iso/boot/$(OUTPUT)


