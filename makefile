# STM8 device (for supported devices see stm8s.h)
DEVICE       = STM8L05X_LD_VL
MCU          = STM8L05X_LD_VL

SDCC         = sdcc

# Add process specific arguments here
CFLAGS       = -lstm8
CFLAGS      += -mstm8
CFLAGS      += --opt-code-size
CFLAGS      += --std-sdcc99
CFLAGS      += --nogcse
#CFLAGS      += --vc --debug

CFLAGS      += --out-fmt-elf

CFLAGS       = -mstm8 --out-fmt-elf --all-callee-saves --debug --verbose --stack-auto --fverbose-asm  --float-reent --no-peep
#CFLAGS      += --all-callee-saves
#CFLAGS      += --debug
#CFLAGS      += --verbose
#CFLAGS      += --stack-auto
#CFLAGS      += --fverbose-asm
#CFLAGS      += --float-reent
#CFLAGS      += --no-peep

SOURCE       = \
user/main.c \
user/bsp/adc_func.c \
user/bsp/initialization.c \
user/bsp/rtc.c \
user/bsp/stm8l15x_it.c \
user/bsp/uart.c \
user/common/common.c \
user/common/gp_sub.c \
user/key/key_process.c \
user/oled_6448/oled_6448.c \
user/print/my_printf.c \
user/temp_humi/ntc.c \
user/temp_humi/th_test.c

SOURCE_DIR   = .
OUTPUT_DIR   = $(SOURCE_DIR)/build
StdPeriph    = $(SOURCE_DIR)/StdPeriph/STM8L15x-16x-05x/Libraries/STM8L15x_StdPeriph_Driver

# Add include paths here
INCLUDEPATH  = -I$(StdPeriph)/inc
INCLUDEPATH += -I$(SOURCE_DIR)/user
INCLUDEPATH += -I$(SOURCE_DIR)/user/bsp
INCLUDEPATH += -I$(SOURCE_DIR)/user/common
INCLUDEPATH += -I$(SOURCE_DIR)/user/key
INCLUDEPATH += -I$(SOURCE_DIR)/user/oled_6448
INCLUDEPATH += -I$(SOURCE_DIR)/user/print
INCLUDEPATH += -I$(SOURCE_DIR)/user/temp_humi

def: compile flash

all: clean compile_obj compile

compile:
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ $(SOURCE_DIR)/$(SOURCE).c \
	$(OUTPUT_DIR)/stm8l15x_adc.rel
	$(OUTPUT_DIR)/stm8l15x_aes.rel
	$(OUTPUT_DIR)/stm8l15x_beep.rel
	$(OUTPUT_DIR)/stm8l15x_clk.rel
	$(OUTPUT_DIR)/stm8l15x_comp.rel
	$(OUTPUT_DIR)/stm8l15x_dac.rel
	$(OUTPUT_DIR)/stm8l15x_dma.rel
	$(OUTPUT_DIR)/stm8l15x_exti.rel
	$(OUTPUT_DIR)/stm8l15x_flash.rel
	$(OUTPUT_DIR)/stm8l15x_gpio.rel
	$(OUTPUT_DIR)/stm8l15x_i2c.rel
	$(OUTPUT_DIR)/stm8l15x_irtim.rel
	$(OUTPUT_DIR)/stm8l15x_itc.rel
	$(OUTPUT_DIR)/stm8l15x_iwdg.rel
	$(OUTPUT_DIR)/stm8l15x_lcd.rel
	$(OUTPUT_DIR)/stm8l15x_pwr.rel
	$(OUTPUT_DIR)/stm8l15x_rst.rel
	$(OUTPUT_DIR)/stm8l15x_rtc.rel
	$(OUTPUT_DIR)/stm8l15x_spi.rel
	$(OUTPUT_DIR)/stm8l15x_syscfg.rel
	$(OUTPUT_DIR)/stm8l15x_tim1.rel
	$(OUTPUT_DIR)/stm8l15x_tim2.rel
	$(OUTPUT_DIR)/stm8l15x_tim3.rel
	$(OUTPUT_DIR)/stm8l15x_tim4.rel
	$(OUTPUT_DIR)/stm8l15x_tim5.rel
	$(OUTPUT_DIR)/stm8l15x_usart.rel
	$(OUTPUT_DIR)/stm8l15x_wfe.rel
	$(OUTPUT_DIR)/stm8l15x_wwdg.rel
#	--out-fmt-elf --all-callee-saves --debug --verbose --stack-auto --fverbose-asm  --float-reent --no-peep

compile_obj:
	mkdir -p $(OUTPUT_DIR)
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_adc.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_aes.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_beep.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_clk.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_comp.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_dac.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_dma.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_exti.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_flash.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_gpio.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_i2c.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_irtim.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_itc.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_iwdg.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_lcd.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_pwr.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_rst.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_rtc.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_spi.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_syscfg.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_tim1.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_tim2.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_tim3.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_tim4.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_tim5.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_usart.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_wfe.c
	$(SDCC) $(CFLAGS) $(INCLUDEPATH) -D $(DEVICE) -o $(OUTPUT_DIR)/ -c $(StdPeriph)/src/stm8l15x_wwdg.c

clean:
	rm -Rrf $(OUTPUT_DIR)

flash:
	stm8flash -c stlinkv2 -p $(MCU) -w $(OUTPUT_DIR)/$(SOURCE).elf

openocd:
	openocd -f interface/stlink.cfg -f target/stm8s003.cfg -c "init" -c "reset halt"