################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_Device/Target/usbd_conf.c 

OBJS += \
./USB_Device/Target/usbd_conf.o 

C_DEPS += \
./USB_Device/Target/usbd_conf.d 


# Each subdirectory must supply rules for building sources it contributes
USB_Device/Target/%.o USB_Device/Target/%.su: ../USB_Device/Target/%.c USB_Device/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G484xx -DDEBUG -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../USB_Device/App -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../USB_Device/Target -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -I../Core/ThreadSafe -I../Application -I../Application/modules -I../Application/runtime -I../Application/runtime/device_init -I../Application/runtime/ISR -I../Application/runtime/tasks -I../Application/modules/USB -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-USB_Device-2f-Target

clean-USB_Device-2f-Target:
	-$(RM) ./USB_Device/Target/usbd_conf.d ./USB_Device/Target/usbd_conf.o ./USB_Device/Target/usbd_conf.su

.PHONY: clean-USB_Device-2f-Target
