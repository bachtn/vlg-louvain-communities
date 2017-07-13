cmake_minimum_required (VERSION 2.6)
project (vlg-louvain-communities)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14 -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -ggdb3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Werror -O3")
set(PROJECT_NAME vlg-louvain-communities)
set(BUILD_FILES cmake_install.cmake CMakeCache.txt CMakeFiles Makefile)
set(DOCUMENTATION_DIR doc)

### Add all *.cc files to SRS
file(GLOB_RECURSE SRC ${CMAKE_SOURCE_DIR}/*.cc)

# Use the message function for debugging
# MESSAGE("debug ${CMAKE_SOURCE_DIR}")

add_executable (${PROJECT_NAME} ${SRC})

### Build Type
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set (CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

find_package(OpenMP)
if (OPENMP_FOUND)
  message("OPENMP FOUND")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


### Documentation
find_package(Doxygen)
if (DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}Doxyfile @ONLY)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)

### Clean
add_custom_target(distclean COMMAND rm -rf ${PROJECT_NAME} ${BUILD_FILES} ${DOCUMENTATION_DIR})
