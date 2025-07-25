#include <catch2/catch_all.hpp>

#include "TungstenUtils/FindAndReplace.hpp"

TEST_CASE("FindAndReplaceAll correctly replaces all occurrences", "[FindAndReplace]")
{
    SECTION("Hello, World Find and Replace")
    {
        std::string helloStr = "hello @NAME@";
        wUtils::FindAndReplaceAll(helloStr, "@NAME@", "World");
        REQUIRE(helloStr == "hello World");
        wUtils::FindAndReplaceAll(helloStr, "hello", "Hello,");
        REQUIRE(helloStr == "Hello, World");
    }

    SECTION("Multiple Replacements")
    {
        std::string str0 = "asdfijklasdftijklqwerty";
        wUtils::FindAndReplaceAll(str0, "asdf", "WASD");
        REQUIRE(str0 == "WASDijklWASDtijklqwerty");
        wUtils::FindAndReplaceAll(str0, "ijk", "?");
        REQUIRE(str0 == "WASD?lWASDt?lqwerty");
    }

    SECTION("Random Text")
    {
        std::string str1 = ":LFSDHFGoh;oiFH:SO\nIUGHDLKH\\eIUOHGKLJSLDIOERTSD\nIOF932489328-98ioghsdpo";
        wUtils::FindAndReplaceAll(str1, "\\e", "\n893458902089436508962dkjlghvsd3098645");
        REQUIRE(str1 == ":LFSDHFGoh;oiFH:SO\nIUGHDLKH\n893458902089436508962dkjlghvsd3098645IUOHGKLJSLDIOERTSD\nIOF932489328-98ioghsdpo");
        wUtils::FindAndReplaceAll(str1, "LFSDH", "5IUOHGKLJSLDIOERTSD\nIOF932489328-98i");
        REQUIRE(str1 == ":5IUOHGKLJSLDIOERTSD\nIOF932489328-98iFGoh;oiFH:SO\nIUGHDLKH\n893458902089436508962dkjlghvsd3098645IUOHGKLJSLDIOERTSD\nIOF932489328-98ioghsdpo");
        wUtils::FindAndReplaceAll(str1, "L2FSDH", "asdf");
        REQUIRE(str1 == ":5IUOHGKLJSLDIOERTSD\nIOF932489328-98iFGoh;oiFH:SO\nIUGHDLKH\n893458902089436508962dkjlghvsd3098645IUOHGKLJSLDIOERTSD\nIOF932489328-98ioghsdpo");
        wUtils::FindAndReplaceAll(str1, "5IUOHGKLJSLDIOERTSD\nIOF932489328-98i", ":");
        REQUIRE(str1 == "::FGoh;oiFH:SO\nIUGHDLKH\n893458902089436508962dkjlghvsd309864:oghsdpo");
        wUtils::FindAndReplaceAll(str1, ";", ":");
        REQUIRE(str1 == "::FGoh:oiFH:SO\nIUGHDLKH\n893458902089436508962dkjlghvsd309864:oghsdpo");
        wUtils::FindAndReplaceAll(str1, ":", "");
        REQUIRE(str1 == "FGohoiFHSO\nIUGHDLKH\n893458902089436508962dkjlghvsd309864oghsdpo");
    }

}

TEST_CASE("FindAndReplaceAllCopy correctly replaces all occurrences", "[FindAndReplace]")
{
    SECTION("Hello, World Find and Replace")
    {
        REQUIRE(wUtils::FindAndReplaceAllCopy("hello @NAME@", "@NAME@", "World") == "hello World");
        REQUIRE(wUtils::FindAndReplaceAllCopy("hello @NAME@", "hello ", "@BEGINING@ ") == "@BEGINING@ @NAME@");
    }

    SECTION("Multiple Replacements")
    {
        REQUIRE(wUtils::FindAndReplaceAllCopy("asdfaffadfdfaffffsafdfasff", "ff", "a") == "asdfaaadfdfaaasafdfasa");
        REQUIRE(wUtils::FindAndReplaceAllCopy("The quick brown fox jumped over the lazy dog!", " ", "_") == "The_quick_brown_fox_jumped_over_the_lazy_dog!");
    }

    SECTION("Random Text")
    {
        REQUIRE(wUtils::FindAndReplaceAllCopy("asdfaffadfdfaffffsafdfasff", "ff", "a") == "asdfaaadfdfaaasafdfasa");
        REQUIRE(wUtils::FindAndReplaceAllCopy("", " ", "_") == "");
    }

    SECTION("EDGE CASES")
    {
        REQUIRE(wUtils::FindAndReplaceAllCopy("abcabc", "abc", "abc") == "abcabc");
        REQUIRE(wUtils::FindAndReplaceAllCopy("abcabc", "xyz", "123") == "abcabc");
        REQUIRE(wUtils::FindAndReplaceAllCopy("aaaa", "", "x") == "aaaa");
    }
}