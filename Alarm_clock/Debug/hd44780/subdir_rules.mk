################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
hd44780/%.obj: ../hd44780/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/Brandon Chase/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Brandon Chase/ccs/ccs_base/arm/include" --include_path="C:/Users/Brandon Chase/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Brandon Chase/workspace_v9/Alarm_clock" --include_path="C:/Users/Brandon Chase/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="hd44780/$(basename $(<F)).d_raw" --obj_directory="hd44780" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


