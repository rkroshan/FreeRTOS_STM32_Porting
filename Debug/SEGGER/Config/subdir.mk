################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c 

OBJS += \
./SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o 

C_DEPS += \
./SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o: ../SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DDEBUG -c -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/CMSIS/core" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/FreeRTOS/org/Source/include" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/CMSIS/device" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/startup" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/StdPeriph_Driver/inc" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/inc" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/Config" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/OS" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

