################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/FastMathFunctions.c 

OBJS += \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/FastMathFunctions.o 

C_DEPS += \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/FastMathFunctions.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/Source/FastMathFunctions/%.o Drivers/CMSIS/DSP/Source/FastMathFunctions/%.su Drivers/CMSIS/DSP/Source/FastMathFunctions/%.cyclo: ../Drivers/CMSIS/DSP/Source/FastMathFunctions/%.c Drivers/CMSIS/DSP/Source/FastMathFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -D__FPU_PRESENT=1 -c -I../Core/Inc -I/$(ProjName)/Drivers/CMSIS/DSP/Include -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32f4xx_HAL_Drier/Inc -I../Driers/STM32f4xx_HAL_Drive/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-FastMathFunctions

clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-FastMathFunctions:
	-$(RM) ./Drivers/CMSIS/DSP/Source/FastMathFunctions/FastMathFunctions.cyclo ./Drivers/CMSIS/DSP/Source/FastMathFunctions/FastMathFunctions.d ./Drivers/CMSIS/DSP/Source/FastMathFunctions/FastMathFunctions.o ./Drivers/CMSIS/DSP/Source/FastMathFunctions/FastMathFunctions.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-FastMathFunctions

