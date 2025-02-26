cmake_minimum_required(VERSION 3.13)
message(STATUS "'${CMAKE_BUILD_TYPE}'")

set(CMAKE_SYSTEM_NAME van_turco)
set(TOOLCHAIN_PREFIX arm-none-eabi)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc REQUIRED)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++ REQUIRED)

set(CMAKE_SYSTEM_PROCESSOR cortex-m0)

set(THREADX_ARCH "cortex_m0")
set(THREADX_TOOLCHAIN "gnu")

set(MCPU_FLAGS "-mthumb -mcpu=cortex-m0")
set(VFP_FLAGS "")
set(SPEC_FLAGS "--specs=nosys.specs")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_FLAGS   "${MCPU_FLAGS} ${VFP_FLAGS} ${SPEC_FLAGS} -fdata-sections -ffunction-sections -mlong-calls" CACHE INTERNAL "c compiler flags")
set(CMAKE_CXX_FLAGS "${MCPU_FLAGS} ${VFP_FLAGS} -fdata-sections -ffunction-sections -fno-rtti -fno-exceptions -mlong-calls" CACHE INTERNAL "cxx compiler flags")
set(CMAKE_ASM_FLAGS "${MCPU_FLAGS} ${VFP_FLAGS} -x assembler-with-cpp" CACHE INTERNAL "asm compiler flags")
set(CMAKE_EXE_LINKER_FLAGS "${MCPU_FLAGS} ${LD_FLAGS} -Wl,--gc-sections" CACHE INTERNAL "exe link flags")

SET(CMAKE_C_FLAGS_DEBUG "-Og -g -ggdb3" CACHE INTERNAL "c debug compiler flags")
SET(CMAKE_CXX_FLAGS_DEBUG "-Og -g -ggdb3" CACHE INTERNAL "cxx debug compiler flags")
SET(CMAKE_ASM_FLAGS_DEBUG "-g -ggdb3" CACHE INTERNAL "asm debug compiler flags")

SET(CMAKE_C_FLAGS_RELEASE "-O3" CACHE INTERNAL "c release compiler flags")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3" CACHE INTERNAL "cxx release compiler flags")
SET(CMAKE_ASM_FLAGS_RELEASE "" CACHE INTERNAL "asm release compiler flags")

find_program(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy)
IF (CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    MESSAGE(STATUS "DEBUG MODE")
    SET(CMAKE_BUILD_TYPE Debug)
    project(libarbys)
    add_compile_definitions(__DEBUG)
    add_executable(libarbys ./libarbys/tests/test.cpp)
ELSE()
    MESSAGE(STATUS "RELEASE MODE")
    SET(CMAKE_BUILD_TYPE Release)
    project(libarbys)
    add_executable(libarbys ./libarbys/libarbys.cpp ./libarbys/modules/**.hpp)

ENDIF()

