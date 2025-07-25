# Add test executable
add_executable(TungstenUtilsTests
    TestSlotList.cpp
    TestReadFile.cpp
    TestWriteFile.cpp
    TestFindAndReplace.cpp
)

target_link_libraries(TungstenUtilsTests PRIVATE
    TungstenUtils
    Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(TungstenUtilsTests)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})