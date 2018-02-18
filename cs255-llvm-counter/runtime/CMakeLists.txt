add_library(InstCounting_rt STATIC
    # List your source files here.
    InstCounting.c
)

# Build the library and put it in the build/lib
target_include_directories(InstCounting_rt
    PRIVATE ${PROJECT_SOURCE_DIR}/lib
)
