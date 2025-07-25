#include <catch2/catch_all.hpp>

#include "TungstenUtils/ReadFile.hpp"

TEST_CASE("ReadFile reads known files correctly", "[ReadFile]")
{
    SECTION("Reads hello.txt")
    {
        const std::filesystem::path helloTestPath = "res/hello.txt";
        CAPTURE(helloTestPath);
        REQUIRE(std::filesystem::exists(helloTestPath));
        const char* expectedHelloStr = "Hello, World!";
        std::optional<std::string> helloString = wUtils::ReadFile(helloTestPath);
        REQUIRE(helloString);
        if (helloString)
        {
            CAPTURE(fmt::format("Expected: \"{}\", Read: {}", expectedHelloStr, *helloString));
        }
        else
        {
            CAPTURE(helloString.has_value());
        }
        REQUIRE(*helloString == expectedHelloStr);
    }

    SECTION("Reads empty.txt")
    {
        const std::filesystem::path emptyTestPath = "res/empty.txt";
        CAPTURE(emptyTestPath);
        REQUIRE(std::filesystem::exists(emptyTestPath));
        std::optional<std::string> emptyString = wUtils::ReadFile(emptyTestPath);
        REQUIRE(emptyString);
        if (emptyString)
        {
            CAPTURE(fmt::format("Expected and empty string, Read: {}", *emptyString));
        }
        else
        {
            CAPTURE(emptyString.has_value());
        }
        REQUIRE(emptyString->empty());
    }

    SECTION("Reads party.txt")
    {
        const std::filesystem::path partyTestPath = "res/party.txt";
        CAPTURE(partyTestPath);
        REQUIRE(std::filesystem::exists(partyTestPath));
        const char* expectedPartyStr = R"(####################################################################
#                                                                  #
# The Party told you to reject the evidence of your eyes and ears. #
# It was their final, most essential command.                      #
#                                                                  #
####################################################################)";
        std::optional<std::string> partyString = wUtils::ReadFile(partyTestPath);
        REQUIRE(partyString);
        if (partyString)
        {
            CAPTURE(fmt::format("Expected: \"{}\", Read: {}", expectedPartyStr, *partyString));
        }
        else
        {
            CAPTURE(partyString.has_value());
        }
        REQUIRE(*partyString == expectedPartyStr);
    }
}

TEST_CASE("ReadFile handles missing file", "[ReadFile]") {
    const std::filesystem::path nonexistentFilePath = "res/nonexistentFile.txt";
    CAPTURE(nonexistentFilePath);
    REQUIRE_FALSE(std::filesystem::exists(nonexistentFilePath));
    std::optional<std::string> result = wUtils::ReadFile(nonexistentFilePath);
    if (result)
    {
        CAPTURE(fmt::format("Expected a false output, Read: {}", *result));
    }
    else
    {
        CAPTURE(result.has_value());
    }
    REQUIRE_FALSE(result);
}