TITLE_ID = TIMEDK001
TARGET = TimeDk
PSVITAIP = 192.168.1.115

PLUGIN_OBJS = main.o
HEADERS = $(wildcard *.h)

PLUGIN_LIBS = -ltaihen_stub -ltaihenModuleUtils_stub -lSceSysclibForDriver_stub -lSceModulemgrForKernel_stub -lSceIofilemgrForDriver_stub

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CFLAGS  = -Wl,-q -Wall -O3
ASFLAGS = $(CFLAGS)

all: kplugin.skprx

kplugin.skprx: kplugin.velf
	vita-make-fself -c $< $@

kplugin.velf: kplugin.elf
	vita-elf-create -e exports.yml $< $@

kplugin.elf: $(PLUGIN_OBJS)
	$(CC) $(CFLAGS) $^ $(PLUGIN_LIBS) -o $@ -nostdlib

clean:
	@rm -rf *.velf *.elf *.vpk *.skprx $(MAIN_OBJS) $(PLUGIN_OBJS) param.sfo eboot.bin

send: eboot.bin
	curl -T eboot.bin ftp://$(PSVITAIP):1337/ux0:/app/$(TITLE_ID)/
	@echo "Sent."
