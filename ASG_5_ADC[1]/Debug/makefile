################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
ASG_5_ADC[1].lss \

FLASH_IMAGE += \
ASG_5_ADC[1].hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: ASG_5_ADC[1].elf secondary-outputs

# Tool invocations
ASG_5_ADC[1].elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ASG_5_ADC[1].map -mmcu=atmega32 -o "ASG_5_ADC[1].elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ASG_5_ADC[1].lss: ASG_5_ADC[1].elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ASG_5_ADC[1].elf  >"ASG_5_ADC[1].lss"
	@echo 'Finished building: $@'
	@echo ' '

ASG_5_ADC[1].hex: ASG_5_ADC[1].elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ASG_5_ADC[1].elf  "ASG_5_ADC[1].hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ASG_5_ADC[1].elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ASG_5_ADC[1].elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ASG_5_ADC[1].elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
