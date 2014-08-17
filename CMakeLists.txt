cmake_minimum_required(VERSION 2.8)

project(Trutle)

file(GLOB header
	"src/*.h" 
	"src/core/*.h" 
	"src/core/event/*.h"	
	"src/node/*.h" 	
	"src/res/*.h")
file(GLOB src 
	"src/*.cpp" 
	"src/core.cpp"
	"src/core/event/*.cpp"
	"src/node/*.cpp"
	"src/res/*.cpp")

set(libs SDL2 SDL2main GL glut GLEW SDL2_image)
 
add_library(trutle ${header} ${src})
target_link_libraries(trutle ${libs})

# Configurations used for all targets
add_definitions(-std=c++11)
add_definitions(-D TRUTLE_COMPILE)


install(FILES ${header} DESTINATION "include/trutle")
install(TARGETS trutle DESTINATION "lib")
