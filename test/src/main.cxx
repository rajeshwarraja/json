#include <gtest/gtest.h>
#include <version.h>

int main(int argc, char* argv[])
{
    std::cout << "Test: " << gitinfo << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}