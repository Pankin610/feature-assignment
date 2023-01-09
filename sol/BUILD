package(default_visibility = ["//visibility:public"])

cc_library(
    name = "solution",
    hdrs = ["solution.h"],
    srcs = ["solution.cpp"],
    deps = [
        "//state:state"
    ]
)

cc_library(
    name = "solver_interface",
    hdrs = ["solver_interface.h"],
    deps = [
        "//state:problem_data",
        ":solution"
    ]
)

cc_library(
    name = "action_producer_interface",
    hdrs = ["action_producer_interface.h"],
    deps = [
        "//state:state"
    ]
)

cc_library(
    name = "producer_based_solver",
    hdrs = ["producer_based_solver.h"],
    srcs = ["producer_based_solver.cpp"],
    deps = [
        ":solver_interface",
        ":action_producer_interface",
        ":solution",
        "//state:state"
    ]
)

cc_library(
    name = "first_take_action_producer",
    hdrs = ["first_take_action_producer.h"],
    srcs = ["first_take_action_producer.cpp"],
    deps = [
        ":action_producer_interface",
        "//state:state"
    ]
)

cc_library(
    name = "ordered_feature_implementation_producer",
    hdrs = ["ordered_feature_implementation_producer.h"],
    srcs = ["ordered_feature_implementation_producer.cpp"],
    deps = [
        ":action_producer_interface",
        "//state:state"
    ]
)