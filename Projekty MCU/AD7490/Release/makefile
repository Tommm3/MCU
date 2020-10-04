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
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
AD7490.lss \

FLASH_IMAGE += \
AD7490.hex \

EEPROM_IMAGE += \
AD7490.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: AD7490.elf secondary-outputs

# Tool invocations
AD7490.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,AD7490.map -mmcu=atmega8 -o "AD7490.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

AD7490.lss: AD7490.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S AD7490.elf  >"AD7490.lss"
	@echo 'Finished building: $@'
	@echo ' '

AD7490.hex: AD7490.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex AD7490.elf  "AD7490.hex"
	@echo 'Finished building: $@'
	@echo ' '

AD7490.eep: AD7490.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex AD7490.elf  "AD7490.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: AD7490.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 AD7490.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) AD7490.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
