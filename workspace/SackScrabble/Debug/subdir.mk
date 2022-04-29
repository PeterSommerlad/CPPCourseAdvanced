################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../nikolaus.cpp \
../sackscrabble.cpp 

CPP_DEPS += \
./nikolaus.d \
./sackscrabble.d 

OBJS += \
./nikolaus.o \
./sackscrabble.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I"/Users/sop/Documents/talks/Firmenkurse/workshop/sources/CPPCourseAdvanced/workspace/SackLib" -O0 -g3 -pedantic -Wall -Wextra -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./nikolaus.d ./nikolaus.o ./sackscrabble.d ./sackscrabble.o

.PHONY: clean--2e-

