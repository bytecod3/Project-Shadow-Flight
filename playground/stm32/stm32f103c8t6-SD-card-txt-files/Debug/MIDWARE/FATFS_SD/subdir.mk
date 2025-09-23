################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MIDWARE/FATFS_SD/FATFS_SD.c 

OBJS += \
./MIDWARE/FATFS_SD/FATFS_SD.o 

C_DEPS += \
./MIDWARE/FATFS_SD/FATFS_SD.d 


# Each subdirectory must supply rules for building sources it contributes
MIDWARE/FATFS_SD/%.o MIDWARE/FATFS_SD/%.su MIDWARE/FATFS_SD/%.cyclo: ../MIDWARE/FATFS_SD/%.c MIDWARE/FATFS_SD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MIDWARE-2f-FATFS_SD

clean-MIDWARE-2f-FATFS_SD:
	-$(RM) ./MIDWARE/FATFS_SD/FATFS_SD.cyclo ./MIDWARE/FATFS_SD/FATFS_SD.d ./MIDWARE/FATFS_SD/FATFS_SD.o ./MIDWARE/FATFS_SD/FATFS_SD.su

.PHONY: clean-MIDWARE-2f-FATFS_SD

