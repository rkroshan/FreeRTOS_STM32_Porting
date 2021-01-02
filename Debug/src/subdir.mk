################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/syscalls.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/main.d \
./src/syscalls.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/main.o: ../src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DDEBUG -c -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/CMSIS/core" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/FreeRTOS/org/Source/include" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/CMSIS/device" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/startup" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/StdPeriph_Driver/inc" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/inc" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/Config" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/OS" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/syscalls.o: ../src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DDEBUG -c -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/CMSIS/core" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/FreeRTOS/org/Source/include" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/CMSIS/device" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/startup" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/StdPeriph_Driver/inc" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/inc" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/Config" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/OS" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/system_stm32f4xx.o: ../src/system_stm32f4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DDEBUG -c -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/CMSIS/core" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/FreeRTOS/org/Source/include" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/CMSIS/device" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/startup" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/StdPeriph_Driver/inc" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/inc" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/Config" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/OS" -I"/home/admirer/Desktop/master_mcu_stm32/FreeRTOS_STM32_Porting/FreeRTOS_STM32_Porting/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/system_stm32f4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

