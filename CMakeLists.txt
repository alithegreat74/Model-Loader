cmake_minimum_required(VERSION 3.5.0)

set (CMAKE_CXX_STANDARD 17)

project(ModelLoader)
set(Thirdparty_Dir "${CMAKE_SOURCE_DIR}/Thirdparty")



#Getting the source files
set(Source_Dir "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SRC_FILES "${Source_Dir}/*.cpp")
file(GLOB_RECURSE IMGUI_FILE "${Thirdparty_Dir}/ImGui/*.cpp")
list(APPEND SRC_FILES ${IMGUI_FILE})
include_directories(
	"${Thirdparty_Dir}/Glad/include"
	"${Thirdparty_Dir}/ImGui"
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

#setting all the model files
file(GLOB SHADER_FILES "${Source_Dir}/Models/soldier/*.*")
foreach(SHADER_FILE ${SHADER_FILES})
	get_filename_component(FILE_NAME ${SHADER_FILE} NAME)
	configure_file(${SHADER_FILE} "${CMAKE_BINARY_DIR}/src/Models/soldier/${FILE_NAME}" COPYONLY)
endforeach()

# Add Thirdparties as a subdirectory
add_subdirectory("${Thirdparty_Dir}/GLFW")
add_subdirectory("${Thirdparty_Dir}/GLM")
add_subdirectory("${Thirdparty_Dir}/Assimp")

# Create the executable
add_executable(ModelLoader "${Thirdparty_Dir}/Glad/src/glad.c" ${SRC_FILES} main.cpp)

# Link thirdparty libraries
target_link_libraries(ModelLoader PRIVATE assimp glm glfw ${CMAKE_DL_LIBS})

