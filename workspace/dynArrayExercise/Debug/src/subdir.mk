################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dynArrayTest.cpp 

CPP_DEPS += \
./src/dynArrayTest.d 

OBJS += \
./src/dynArrayTest.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++20 -I"/Users/sop/Documents/talks/Firmenkurse/workshop/sources/CPPCourseAdvanced/workspace/dynArrayExercise/cute" -O0 -g3 -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/dynArrayTest.d ./src/dynArrayTest.o

.PHONY: clean-src

