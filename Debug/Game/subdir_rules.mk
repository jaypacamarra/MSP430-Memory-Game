################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Game/%.obj: ../Game/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="G:/My Drive/02 Education/Udemy/Microcontrollers and the C Programming Language (MSP430)/CCS workspace/Final_Project_MSP430FR6989/driverlib/MSP430FR5xx_6xx" --include_path="C:/ti/ccs1040/ccs/ccs_base/msp430/include" --include_path="G:/My Drive/02 Education/Udemy/Microcontrollers and the C Programming Language (MSP430)/CCS workspace/Final_Project_MSP430FR6989/Game" --include_path="G:/My Drive/02 Education/Udemy/Microcontrollers and the C Programming Language (MSP430)/CCS workspace/Final_Project_MSP430FR6989" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --advice:power=all --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="Game/$(basename $(<F)).d_raw" --obj_directory="Game" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

