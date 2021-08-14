#include <gtest/gtest.h>
#include <json>
#include <sstream>

class GivenNull : public testing::Test { };

TEST_F(GivenNull, WhenCreating) {
    json::data json;
    ASSERT_EQ(nullptr, json) << "Json data is not null";
}

TEST_F(GivenNull, WhenGenerating) {
    json::data json;
    std::stringstream sstr;
    sstr << json;
    ASSERT_STREQ("null", sstr.str().c_str());
}

TEST_F(GivenNull, WhenParsing) {
    std::stringstream sstr;
    json::data json;
    sstr << json;
    sstr.seekg(0);
    json::data jsonParsed;
    sstr >> jsonParsed;
    ASSERT_EQ(json, jsonParsed);
}

class GivenBoolean : public testing::TestWithParam<bool> { };

INSTANTIATE_TEST_SUITE_P(When, GivenBoolean, testing::Values(true, false));

TEST_P(GivenBoolean, WhenCreating) {
    json::data json(GetParam());
    ASSERT_EQ(GetParam(), (bool)json) << "Json data is not "  << GetParam();
}

TEST_P(GivenBoolean, WhenGenerating) {
    const auto expected = GetParam();
    json::data json(expected);
    std::stringstream sstr;
    sstr << json;
    ASSERT_STREQ(expected? json::grammar::_valueTrue : json::grammar::_valueFalse, sstr.str().c_str());
}

TEST_P(GivenBoolean, WhenParsing) {
    const auto expected = GetParam();
    std::stringstream sstr;
    json::data json(expected);
    sstr << json;
    sstr.seekg(0);
    json::data jsonParsed;
    sstr >> jsonParsed;
    ASSERT_EQ(json, jsonParsed);
}

class GivenInteger : public testing::TestWithParam<int> { };

INSTANTIATE_TEST_SUITE_P(When, GivenInteger, testing::Values(
    +100,
    0,
    -100
));

TEST_P(GivenInteger, WhenCreating) {
    json::data json(GetParam());
    ASSERT_EQ(GetParam(), (int)json) << "Json data is not "  << GetParam();
}

TEST_P(GivenInteger, WhenGenerating) {
    const auto expected = GetParam();
    json::data json(expected);
    std::stringstream sstr;
    sstr << json;
    ASSERT_STREQ(std::to_string(expected).c_str(), sstr.str().c_str());
}

class GivenDouble : public testing::TestWithParam<double> { };

INSTANTIATE_TEST_SUITE_P(When, GivenDouble, testing::Values(
    +1e-2
    +0.100,
    0.0,
    -0.100,
    -1e-2
));

TEST_P(GivenDouble, WhenCreating) {
    json::data json(GetParam());
    ASSERT_EQ(GetParam(), (double)json) << "Json data is not "  << GetParam();
}

TEST_P(GivenDouble, WhenGenerating) {
    const auto expected = GetParam();
    json::data json(expected);
    std::stringstream sstr;
    sstr << json;
    ASSERT_STREQ(std::to_string(expected).c_str(), sstr.str().c_str());
}

class GivenString : public testing::TestWithParam<const char*> { };

INSTANTIATE_TEST_SUITE_P(GivenString, GivenString, testing::Values(
    "Raja", "\"", "\" ", " ", "\\", "\b", "\n", "\t", "\r", "\f"
));

TEST_P(GivenString, WhenCreating) {
    json::data json(GetParam());
    ASSERT_STREQ(GetParam(), (const char*)json) << "Json data is not "  << GetParam();
}

TEST_P(GivenString, WhenGenerating) {
    const auto expected = GetParam();
    json::data json(expected);
    std::stringstream sstr;
    sstr << json;
    ASSERT_STREQ((std::string("\"") + expected + "\"").c_str(), sstr.str().c_str());
}