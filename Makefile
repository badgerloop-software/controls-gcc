###############################################################################
# Default Settings
PROJECT=badgerloop
.PHONY: clean
.DEFAULT_GOAL := $(PROJECT).bin
PROC_DIR=proc
INCLUDES=-I include -I include/cmsis -I include/hal -I proc/
TERMINAL=gnome-terminal
OBJDUMP_FILE=output.txt
DEFINES=-D__STARTUP_CLEAR_BSS -D__START=main
DRIVER_PREFIX=stm32f7xx_hal_
###############################################################################


###############################################################################
# Cross Compiler Settings
TOOLCHAIN=arm-none-eabi-
ARCH_FLAGS=-mthumb -march=armv7e-m
CFLAGS=$(ARCH_FLAGS) $(DEFINES) $(CPU_DEFINES) $(INCLUDES) -Wall -ffunction-sections -fdata-sections -fno-builtin -Os
# -Os -nostdlib -lnosys

# Linker Settings
LFLAGS=--specs=nosys.specs -Wl,--gc-sections -Wl,-Map=$(PROJECT).map -T$(PROC_DIR)/link.ld
###############################################################################


###############################################################################
# Global Objects
OBJECTS += common/main.o 
OBJECTS += common/retarget.o
OBJECTS += common/nuc144.o

OBJECTS += $(PROC_DIR)/start.o
OBJECTS += $(PROC_DIR)/system_stm32f7xx.o

OBJECTS += driver/hal/stm32f7xx_hal.o

OBJECTS += driver/hal/$(DRIVER_PREFIX)gpio.o
OBJECTS += driver/hal/$(DRIVER_PREFIX)rcc.o
OBJECTS += driver/hal/$(DRIVER_PREFIX)cortex.o
OBJECTS += driver/hal/$(DRIVER_PREFIX)dma.o
OBJECTS += driver/hal/$(DRIVER_PREFIX)uart.o
OBJECTS += driver/hal/$(DRIVER_PREFIX)msp.o
OBJECTS += driver/hal/$(DRIVER_PREFIX)rcc_ex.o
###############################################################################


###############################################################################
# Source Rules
%.o: %.S
	$(TOOLCHAIN)gcc $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(TOOLCHAIN)gcc $(CFLAGS) -c -o $@ $<

$(PROJECT).elf: $(OBJECTS)
	$(TOOLCHAIN)gcc $(LFLAGS) $^ $(CFLAGS) -o $@

$(PROJECT).bin: $(PROJECT).elf
	$(TOOLCHAIN)objcopy -O binary $< $@

$(OBJDUMP_FILE): $(PROJECT).bin
	$(TOOLCHAIN)objdump -D $(PROJECT).elf > $(OBJDUMP_FILE)

clean: 
	rm -f *.bin *.map *.elf $(CPUDIR) output.txt
	find . -name '*.o' -delete

install: $(PROJECT).bin
	./$(PROC_DIR)/install.sh

debug: $(PROJECT).bin
	./$(PROC_DIR)/debug.sh

dump: $(OBJDUMP_FILE)
	$(TERMINAL) -e "vim $(OBJDUMP_FILE)"
###############################################################################

