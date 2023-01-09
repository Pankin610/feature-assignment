package(default_visibility = ["//visibility:public"])
cc_library(
    name = "event_queue",
    hdrs = ["event_queue.h"],
)

cc_library(
    name = "id_maintainer",
    hdrs = ["id_maintainer.h"],
    srcs = ["id_maintainer.cpp"],
    deps = [
        "//core:types",
        ":event_queue"
    ]
)

cc_library(
    name = "binary_maintainer",
    hdrs = ["binary_maintainer.h"],
    deps = [
        ":id_maintainer",
        "//core:binary"
    ]
)

cc_library(
    name = "feature_maintainer",
    hdrs = ["feature_maintainer.h"],
    srcs = ["feature_maintainer.cpp"],
    deps = [
        ":id_maintainer",
        "//core:binary",
        "//core:feature"
    ]
)

cc_library(
    name = "problem_data",
    hdrs = ["problem_data.h"],
    srcs = ["problem_data.cpp"],
    deps = [
        ":id_maintainer",
        ":feature_maintainer",
        ":binary_maintainer",
        "//core:types"
    ]
)

cc_library(
    name = "state",
    hdrs = ["state.h", "action.h"],
    srcs = ["state.cpp", "action.cpp"],
    deps = [
        "//core:binary",
        "//core:feature",
        "//core:types",
        ":binary_maintainer",
        ":feature_maintainer",
        ":problem_data",
        ":event_queue"
    ]
)