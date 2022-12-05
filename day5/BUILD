cc_binary (
       name = "main",
       srcs = [":main/main.cpp"],
       deps = ["CrateStack"],
)

cc_library (
       name = "CrateStack",
       hdrs = [":CrateStack/CrateStack.hpp"],
       srcs = [":CrateStack/CrateStack.hpp"],
       strip_include_prefix = "CrateStack/",
)
