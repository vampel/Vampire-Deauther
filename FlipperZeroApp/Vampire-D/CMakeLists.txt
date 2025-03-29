cmake_minimum_required(VERSION 3.13)
project(vampire_deauther)

add_executable(vampire_deauther
    vampire_deauther.c
    vampire_deauther.h
)

target_link_libraries(vampire_deauther
    furi
)
