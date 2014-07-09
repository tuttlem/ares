CC 	:= gcc
CFLAGS 	:= -m64 -mcmodel=kernel -ffreestanding -nostdlib -mno-red-zone
AS	:= nasm
AFLAGS	:= -felf64
LD	:= ld
LFLAGS	:= -z max-page-size=0x1000 -nodefaultlibs
ISO := os.iso
OUTPUT := kernel.sys

OBJS := boot/boot.o init/main.o

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


