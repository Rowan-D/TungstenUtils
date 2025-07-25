cmake_minimum_required(VERSION 3.14)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" TUNGSTENUTILS_VERSION_RAW)
string(STRIP "${TUNGSTENUTILS_VERSION_RAW}" TUNGSTENUTILS_VERSION)
string(REGEX MATCH "^([0-9]+)\\.([0-9]+)\\.([0-9]+)" _ "${TUNGSTENUTILS_VERSION}")
set(TUNGSTENUTILS_VERSION_MAJOR ${CMAKE_MATCH_1})
set(TUNGSTENUTILS_VERSION_MINOR ${CMAKE_MATCH_2})
set(TUNGSTENUTILS_VERSION_PATCH ${CMAKE_MATCH_3})

project(TungstenUtils VERSION ${TUNGSTENUTILS_VERSION} LANGUAGES CXX)


set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Version.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/TungstenUtils/Version.hpp
  @ONLY
)

# Add fmt
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/fmt)

add_library(TungstenUtils STATIC
    include/TungstenUtils/macros/ansi.hpp
    include/TungstenUtils/macros/noOp.hpp
    include/TungstenUtils/macros/debugBreak.hpp
    include/TungstenUtils/macros/assert.hpp
    include/TungstenUtils/macros/nameof.hpp
    include/TungstenUtils/TungstenUtils.hpp
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
include(GNUInstallDirs)

install(TARGETS TungstenUtils
        EXPORT TungstenUtilsTargets
        EXPORT_NAME TungstenUtils
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
    "${CMAKE_CURRENT_SOURCE_DIR}/TungstenUtilsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/TungstenUtilsConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TungstenUtils
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/TungstenUtilsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/TungstenUtilsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TungstenUtils
)

# Uninstall logic
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)