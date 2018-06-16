cmake_minimum_required(VERSION 3.10)
project(I2CPP)

set(CMAKE_CXX_STANDARD 11)
## Install libraries (if any) to <install_directory>/bin
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()


include_directories(i2cpp PUBLIC ${PROJECT_SOURCE_DIR}/include)
include_directories(i2cpp PRIVATE ${PROJECT_SOURCE_DIR}/src)
if(NOT LINUX)
    include_directories(i2cpp PRIVATE ${PROJECT_SOURCE_DIR}/hack_include)
endif()


file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)


add_library(i2cpp ${SOURCES})

install(
	TARGETS i2cpp
	DESTINATION lib
)
install(
	DIRECTORY include/
	DESTINATION include
)

find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create the HTML based documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    message("Building Documentation...")
	if(NOT DOXYGEN_FOUND)
		message(FATAL_ERROR "Doxygen is needed to build the documentation.")
	endif()

	set(doxyfile_in ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}.doxygen)
	set(doxyfile ${PROJECT_SOURCE_DIR}/doxyfile)

	configure_file(${doxyfile_in} ${doxyfile} @ONLY)

	message("Doxygen build started.")

	add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doc
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

	# install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION     share/doc)
else()
    message("Not building documentation.")
endif()