################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include Utilities/STM32L1xx_Nucleo/subdir.mk
-include Third_party/FreeRTOS/org/Source/portable/MemMang/subdir.mk
-include Third_party/FreeRTOS/org/Source/portable/GCC/ARM_CM3/subdir.mk
-include Third_party/FreeRTOS/org/Source/subdir.mk
-include HAL_Driver/Src/subdir.mk
-include Drivers/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Water_level.elf

# Tool invocations
Water_level.elf: $(OBJS) $(USER_OBJS) /home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/LinkerScript.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -T"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "Water_level.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "Water_level.elf" "Water_level.bin"
	arm-none-eabi-size "Water_level.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
