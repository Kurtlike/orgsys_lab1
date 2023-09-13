//
// Created by kurtlike on 12.09.2023.
//

#include "txt_parser.h"

struct img* parse(FILE *file, enum figure_type type){
    struct img* img = (struct img*)malloc(sizeof(struct img));
    img->height = 7;
    img->wight = 7;
    img->data = (uint8_t*)malloc(sizeof(uint8_t) * img->height * img->wight);
    for(int i = 0; i < img->height * img->wight; i++){
        char num;
        fscanf(file,"%c", &num);
        if(num == '\n'){
            i--;
            continue;
        }
        img->data[i] = atoi((const char *) &num);
    }
    img->type = type;
    return img;
}