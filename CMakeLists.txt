cmake_minimum_required(VERSION 3.10)
project(InertialScaleProject)

set(CMAKE_CXX_STANDARD 17)

# Set MATLAB Root Directory (Adjust for your installed path)
set(MATLAB_RUNTIME_DIR "/usr/local/MATLAB/MATLAB_Runtime/R2024b")  # Replace v99 with your MCR version

# Include MATLAB Runtime headers
include_directories(${MATLAB_RUNTIME_DIR}/extern/include)
include_directories(${CMAKE_SOURCE_DIR}/c_project)  # Include the path to the generated files

# Link MATLAB Runtime Libraries
link_directories(${MATLAB_RUNTIME_DIR}/runtime/glnxa64)

# Add the shared object path
set(LIBRARY_PATH "${CMAKE_SOURCE_DIR}/c_project")
link_directories(${LIBRARY_PATH})

# Add executable
add_executable(my_program main.cpp)

# Link the generated shared library and MATLAB Runtime libraries
target_link_libraries(my_program PRIVATE InertialScale)


target_link_libraries(my_program PRIVATE 
   # ${MATLAB_RUNTIME_DIR}/runtime/glnxa64/libmcrrt.so
    ${MATLAB_RUNTIME_DIR}/runtime/glnxa64/libmwmclmcrrt.so  
)