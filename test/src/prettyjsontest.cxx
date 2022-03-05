#include <gtest/gtest.h>
#include <json>
#include <sstream>

namespace Json::Test
{
	class WhenPrettyStreamingOut : public testing::Test { };

	TEST_F(WhenPrettyStreamingOut, GivenArray)
	{
        json::data json;
        json[0] = 1;
        json[1] = 2;
        json[2] = 3;
        json[3] = "text";
        std::stringstream sstr;
        sstr << json::pretty << json;
        ASSERT_STREQ("[\n  1,\n  2,\n  3,\n  \"text\"\n]", sstr.str().c_str());
	}

    TEST_F(WhenPrettyStreamingOut, GivenObject)
    {
        json::data json;
        auto& employee = json["employee"];
        employee["name"] = "Raja";
        std::stringstream sstr;
        sstr << json::pretty << json;
        ASSERT_STREQ("{\n  \"employee\": {\n    \"name\": \"Raja\"\n  }\n}", sstr.str().c_str());
    }
}