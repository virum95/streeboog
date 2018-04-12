#cmake_minimum_required(VERSION 3.9)
#
#set(PROJECT_NAME cracker)
#project(${PROJECT_NAME} C)
#set(CMAKE_C_STANDARD 11)
set ( CMAKE_C_FLAGS "-lssl -lcrypto")
#
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
#
#file(SRC_FILES ${SOURCE_DIR}/*.c)
#
#add_executable(${PROJECT_NAME} ${SRC_FILES} )

cmake_minimum_required(VERSION 2.6.0)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(cracker C)
set(CMAKE_C_STANDARD 11)

add_executable(cracker src/cracker-dict.c)

project(hash C)
set(CMAKE_C_STANDARD 11)

add_executable(hash src/hash.c)




project(prog C)
set(CMAKE_C_STANDARD 11)
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_C_FLAGS -lm)

add_executable(prog src/prog.c)
target_link_libraries(${PROJECT_NAME} ${LIB_DIR}/streebog/libhasher.so) # Streebog static library
