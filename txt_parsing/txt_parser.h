//
// Created by kurtlike on 12.09.2023.
//

#ifndef UNTITLED_TXT_PARSER_H
#define UNTITLED_TXT_PARSER_H
#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
enum figure_type{
    SQUARE = 0,
    CIRCLE = 1,
    TRIANGLE = 2,
    UNKNOWN = 3
};
struct img{
    uint8_t height;
    uint8_t wight;
    uint8_t *data;
    enum figure_type type;
};

struct img* parse(FILE *file, enum figure_type type);

#endif //UNTITLED_TXT_PARSER_H
