cmake_minimum_required(VERSION 3.14)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" TUNGSTENUTILS_VERSION_RAW)
string(STRIP "${TUNGSTENUTILS_VERSION_RAW}" TUNGSTENUTILS_VERSION)
string(REPLACE "." ";" TUNGSTENUTILS_VERSION_LIST ${TUNGSTENUTILS_VERSION})

list(LENGTH TUNGSTENUTILS_VERSION_LIST _ver_len)
if(NOT _ver_len EQUAL 3)
    message(FATAL_ERROR "VERSION file contains unknown format; expected: MAJOR.MINOR.PATCH")
endif()

list(GET TUNGSTENUTILS_VERSION_LIST 0 TUNGSTENUTILS_VERSION_MAJOR)
list(GET TUNGSTENUTILS_VERSION_LIST 1 TUNGSTENUTILS_VERSION_MINOR)
list(GET TUNGSTENUTILS_VERSION_LIST 2 TUNGSTENUTILS_VERSION_PATCH)

project(TungstenUtils VERSION ${TUNGSTENUTILS_VERSION} LANGUAGES CXX)

message(STATUS "TungstenUtils version: ${PROJECT_VERSION}")

option(TUNGSTENUTILS_INSTALL_LIBRARY "Install library, headers, and CMake config" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Version.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/TungstenUtils/Version.hpp
    @ONLY
)

# Add fmt
if(TUNGSTENUTILS_INSTALL_LIBRARY)
    set(FMT_INSTALL ON)
else()
    set(FMT_INSTALL OFF)
endif()
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/fmt)

add_library(TungstenUtils STATIC
    include/TungstenUtils/macros/ansi.hpp
    include/TungstenUtils/macros/noOp.hpp
    include/TungstenUtils/macros/debugBreak.hpp
    include/TungstenUtils/macros/assert.hpp
    include/TungstenUtils/macros/nameof.hpp
    include/TungstenUtils/macros.hpp
    include/TungstenUtils/TungstenUtils.hpp
    include/TungstenUtils/Filesystem.hpp
    include/TungstenUtils/wIndex.hpp
    include/TungstenUtils/DebugGetTypeName.hpp
    include/TungstenUtils/TungstenLogger.hpp
    include/TungstenUtils/SlotList.hpp
    include/TungstenUtils/ReadFile.hpp
    include/TungstenUtils/WriteFile.hpp
    include/TungstenUtils/FindAndReplace.hpp
    src/wUtilsPCH.cpp
    src/TungstenLogger.cpp
    src/ReadFile.cpp
    src/WriteFile.cpp
    src/FindAndReplace.cpp
)

target_include_directories(TungstenUtils PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(TungstenUtils PUBLIC cxx_std_20)
target_precompile_headers(TungstenUtils PRIVATE src/wUtilsPCH.hpp)

target_link_libraries(TungstenUtils PUBLIC fmt::fmt)

set_target_properties(TungstenUtils PROPERTIES
    VERSION ${PROJECT_VERSION}
)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# Enable tests only if requested
include(CTest)  # Sets BUILD_TESTING option
if (BUILD_TESTING)
    add_subdirectory(tests)
endif()

# Installation logic
if(TUNGSTENUTILS_INSTALL_LIBRARY)
    include(GNUInstallDirs)

    install(TARGETS TungstenUtils
            EXPORT TungstenUtilsTargets
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/include/TungstenUtils/Version.hpp"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/TungstenUtils
    )

    install(EXPORT TungstenUtilsTargets
            FILE TungstenUtilsTargets.cmake
            NAMESPACE Tungsten::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TungstenUtils)

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/TungstenUtilsConfigVersion.cmake"
        VERSION ${TUNGSTENUTILS_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/CMake/TungstenUtilsConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/TungstenUtilsConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TungstenUtils
    )

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/TungstenUtilsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/TungstenUtilsConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TungstenUtils
    )
endif()

# Uninstall logic. Only defined if this is the top-level project.
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/CMake/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY
    )

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
    )
endif()