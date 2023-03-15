################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Third_party/FreeRTOS/org/Source/croutine.c \
../Third_party/FreeRTOS/org/Source/event_groups.c \
../Third_party/FreeRTOS/org/Source/list.c \
../Third_party/FreeRTOS/org/Source/queue.c \
../Third_party/FreeRTOS/org/Source/stream_buffer.c \
../Third_party/FreeRTOS/org/Source/tasks.c \
../Third_party/FreeRTOS/org/Source/timers.c 

OBJS += \
./Third_party/FreeRTOS/org/Source/croutine.o \
./Third_party/FreeRTOS/org/Source/event_groups.o \
./Third_party/FreeRTOS/org/Source/list.o \
./Third_party/FreeRTOS/org/Source/queue.o \
./Third_party/FreeRTOS/org/Source/stream_buffer.o \
./Third_party/FreeRTOS/org/Source/tasks.o \
./Third_party/FreeRTOS/org/Source/timers.o 

C_DEPS += \
./Third_party/FreeRTOS/org/Source/croutine.d \
./Third_party/FreeRTOS/org/Source/event_groups.d \
./Third_party/FreeRTOS/org/Source/list.d \
./Third_party/FreeRTOS/org/Source/queue.d \
./Third_party/FreeRTOS/org/Source/stream_buffer.d \
./Third_party/FreeRTOS/org/Source/tasks.d \
./Third_party/FreeRTOS/org/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Third_party/FreeRTOS/org/Source/%.o: ../Third_party/FreeRTOS/org/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32L1 -DSTM32L152RETx -DNUCLEO_L152RE -DDEBUG -DSTM32L152xE -DUSE_HAL_DRIVER -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/Utilities/STM32L1xx_Nucleo" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/Drivers/includes" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/Third_party/FreeRTOS/org/Source/include" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/Third_party/FreeRTOS/org/Source/portable/GCC/ARM_CM3" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/Config" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/HAL_Driver/Inc/Legacy" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/inc" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/CMSIS/device" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/CMSIS/core" -I"/home/silvere/Work/Tuto/RTOS/RTOS_Workspace/Water_level/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


