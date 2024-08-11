#include "gtest/gtest.h"
#include "package_manager/apt_adapter.hpp"

TEST(PackageManagerTest, AptAdapterTest) {
    AptAdapter apt;
    auto packages = apt.getInstalledPackages();
    ASSERT_GT(packages.size(), 0);
}