################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MainApplication/Src/main_app.c 

OBJS += \
./MainApplication/Src/main_app.o 

C_DEPS += \
./MainApplication/Src/main_app.d 


# Each subdirectory must supply rules for building sources it contributes
MainApplication/Src/%.o MainApplication/Src/%.su MainApplication/Src/%.cyclo: ../MainApplication/Src/%.c MainApplication/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/projects/Project-Shadow-Flight/firmware/MainApplication/Inc" -I"F:/projects/Project-Shadow-Flight/firmware/FreeRTOS-Kernel/include" -I"F:/projects/Project-Shadow-Flight/firmware/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MainApplication-2f-Src

clean-MainApplication-2f-Src:
	-$(RM) ./MainApplication/Src/main_app.cyclo ./MainApplication/Src/main_app.d ./MainApplication/Src/main_app.o ./MainApplication/Src/main_app.su

.PHONY: clean-MainApplication-2f-Src

