cmake_minimum_required(VERSION 3.29.5)

file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp")
add_executable(Resurrect ${sources})

target_include_directories(Resurrect PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Include"
	"${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Glfw/include" "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Glm")

target_link_libraries(Resurrect PRIVATE glfw Vulkan::Vulkan)