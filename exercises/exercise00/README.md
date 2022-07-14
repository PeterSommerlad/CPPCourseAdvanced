# Exercise 0

Goals of this exercise:

* You will setup your development environment for C++.
* You will create and run your first executable project
* You will split a project into a library, test and executable project


## Setup Your Environment

First we are setting up our laptops and you will exercise to use Cevelop and the C++ compiler. 
It is recommended to use the Virtual Machine provided to you.

Alternatively, you can install Cevelop and a suitable compiler on your system natively for convenience and performance reasons. Check the setup instructions here: [Setup Instructions](https://github.com/PeterSommerlad/CPPCourseIntroduction/blob/main/exercises/manualsetupenvironment.md)


## Exercises

When you have accomplished these exercises you will:

 - Be familiar with creating C++ projects in Cevelop
 - Be able to split a simple application into:
   - Library Project
   - CUTE Test Project
   - Executable Project
 - Have implemented a testable hello world application in C++
 - Have learned how to implement a unit test for a function using `std::ostream`
 - Have implemented your first simple class


### Hello World

Create a C++ project (Hello World Executable Project) in Cevelop, compile and run Hello World. This is a sanity check for your environment. Please report immediately, if you cannot make this work.

**Note:**

  - In order to build the project you need to have some of its resources selected (the project in the Project Explorer or have a file of that project open in the focused editor) and then click the Hammer icon. This will build your project. The commands executed and the errors (if any) are reported in the `Console` view of Cevelop.
  - To run the (executable) project for the first time, you need to right-click the project in the Project Explorer and select `Run As -> 1 Local C/C++ Application` from the menu.
    - You cannot run the project if you have never built it before (i.e. there must be an executable binary file in the project).
    - Running the project will build it if necessary.
    - Subsequent launches of the executable are accessible through the `Run` button in the tool bar.


### Hello World with separate Compilation Unit

  - Create a single C++ project with [Header](https://github.com/PeterSommerlad/CPPCourseIntroduction/tree/main/src/hellolib/sayhello.h), [Implementation](https://github.com/PeterSommerlad/CPPCourseIntroduction/tree/main/src/hellolib/sayhello.cpp) and [Main Program](https://github.com/PeterSommerlad/CPPCourseIntroduction/tree/main/src/hellomain/hellomain.cpp)
  - Compiling the code:
    - Build your project (Hammer icon in Cevelop).
    - Do you get any errors?
    - Read the output in the build console and understand the executed commands. You should be familiar with similar compiler calls from the Bsys module.
  - Breaking the code:
    - What happens, when you remove the `#include` preprocessor directives from either the main program or the sayhello source file?
    - Experiment with the code by applying small modifications to prevent the compilation from succeeding. See what happens in Cevelop and when you try to build your project. Try to understand the error messages.


### Hello World Library Project and Unit Test

  - Create a C++ **Static** Library Project with Cevelop that consists of the files from above.
  - Compile it.
  - Create a CUTE Test Project in your Cevelop Workspace that depends on the above library project. You can select the dependency in the `New Project` wizard on the second page (click `Next` instead of `Finish`.)
  - Change the test case in the generated Test.cpp that it actually executes `sayHello()` using a `std::ostringstream` object os. Verify the result using 

```cpp
  ASSERT_EQUAL("Hello, World!\n", os.str())
```

  - Can you make the test fail, can you make the test succeed?
    - what do you observe in the CUTE test viewer. Can you navigate to the failing test case? Can you compare the results if the test fails?
    - If unsure how to use it, try to access the documentation of CUTE test plug-in. Where is it?
  - Why don't you violate the One-Definition-Rule with the second `main()` function in the library?

