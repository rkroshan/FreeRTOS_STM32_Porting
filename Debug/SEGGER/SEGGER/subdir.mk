################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SEGGER/SEGGER/SEGGER_RTT.c \
../SEGGER/SEGGER/SEGGER_SYSVIEW.c 

S_UPPER_SRCS += \
../SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./SEGGER/SEGGER/SEGGER_RTT.o \
./SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o \
./SEGGER/SEGGER/SEGGER_SYSVIEW.o 

C_DEPS += \
./SEGGER/SEGGER/SEGGER_RTT.d \
./SEGGER/SEGGER/SEGGER_SYSVIEW.d 


# Each subdirectory must supply rules for building sources it contributes
SEGGER/SEGGER/SEGGER_RTT.o: ../SEGGER/SEGGER/SEGGER_RTT.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DDEBUG -c -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/CMSIS/core" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/FreeRTOS/org/Source/include" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/CMSIS/device" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/startup" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/StdPeriph_Driver/inc" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/inc" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/Config" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/OS" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"SEGGER/SEGGER/SEGGER_RTT.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SEGGER/SEGGER/%.o: ../SEGGER/SEGGER/%.S
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/Config" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/SEGGER" -x assembler-with-cpp --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
SEGGER/SEGGER/SEGGER_SYSVIEW.o: ../SEGGER/SEGGER/SEGGER_SYSVIEW.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DDEBUG -c -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/CMSIS/core" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/FreeRTOS/org/Source/include" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/CMSIS/device" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/startup" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/StdPeriph_Driver/inc" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/inc" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/Config" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/OS" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"SEGGER/SEGGER/SEGGER_SYSVIEW.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

