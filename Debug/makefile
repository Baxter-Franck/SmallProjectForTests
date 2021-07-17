################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./tm4c1294kcpdt_startup_ccs.obj" \
"./lib/driverlib/adc.obj" \
"./lib/driverlib/aes.obj" \
"./lib/driverlib/can.obj" \
"./lib/driverlib/comp.obj" \
"./lib/driverlib/cpu.obj" \
"./lib/driverlib/crc.obj" \
"./lib/driverlib/des.obj" \
"./lib/driverlib/eeprom.obj" \
"./lib/driverlib/emac.obj" \
"./lib/driverlib/epi.obj" \
"./lib/driverlib/epi_workaround_ccs.obj" \
"./lib/driverlib/flash.obj" \
"./lib/driverlib/fpu.obj" \
"./lib/driverlib/gpio.obj" \
"./lib/driverlib/hibernate.obj" \
"./lib/driverlib/i2c.obj" \
"./lib/driverlib/interrupt.obj" \
"./lib/driverlib/lcd.obj" \
"./lib/driverlib/mpu.obj" \
"./lib/driverlib/onewire.obj" \
"./lib/driverlib/pwm.obj" \
"./lib/driverlib/qei.obj" \
"./lib/driverlib/shamd5.obj" \
"./lib/driverlib/ssi.obj" \
"./lib/driverlib/sw_crc.obj" \
"./lib/driverlib/sysctl.obj" \
"./lib/driverlib/sysexc.obj" \
"./lib/driverlib/systick.obj" \
"./lib/driverlib/timer.obj" \
"./lib/driverlib/uart.obj" \
"./lib/driverlib/udma.obj" \
"./lib/driverlib/usb.obj" \
"./lib/driverlib/watchdog.obj" \
"./sources/ioExp.obj" \
"./sources/main.obj" \
"./sources/myFunctions.obj" \
"./sources/watchdog_ext.obj" \
"../tm4c1294kcpdt.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include lib/driverlib/subdir_vars.mk
-include sources/subdir_vars.mk
-include subdir_rules.mk
-include lib/driverlib/subdir_rules.mk
-include sources/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
SmallProjectForTests.out \

EXE_OUTPUTS__QUOTED += \
"SmallProjectForTests.out" \

BIN_OUTPUTS += \
SmallProjectForTests.hex \

BIN_OUTPUTS__QUOTED += \
"SmallProjectForTests.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "SmallProjectForTests.out"

# Tool invocations
SmallProjectForTests.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C1294KCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"SmallProjectForTests.map" --heap_size=0 --stack_size=512 -i"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/lib" -i"C:/Users/furicf1/Documents/Code/Code SampleTest/SmallProjectForTests/sources" -i"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="SmallProjectForTests_linkInfo.xml" --rom_model -o "SmallProjectForTests.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

SmallProjectForTests.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: Arm Hex Utility'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armhex" --diag_wrap=off -o "SmallProjectForTests.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "tm4c1294kcpdt_startup_ccs.obj" "lib\driverlib\adc.obj" "lib\driverlib\aes.obj" "lib\driverlib\can.obj" "lib\driverlib\comp.obj" "lib\driverlib\cpu.obj" "lib\driverlib\crc.obj" "lib\driverlib\des.obj" "lib\driverlib\eeprom.obj" "lib\driverlib\emac.obj" "lib\driverlib\epi.obj" "lib\driverlib\epi_workaround_ccs.obj" "lib\driverlib\flash.obj" "lib\driverlib\fpu.obj" "lib\driverlib\gpio.obj" "lib\driverlib\hibernate.obj" "lib\driverlib\i2c.obj" "lib\driverlib\interrupt.obj" "lib\driverlib\lcd.obj" "lib\driverlib\mpu.obj" "lib\driverlib\onewire.obj" "lib\driverlib\pwm.obj" "lib\driverlib\qei.obj" "lib\driverlib\shamd5.obj" "lib\driverlib\ssi.obj" "lib\driverlib\sw_crc.obj" "lib\driverlib\sysctl.obj" "lib\driverlib\sysexc.obj" "lib\driverlib\systick.obj" "lib\driverlib\timer.obj" "lib\driverlib\uart.obj" "lib\driverlib\udma.obj" "lib\driverlib\usb.obj" "lib\driverlib\watchdog.obj" "sources\ioExp.obj" "sources\main.obj" "sources\myFunctions.obj" "sources\watchdog_ext.obj" 
	-$(RM) "tm4c1294kcpdt_startup_ccs.d" "lib\driverlib\adc.d" "lib\driverlib\aes.d" "lib\driverlib\can.d" "lib\driverlib\comp.d" "lib\driverlib\cpu.d" "lib\driverlib\crc.d" "lib\driverlib\des.d" "lib\driverlib\eeprom.d" "lib\driverlib\emac.d" "lib\driverlib\epi.d" "lib\driverlib\flash.d" "lib\driverlib\fpu.d" "lib\driverlib\gpio.d" "lib\driverlib\hibernate.d" "lib\driverlib\i2c.d" "lib\driverlib\interrupt.d" "lib\driverlib\lcd.d" "lib\driverlib\mpu.d" "lib\driverlib\onewire.d" "lib\driverlib\pwm.d" "lib\driverlib\qei.d" "lib\driverlib\shamd5.d" "lib\driverlib\ssi.d" "lib\driverlib\sw_crc.d" "lib\driverlib\sysctl.d" "lib\driverlib\sysexc.d" "lib\driverlib\systick.d" "lib\driverlib\timer.d" "lib\driverlib\uart.d" "lib\driverlib\udma.d" "lib\driverlib\usb.d" "lib\driverlib\watchdog.d" "sources\ioExp.d" "sources\main.d" "sources\myFunctions.d" "sources\watchdog_ext.d" 
	-$(RM) "lib\driverlib\epi_workaround_ccs.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

