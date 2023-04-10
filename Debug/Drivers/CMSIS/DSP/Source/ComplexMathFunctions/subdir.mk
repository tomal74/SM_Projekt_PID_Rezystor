################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/Source/ComplexMathFunctions/ComplexMathFunctions.c 

OBJS += \
./Drivers/CMSIS/DSP/Source/ComplexMathFunctions/ComplexMathFunctions.o 

C_DEPS += \
./Drivers/CMSIS/DSP/Source/ComplexMathFunctions/ComplexMathFunctions.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/%.o Drivers/CMSIS/DSP/Source/ComplexMathFunctions/%.su Drivers/CMSIS/DSP/Source/ComplexMathFunctions/%.cyclo: ../Drivers/CMSIS/DSP/Source/ComplexMathFunctions/%.c Drivers/CMSIS/DSP/Source/ComplexMathFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -D__FPU_PRESENT=1 -c -I../Core/Inc -I/$(ProjName)/Drivers/CMSIS/DSP/Include -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32f4xx_HAL_Drier/Inc -I../Driers/STM32f4xx_HAL_Drive/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-ComplexMathFunctions

clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-ComplexMathFunctions:
	-$(RM) ./Drivers/CMSIS/DSP/Source/ComplexMathFunctions/ComplexMathFunctions.cyclo ./Drivers/CMSIS/DSP/Source/ComplexMathFunctions/ComplexMathFunctions.d ./Drivers/CMSIS/DSP/Source/ComplexMathFunctions/ComplexMathFunctions.o ./Drivers/CMSIS/DSP/Source/ComplexMathFunctions/ComplexMathFunctions.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-ComplexMathFunctions

