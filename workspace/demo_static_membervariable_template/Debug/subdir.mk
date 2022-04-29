################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/sop/Documents/talks/Firmenkurse/workshop/sources/CPPCourseAdvanced/src/setToDummy.cpp \
/Users/sop/Documents/talks/Firmenkurse/workshop/sources/CPPCourseAdvanced/src/templatewithstaticmember.cpp 

CPP_DEPS += \
./setToDummy.d \
./templatewithstaticmember.d 

OBJS += \
./setToDummy.o \
./templatewithstaticmember.o 


# Each subdirectory must supply rules for building sources it contributes
setToDummy.o: /Users/sop/Documents/talks/Firmenkurse/workshop/sources/CPPCourseAdvanced/src/setToDummy.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O0 -g3 -pedantic -Wall -Wextra -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

templatewithstaticmember.o: /Users/sop/Documents/talks/Firmenkurse/workshop/sources/CPPCourseAdvanced/src/templatewithstaticmember.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O0 -g3 -pedantic -Wall -Wextra -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./setToDummy.d ./setToDummy.o ./templatewithstaticmember.d ./templatewithstaticmember.o

.PHONY: clean--2e-

