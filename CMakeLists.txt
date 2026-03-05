cmake_minimum_required(VERSION 3.10)
project(termpod LANGUAGES CXX C)

set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "Single-header C++ library for CRC-32/MPEG-2 checksummed POD{1,2,3,4,5,6}/EPD archive file formats used in Terminal Reality game engines")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(GNUInstallDirs)
include(FindPkgConfig)

if( NOT CMAKE_BUILD_TYPE )
        set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE )
endif()

set( CMAKE_C_STANDARD 23 )
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_CXX_STANDARD 26)
set( CMAKE_CXX_STANDARD_REQUIRED ON )

if( CMAKE_BUILD_TYPE EQUAL Debug )
	add_compile_options(-g)
endif()
if( CMAKE_GENERATOR_PLATFORM STREQUAL "x64" OR CMAKE_GENERATOR_PLATFORM STREQUAL "x86_64" OR CMAKE_GENERATOR_PLATFORM STREQUAL "AMD64" )
	add_compile_options(-mfpmath=sse)
endif()

if( NOT CMAKE_BUILD_OPTLEVEL )
	set( CMAKE_BUILD_OPTLEVEL 3 CACHE STRING "Choose the optimization level of the build." FORCE )
endif()

add_compile_options(-march=native)
add_compile_options(-O${OPTIMIZATION})
add_compile_options(-fopenmp-simd)
add_compile_options(-ftree-vectorize)
add_compile_options(-Wno-gnu-alignof-expression)
add_compile_options(-D_FILE_OFFSET_BITS=64)
add_compile_options(-fdata-sections)
add_compile_options(-fpermissive)
add_compile_options(-ffunction-sections)
add_compile_options(-Wno-array-bounds)
add_compile_options(-Wno-unused-parameter)
add_compile_options(-Wno-pedantic)
add_compile_options(-Wno-narrowing)
add_link_options(-Wl,--gc-sections)
add_link_options(-Wl,--print-gc-sections)
add_link_options(-Wl,-s)

set(SOURCE_FILES
)

set(INCLUDE_FILES
	#external/libzippp/src/libzippp.h
	external/crcle/include/crcle/crcle.hpp
	include/termpod/pod.hpp
)

set(EXAMPLE_SOURCE_FILES
	examples/podorgana/podorgana.cpp
)

#add_subdirectory(external/libzippp)

# termpod library
include_directories(${PROJECT_NAME} PUBLIC 
                    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/external/crcle/include>
		    #                    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/external/libzippp/src>
                    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

set(install_prefix "${CMAKE_INSTALL_PREFIX}")
set(install_libdir "${CMAKE_INSTALL_LIBDIR}")
set(install_includedir "${CMAKE_INSTALL_INCLUDEDIR}")
set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(project_config "${PROJECT_NAME}Config.cmake")
set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * TARGETS_EXPORT_NAME
#   * PROJECT_NAME
configure_package_config_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in"
	"${project_config}"
	INSTALL_DESTINATION "${config_install_dir}"
)

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc @ONLY)

set(ENV{PKG_CONFIG_PATH} "${PROJECT_BINARY_DIR}:$ENV{PKG_CONFIG_PATH}")

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindTermPOD.cmake DESTINATION
	${CMAKE_INSTALL_LIBDIR}/cmake/TermPOD)

install(FILES ${INCLUDE_FILES} DESTINATION
	${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/)

install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig/)

add_executable(podorgana examples/podorgana/podorgana.cpp)
install(TARGETS podorgana DESTINATION ${CMAKE_INSTALL_BINDIR}) 
