#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness_c.h"

/** For each C test group */
TEST_GROUP_C_WRAPPER(binary_tree)
{
    TEST_GROUP_C_SETUP_WRAPPER(binary_tree); /** optional */
    TEST_GROUP_C_TEARDOWN_WRAPPER(binary_tree); /** optional */
};

TEST_C_WRAPPER(binary_tree, tests);

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
