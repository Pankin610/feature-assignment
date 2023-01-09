cc_binary(
    name = "run_solution",
    srcs = ["run_solution.cpp"],
    deps = [
        "//state:state",
        "//sol:producer_based_solver",
        "//sol:ordered_feature_implementation_producer"
    ]
)

cc_binary(
    name = "get_test_info",
    srcs = ["get_test_info.cpp"],
    deps = [
        "//state:problem_data",
    ]
)