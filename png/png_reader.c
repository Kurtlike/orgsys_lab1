//
// Created by kurtlike on 12.09.2023.
//

#include "png_reader.h"
/*
unsigned char* encode_image(const char* path){
    FILE *png;
    int ret = 0;
    spng_ctx *ctx = NULL;
    unsigned char *image = NULL;

    png = fopen(path, "rb");
    ctx = spng_ctx_new(0);
    spng_set_png_file(ctx, png);

    struct spng_ihdr ihdr;
    spng_get_ihdr(ctx, &ihdr);

    printf("width: %u\n"
           "height: %u\n"
           "bit depth: %u\n",
           ihdr.width, ihdr.height, ihdr.bit_depth, ihdr.color_type);

    printf("compression method: %u\n"
           "filter method: %u\n"
           "interlace method: %u\n",
           ihdr.compression_method, ihdr.filter_method, ihdr.interlace_method);

    size_t image_size, image_width;
    int fmt = SPNG_FMT_PNG;
    if(ihdr.color_type == SPNG_COLOR_TYPE_INDEXED) fmt = SPNG_FMT_RGB8;
    spng_decoded_image_size(ctx, fmt, &image_size);
    image = malloc(image_size);
    spng_decode_image(ctx, NULL, 0, fmt, SPNG_DECODE_PROGRESSIVE);
    image_width = image_size / ihdr.height;
    struct spng_row_info row_info = {0};
    spng_get_row_info(ctx, &row_info);
    spng_decode_row(ctx, image + row_info.row_num * image_width, image_width);
    return image;
}*/