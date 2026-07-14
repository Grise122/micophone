################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/stm32cube/STM32CubeExpansion_MEMSMIC1_V5.9.0/Projects/STM32L4R9ZI-STWIN/Demonstration/micophone/Patch/stm32l4xx_hal_pcd_patch.c 

OBJS += \
./Application/Patch/stm32l4xx_hal_pcd_patch.o 

C_DEPS += \
./Application/Patch/stm32l4xx_hal_pcd_patch.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Patch/stm32l4xx_hal_pcd_patch.o: D:/stm32cube/STM32CubeExpansion_MEMSMIC1_V5.9.0/Projects/STM32L4R9ZI-STWIN/Demonstration/micophone/Patch/stm32l4xx_hal_pcd_patch.c Application/Patch/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L4R9xx -DUSE_USB_FS -DARM_MATH_CM4 -c -I../../../Inc -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc -I../../../../../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/CMSIS/DSP/Include -I../../../../../../../Drivers/BSP/STWIN -I../../../../../../../Drivers/BSP/Components/Common -O0 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-Application-2f-Patch

clean-Application-2f-Patch:
	-$(RM) ./Application/Patch/stm32l4xx_hal_pcd_patch.cyclo ./Application/Patch/stm32l4xx_hal_pcd_patch.d ./Application/Patch/stm32l4xx_hal_pcd_patch.o ./Application/Patch/stm32l4xx_hal_pcd_patch.su

.PHONY: clean-Application-2f-Patch

