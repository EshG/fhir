licenses(["notice"])

package(default_visibility = ["//visibility:public"],)

cc_library(
    name = "status",
    hdrs = ["status.h"],
    strip_include_prefix = "//cc/",
    deps = [
        "@com_google_absl//absl/status",
    ],
)

cc_library(
    name = "statusor",
    srcs = ["statusor.cc"],
    hdrs = [
        "statusor.h",
        "statusor_internals.h",
    ],
    strip_include_prefix = "//cc/",
    deps = [
        ":status",
        "@com_google_absl//absl/status",
        "@org_tensorflow//tensorflow/core:lib",
    ],
)

cc_test(
    name = "statusor_test",
    size = "small",
    srcs = ["statusor_test.cc"],
    deps = [
        ":statusor",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status",
        "@com_google_googletest//:gtest_main",
    ],
)
