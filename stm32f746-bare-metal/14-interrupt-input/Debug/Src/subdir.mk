################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/exti.c \
../Src/gpio.c \
../Src/led.c \
../Src/main.c \
../Src/rcc.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/systick.c \
../Src/tim.c \
../Src/uart.c 

OBJS += \
./Src/adc.o \
./Src/exti.o \
./Src/gpio.o \
./Src/led.o \
./Src/main.o \
./Src/rcc.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/systick.o \
./Src/tim.o \
./Src/uart.o 

C_DEPS += \
./Src/adc.d \
./Src/exti.d \
./Src/gpio.d \
./Src/led.d \
./Src/main.d \
./Src/rcc.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/systick.d \
./Src/tim.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F746NGHx -DSTM32F7 -DSTM32F746xx -c -I../Inc -I"D:/01 Jupiter/OneDrive/05-embedded-learning/STM32Cube/01-udemy/chip-header-files/CMSIS/Include" -I"D:/01 Jupiter/OneDrive/05-embedded-learning/STM32Cube/01-udemy/chip-header-files/CMSIS/Device/ST/STM32F7xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc.cyclo ./Src/adc.d ./Src/adc.o ./Src/adc.su ./Src/exti.cyclo ./Src/exti.d ./Src/exti.o ./Src/exti.su ./Src/gpio.cyclo ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/led.cyclo ./Src/led.d ./Src/led.o ./Src/led.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/rcc.cyclo ./Src/rcc.d ./Src/rcc.o ./Src/rcc.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/systick.cyclo ./Src/systick.d ./Src/systick.o ./Src/systick.su ./Src/tim.cyclo ./Src/tim.d ./Src/tim.o ./Src/tim.su ./Src/uart.cyclo ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src

