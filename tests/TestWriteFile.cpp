#include <catch2/catch_all.hpp>

#include "TungstenUtils/ReadFile.hpp"
#include "TungstenUtils/WriteFile.hpp"

#include <vector>

TEST_CASE("WriteFile writes content correctly", "[WriteFile]") {
    struct WriteFileTest {
        std::filesystem::path path;
        std::string content;
    };

    const std::vector<WriteFileTest> writeFileTests = {
        WriteFileTest("helloWorld.txt", "Hello, World! Test"),
        WriteFileTest("WriteFileTest.txt", "WriteFile Test"),
        WriteFileTest("empty.txt", "")
    };

    for (const WriteFileTest& writeFileTest : writeFileTests)
    {
        DYNAMIC_SECTION("Write and Read Back: " << writeFileTest.path)
        {
            CAPTURE(writeFileTest.path);
            CAPTURE(writeFileTest.content);
            REQUIRE(wUtils::WriteFile(writeFileTest.path, writeFileTest.content));
            REQUIRE(std::filesystem::exists(writeFileTest.path));
            std::optional<std::string> result = wUtils::ReadFile(writeFileTest.path);
            REQUIRE(result);
            if (result)
            {
                CAPTURE(fmt::format("Expected: \"{}\", Read: {}", writeFileTest.content, *result));
            }
            else
            {
                CAPTURE(result.has_value());
            }
            REQUIRE(*result == writeFileTest.content);

            std::error_code ec;
            std::filesystem::remove(writeFileTest.path, ec);
            if (ec)
            {
                WARN("Failed to remove test file: " << writeFileTest.path << " - " << ec.message());
            }
        }
    }
}