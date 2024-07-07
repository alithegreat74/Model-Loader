cmake_minimum_required(VERSION 3.5.0)

set (CMAKE_CXX_STANDARD 17)

project(ModelLoader)
set(Thirdparty_Dir "${CMAKE_SOURCE_DIR}/Thirdparty")



#Getting the source files
set(Source_Dir "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SRC_FILES "${Source_Dir}/*.cpp")


include_directories(
	"${Thirdparty_Dir}/Glad/include"
	"${Source_Dir}"
)

#setting the vertex shader files
file(GLOB SHADER_FILES "${Source_Dir}/Shaders/Vertex/*.glsl")
foreach(SHADER_FILE ${SHADER_FILES})
	get_filename_component(FILE_NAME ${SHADER_FILE} NAME)
	configure_file(${SHADER_FILE} "${CMAKE_BINARY_DIR}/src/Shaders/Vertex/${FILE_NAME}" COPYONLY)
endforeach()

#setting the fragment shader files
file(GLOB SHADER_FILES "${Source_Dir}/Shaders/Fragment/*.glsl")
foreach(SHADER_FILE ${SHADER_FILES})
	get_filename_component(FILE_NAME ${SHADER_FILE} NAME)
	configure_file(${SHADER_FILE} "${CMAKE_BINARY_DIR}/src/Shaders/Fragment/${FILE_NAME}" COPYONLY)
endforeach()

# Add GLFW as a subdirectory
add_subdirectory("${Thirdparty_Dir}/GLFW")
add_subdirectory("${Thirdparty_Dir}/GLM")
# Create the executable
add_executable(ModelLoader "${Thirdparty_Dir}/Glad/src/glad.c" ${SRC_FILES} main.cpp)

# Link GLFW library
target_link_libraries(ModelLoader PRIVATE glm glfw ${CMAKE_DL_LIBS})

