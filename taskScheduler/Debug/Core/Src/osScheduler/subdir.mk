################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/osScheduler/osScheduler.c 

OBJS += \
./Core/Src/osScheduler/osScheduler.o 

C_DEPS += \
./Core/Src/osScheduler/osScheduler.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/osScheduler/osScheduler.o: ../Core/Src/osScheduler/osScheduler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"/Users/ko106n4/Desktop/taskScheduler/taskScheduler/Core/Src/osScheduler" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/osScheduler/osScheduler.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

