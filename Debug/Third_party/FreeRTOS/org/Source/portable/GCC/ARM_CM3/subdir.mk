################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Third_party/FreeRTOS/org/Source/portable/GCC/ARM_CM3/port.c 

OBJS += \
./Third_party/FreeRTOS/org/Source/portable/GCC/ARM_CM3/port.o 

C_DEPS += \
./Third_party/FreeRTOS/org/Source/portable/GCC/ARM_CM3/port.d 


# Each subdirectory must supply rules for building sources it contributes
Third_party/FreeRTOS/org/Source/portable/GCC/ARM_CM3/%.o: ../Third_party/FreeRTOS/org/Source/portable/GCC/ARM_CM3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32L1 -DSTM32L152RETx -DNUCLEO_L152RE -DDEBUG -DSTM32L152xE -DUSE_HAL_DRIVER -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/Utilities/STM32L1xx_Nucleo" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/Drivers/includes" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/Third_party/FreeRTOS/org/Source/include" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/Third_party/FreeRTOS/org/Source/portable/GCC/ARM_CM3" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/Config" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/HAL_Driver/Inc/Legacy" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/inc" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/CMSIS/device" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/CMSIS/core" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


