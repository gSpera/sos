ARM := arm-none-eabi-
LINKER_SCRIPT := linker.ld
KERNEL_ELF := kernel.elf
KERNEL := kernel7.img
SRCSC   := $(wildcard kernel/*.c)
SRCSASM := $(wildcard kernel/*.s)
SRCS    := $(SRCSC) $(SRCSASM)
OBJECTSC   := $(patsubst kernel/%.c,obj/%.o,$(SRCSC))
OBJECTSASM := $(patsubst kernel/%.s,obj/%.o,$(SRCSASM))
OBJECTS    := $(OBJECTSC) $(OBJECTSASM)
PREPROCESSOR := gpp
LIST := kernel.list
MAP_FILE := kernel.map
CFLAGS := -g -Os
LDFLAGS := -g --no-undefined
UBOOTOUT := sos.uboot

all: $(UBOOTOUT) $(LIST) $(MAP_FILE)

$(UBOOTOUT): $(KERNEL)
	mkimage -A arm -T standalone -C none -c 0x8000 -a 0x8000 -d $(KERNEL) $(UBOOTOUT)

$(KERNEL): $(KERNEL_ELF)
	$(ARM)objcopy $(KERNEL_ELF) -O binary $(KERNEL)

$(KERNEL_ELF) $(MAP_FILE): $(OBJECTS) 
	$(ARM)ld $(LDFLAGS) $(OBJECTS) -o $(KERNEL_ELF) -T $(LINKER_SCRIPT) -Map $(MAP_FILE)

obj/%.o: kernel/%.s
	$(ARM)as -g -o $@ $<
obj/%.o: kernel/%.c
	$(ARM)gcc -c $(CFLAGS) -o $@ $< -nostdlib -ffreestanding

$(LIST): $(KERNEL_ELF)
	$(ARM)objdump -S $(KERNEL_ELF) > $(LIST)

clean:
	rm -f $(OBJECTS)
	rm -f $(KERNEL)
	rm -f $(KERNEL_ELF)
	rm -f $(MAP_FILE)
	rm -f $(LIST)
