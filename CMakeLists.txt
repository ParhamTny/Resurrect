cmake_minimum_required(VERSION 3.29.5)

project(Resurrect VERSION 0.1 DESCRIPTION "A simple and cross-platform game engine written in C++ using the Vulkan API for
	beginners to learn the Vulkan API" LANGUAGES CXX)

find_package(Vulkan REQUIRED)

if(Vulkan_FOUND)
	message(STATUS "Vulkan found")
else()
	message(FATAL_ERROR "Vulkan not found, download the Vulkan SDK before running this application")
endif()