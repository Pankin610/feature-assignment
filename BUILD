package(default_visibility = ["//visibility:public"])

cc_library(
    name = "types",
    hdrs = ["types.h"]
)

cc_library(
    name = "binary",
    hdrs = ["binary.h"],
    deps = [
        ":types"
    ]
)

cc_library(
    name = "feature",
    hdrs = ["feature.h"],
    deps = [
        ":types"
    ]
)

cc_binary(
    name = "run_solution",
    srcs = ["run_solution.cpp"],
    deps = [
        ":binary",
        ":feature",
        ":types"
    ]
)

cc_library(
    name = "event_queue",
    hdrs = ["event_queue.h"],
)

cc_library(
    name = "id_maintainer",
    srcs = ["id_maintainer.cpp"],
    hdrs = ["id_maintainer.h"],
    deps = [
        ":types",
        ":event_queue",
    ]
)

cc_library(
    name = "feature_maintainer",
    hdrs = ["feature_maintainer.h"],
    srcs = ["feature_maintainer.cpp"],
    deps = [
        ":binary",
        ":feature",
        ":id_maintainer",
        ":types"
    ]
)

cc_library(
    name = "binary_maintainer",
    hdrs = ["binary_maintainer.h"],
    deps = [
        ":binary",
        ":id_maintainer",
        ":types"
    ]
)

cc_test(
    name = "feature_maintainer_test",
    size = "small",
    srcs = ["feature_maintainer_test.cpp"],
    deps = [
        ":feature_maintainer",
        "@gtest//:gtest",
        "@gtest//:gtest_main"
    ],
)

cc_test(
    name = "binary_maintainer_test",
    size = "small",
    srcs = ["binary_maintainer_test.cpp"],
    deps = [
        ":binary_maintainer",
        "@gtest//:gtest",
        "@gtest//:gtest_main"
    ],
)

cc_library(
    name = "state",
    srcs = ["state.cpp", "action.cpp"],
    hdrs = ["state.h", "action.h"],
    deps = [
        ":binary_maintainer",
        ":feature_maintainer",
        ":id_maintainer",
        ":types",
        ":event_queue",
    ]
)

cc_test(
    name = "state_test",
    size = "small",
    srcs = ["state_test.cpp"],
    deps = [
        ":state",
        "@gtest//:gtest",
        "@gtest//:gtest_main"
    ],
)