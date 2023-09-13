cmake_minimum_required(VERSION 3.24)
project(orgsys_lab1 C)

set(CMAKE_C_STANDARD 11)

add_executable(orgsys_lab1 main.c neuro/neuro.c neuro/neuro.h png/png_reader.c png/png_reader.h txt_parsing/txt_parser.c txt_parsing/txt_parser.h)
