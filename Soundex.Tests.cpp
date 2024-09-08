#include <gtest/gtest.h>
#include "soundex.h"

TEST(SoundexTest, HandlesEmptyString) {
    std::string result = generateSoundex("");
    ASSERT_EQ(result, "");
}

TEST(SoundexTest, HandlesSingleLetterName) {
    std::string result = generateSoundex("A");
    ASSERT_EQ(result, "A000");
}

TEST(SoundexTest, HandlesNoMappingCharacters) {
    std::string result = generateSoundex("AEIOUHWY");
    ASSERT_EQ(result, "A000");
}

TEST(SoundexTest, HandlesSimpleName) {
    std::string result = generateSoundex("Smith");
    ASSERT_EQ(result, "S530");
}

TEST(SoundexTest, HandlesDuplicateMappedCharacters) {
    std::string result = generateSoundex("Tymczak");
    ASSERT_EQ(result, "T522");
}

TEST(SoundexTest, HandlesNameWithDifferentCases) {
    std::string result = generateSoundex("SMITH");
    ASSERT_EQ(result, "S530");
    result = generateSoundex("sMiTh");
    ASSERT_EQ(result, "S530");
}

TEST(SoundexTest, PadsWithZeros) {
    std::string result = generateSoundex("Ray");
    ASSERT_EQ(result, "R000");
}

TEST(SoundexTest, TrimsToFourCharacters) {
    std::string result = generateSoundex("Jackson");
    ASSERT_EQ(result, "J250");
}

TEST(SoundexTest, IgnoresCaseInSoundexCodeMapping) {
    std::string result = generateSoundex("O'Brien");
    ASSERT_EQ(result, "O165");
}

