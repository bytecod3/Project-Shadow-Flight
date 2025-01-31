################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS-Kernel/croutine.c \
../FreeRTOS-Kernel/event_groups.c \
../FreeRTOS-Kernel/list.c \
../FreeRTOS-Kernel/queue.c \
../FreeRTOS-Kernel/stream_buffer.c \
../FreeRTOS-Kernel/tasks.c \
../FreeRTOS-Kernel/timers.c 

OBJS += \
./FreeRTOS-Kernel/croutine.o \
./FreeRTOS-Kernel/event_groups.o \
./FreeRTOS-Kernel/list.o \
./FreeRTOS-Kernel/queue.o \
./FreeRTOS-Kernel/stream_buffer.o \
./FreeRTOS-Kernel/tasks.o \
./FreeRTOS-Kernel/timers.o 

C_DEPS += \
./FreeRTOS-Kernel/croutine.d \
./FreeRTOS-Kernel/event_groups.d \
./FreeRTOS-Kernel/list.d \
./FreeRTOS-Kernel/queue.d \
./FreeRTOS-Kernel/stream_buffer.d \
./FreeRTOS-Kernel/tasks.d \
./FreeRTOS-Kernel/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS-Kernel/%.o FreeRTOS-Kernel/%.su FreeRTOS-Kernel/%.cyclo: ../FreeRTOS-Kernel/%.c FreeRTOS-Kernel/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/projects/Project-Shadow-Flight/firmware/MainApplication/Inc" -I"F:/projects/Project-Shadow-Flight/firmware/FreeRTOS-Kernel/include" -I"F:/projects/Project-Shadow-Flight/firmware/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRTOS-2d-Kernel

clean-FreeRTOS-2d-Kernel:
	-$(RM) ./FreeRTOS-Kernel/croutine.cyclo ./FreeRTOS-Kernel/croutine.d ./FreeRTOS-Kernel/croutine.o ./FreeRTOS-Kernel/croutine.su ./FreeRTOS-Kernel/event_groups.cyclo ./FreeRTOS-Kernel/event_groups.d ./FreeRTOS-Kernel/event_groups.o ./FreeRTOS-Kernel/event_groups.su ./FreeRTOS-Kernel/list.cyclo ./FreeRTOS-Kernel/list.d ./FreeRTOS-Kernel/list.o ./FreeRTOS-Kernel/list.su ./FreeRTOS-Kernel/queue.cyclo ./FreeRTOS-Kernel/queue.d ./FreeRTOS-Kernel/queue.o ./FreeRTOS-Kernel/queue.su ./FreeRTOS-Kernel/stream_buffer.cyclo ./FreeRTOS-Kernel/stream_buffer.d ./FreeRTOS-Kernel/stream_buffer.o ./FreeRTOS-Kernel/stream_buffer.su ./FreeRTOS-Kernel/tasks.cyclo ./FreeRTOS-Kernel/tasks.d ./FreeRTOS-Kernel/tasks.o ./FreeRTOS-Kernel/tasks.su ./FreeRTOS-Kernel/timers.cyclo ./FreeRTOS-Kernel/timers.d ./FreeRTOS-Kernel/timers.o ./FreeRTOS-Kernel/timers.su

.PHONY: clean-FreeRTOS-2d-Kernel

