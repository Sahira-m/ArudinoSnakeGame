CC=C:\Users\ufaro\avr-gcc-12.1.0-x64-windows\avr-gcc-12.1.0-x64-windows\bin\avr-gcc
LD=C:\Users\ufaro\avr-gcc-12.1.0-x64-windows\avr-gcc-12.1.0-x64-windows\bin\avr-ld
OBJCOPY="C:\Users\ufaro\avr-gcc-12.1.0-x64-windows\avr-gcc-12.1.0-x64-windows\bin\avr-objcopy"
OBJDUMP="C:\Users\ufaro\avr-gcc-12.1.0-x64-windows\avr-gcc-12.1.0-x64-windows\bin\avr-objdump"
AVRSIZE="C:\Users\ufaro\avr-gcc-12.1.0-x64-windows\avr-gcc-12.1.0-x64-windows\bin\avr-size"
OBJISP="C:\avr\bin\avrdude"
MCU=atmega328p
CFLAGS=-Wall -Wextra  -Wundef -pedantic \
		-Os -std=gnu99 -DF_CPU=16000000UL -mmcu=${MCU} -DBAUD=19200
LDFLAGS=-mmcu=$(MCU)
PORT=\\\\.\\COM7
BIN=snake
OUT=${BIN}.hex
SOURCES = main.c millis.c max72xx.c uart.c analogRead.c joystick.c snake.c food.c

DEBUG?=1

ifeq ($(DEBUG), 1)
	OUTPUTDIR=bin/debug
else
	OUTPUTDIR=bin/release
endif

OBJS =  $(addprefix $(OUTPUTDIR)/,$(SOURCES:.c=.o))

all: $(OUTPUTDIR)  $(OUT) 

$(OBJS): Makefile

$(OUTPUTDIR)/%.o:%.c
	$(CC) $(CFLAGS) -MD -o $@ -c $<

%.lss: %.elf
	$(OBJDUMP) -h -S -s $< > $@

%.elf: $(OBJS)
	$(CC) -Wl,-Map=$(@:.elf=.map) $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@


$(OBJS):$(SOURCES)

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .fuse -R .lock -R .user_signatures -R .comment $< $@

isp: ${BIN}.hex
	$(OBJISP) -F -V -c arduino -p ${MCU} -P ${PORT} -U flash:w:$<


clean:
	del "$(OUT)"  *.map *.P *.d

$(OUTPUTDIR): 
	@mkdir "$(OUTPUTDIR)"
		   	
.PHONY: clean dirs