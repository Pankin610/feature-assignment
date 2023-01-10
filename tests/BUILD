cc_test(
    name = "feature_maintainer_test",
    srcs = ["feature_maintainer_test.cpp"],
    deps = [
        "//state:feature_maintainer",
        "@gtest//:gtest",
        "@gtest//:gtest_main"
    ]
)

cc_test(
    name = "binary_maintainer_test",
    srcs = ["binary_maintainer_test.cpp"],
    deps = [
        "//state:binary_maintainer",
        "@gtest//:gtest",
        "@gtest//:gtest_main"
    ]
)

cc_test(
    name = "state_test",
    srcs = ["state_test.cpp"],
    deps = [
        "//state:state",
        "@gtest//:gtest",
        "@gtest//:gtest_main"
    ]
)

cc_test(
    name = "producer_based_solver_test",
    srcs = ["producer_based_solver_test.cpp"],
    data = ["//hashcode_tests:a_example.in.txt"],
    deps = [
        "//sol:first_take_action_producer",
        "//sol:producer_based_solver",
        "@gtest//:gtest",
        "@gtest//:gtest_main"
    ]
)