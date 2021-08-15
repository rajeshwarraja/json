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

TEST_P(GivenInteger, WhenParsing) {
    const auto expected = GetParam();
    std::stringstream sstr;
    json::data json(expected);
    sstr << json;
    json::data jsonParsed;
    sstr >> jsonParsed;
    ASSERT_EQ(json, jsonParsed);
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

TEST_P(GivenDouble, WhenParsing) {
    const auto expected = GetParam();
    std::stringstream sstr;
    json::data json(expected);
    sstr << json;
    json::data jsonParsed;
    sstr >> jsonParsed;
    ASSERT_EQ(json, jsonParsed);
}

class GivenString : public testing::TestWithParam<const char*> { };

INSTANTIATE_TEST_SUITE_P(GivenString, GivenString, testing::Values(
    "\\", "\b", "\n", "\t", "\r", "\f", "\" - double quotes", "string", ""
));

TEST_P(GivenString, WhenParsing) {
    const auto expected = GetParam();
    std::stringstream sstr;
    json::data json(expected);
    sstr << json;
    json::data jsonParsed;
    sstr >> jsonParsed;
    ASSERT_EQ(json, jsonParsed);
}

class GivenArray : public testing::Test { };

TEST_F(GivenArray, WhenGenerating) {
    std::stringstream sstr;
    json::data json;
    json[0] = "text";
    json[1] = 1.01;
    json[2] = true;
    json[3] = nullptr;
    sstr << json;
    ASSERT_STREQ("[\"text\",1.010000,true,null]", sstr.str().c_str());
}

TEST_F(GivenArray, WhenGeneratingMixed) {
    std::stringstream sstr;
    json::data json;
    json[0] = 1;
    json[1] = 2;
    json[2] = 3;
    json[3] = "text";
    sstr << json;
    ASSERT_STREQ("[1,2,3,\"text\"]", sstr.str().c_str());
}

class GivenObject : public testing::Test { };

TEST_F(GivenObject, WhenGenerating) {
    json::data json;
    auto& employee = json["employee"];
    employee["name"] = "Raja";
    std::stringstream sstr;
    sstr << json;
    ASSERT_STREQ("{\"employee\":{\"name\":\"Raja\"}}", sstr.str().c_str());
}

TEST_F(GivenObject, WhenParsing) {
    json::data json;
    auto& employee = json["employee"];
    employee["name"] = "Raja";
    std::stringstream sstr;
    sstr << json;
    json::data jsonParsed;
    sstr >> jsonParsed;
    ASSERT_EQ(json, jsonParsed);
}