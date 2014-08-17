cmake_minimum_required(VERSION 2.8)

project(Trutle)

file(GLOB src 
	"src/*.h" 				"src/*.cpp" 
	"src/core/*.h" 			"src/core/*.cpp"
	"src/core/event/*.h" 	"src/core/event/*.cpp"
	"src/node/*.h" 			"src/node/*.cpp"
	"src/res/*.h" 			"src/res/*.cpp")

set(libs SDL2 SDL2main GL glut GLEW SDL2_image)
 
add_library(trutle ${src})
target_link_libraries(trutle ${libs})

# Configurations used for all targets
add_definitions(-std=c++11)
add_definitions(-D TRUTLE_COMPILE)


# TODO: Streamline this shit :L
file(GLOB h "src/*.h")
file(GLOB hcore "src/core/*.h")
file(GLOB hcoreevent "src/core/event/*.h")
file(GLOB hnode "src/node/*.h")
file(GLOB hres "src/res/*.h")

install(FILES ${h} DESTINATION "include/trutle")
install(FILES ${hcore} DESTINATION "include/trutle/core")
install(FILES ${hcoreevent} DESTINATION "include/trutle/core/event")
install(FILES ${hnode} DESTINATION "include/trutle/node")
install(FILES ${hres} DESTINATION "include/trutle/res")

install(TARGETS trutle DESTINATION "lib")
