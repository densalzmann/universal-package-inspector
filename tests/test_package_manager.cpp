#include "gtest/gtest.h"
#include "package_manager/dpkg_adapter.hpp"

TEST(PackageManagerTest, AptAdapterTest) {
    DpkgAdapter dpkg;
    auto packages = dpkg.getInstalledPackages();
    ASSERT_GT(packages.size(), 0);
}