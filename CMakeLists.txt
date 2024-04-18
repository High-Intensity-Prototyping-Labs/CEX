cmake_minimum_required(VERSION 3.19)

project(
        CEX
        DESCRIPTION "The C-Extended Standard Library."
        LANGUAGES C
)

add_library(cex cex.c cex.h)
set_target_properties(cex PROPERTIES PUBLIC_HEADER cex.h)
target_compile_options(cex PRIVATE -std=c89 -O3)

if(DEBUG)
        target_compile_options(cex PRIVATE -g)
endif()

if(CEX_USE_NAMESPACE)
        target_compile_options(cex PRIVATE -DCEX_USE_NAMESPACE)
endif()

install(TARGETS
        cex
        PUBLIC_HEADER
)
