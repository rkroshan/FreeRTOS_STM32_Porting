################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o: ../FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DDEBUG -c -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/CMSIS/core" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/FreeRTOS/Source/include" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/CMSIS/device" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/startup" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/StdPeriph_Driver/inc" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

