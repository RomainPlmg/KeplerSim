# CMakeList.txt : CMake project for KeplerSim, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (KeplerSim "KeplerSim.cpp" "KeplerSim.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET KeplerSim PROPERTY CXX_STANDARD 20)
endif()

# Adding all vendor libraries
add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glm)
