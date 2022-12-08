cc_binary (
       name="main",
       srcs=[":main/main.cpp"],
       deps = ["Node"],
)

cc_library (
       name = "Node",
       hdrs = [":Node/Node.hpp"],
       srcs = [":Node/Node.hpp"],
       strip_include_prefix = "Node/",
)