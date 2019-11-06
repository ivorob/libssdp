#include <gtest/gtest.h>
#include "ssdp/StringUtils.h"

TEST(StringUtils, trimTest)
{
    std::string emptyString = StringUtils::trim("");
    ASSERT_TRUE(emptyString.empty());
    ASSERT_EQ("test", StringUtils::trim(" test"));
    ASSERT_EQ("test", StringUtils::trim("  test"));
    ASSERT_EQ("test", StringUtils::trim("test "));
    ASSERT_EQ("test", StringUtils::trim("test  "));
    ASSERT_EQ("test", StringUtils::trim("  \ttest  "));
    ASSERT_EQ("", StringUtils::trim("  \t  "));
}
