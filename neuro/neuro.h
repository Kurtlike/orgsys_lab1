//
// Created by kurtlike on 12.09.2023.
//

#ifndef UNTITLED_NEURO_H
#define UNTITLED_NEURO_H
#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include "../txt_parsing/txt_parser.h"

struct neuron{
    uint16_t in_size;
    float* in;
    float out;
    float delta_error;
};
struct layer{
    uint16_t size;
    struct neuron* neurons;
};
struct network{
    uint8_t level_size;
    struct layer* layers;
};
void print_predicted(struct network* net);
void train(struct network* net, uint8_t size, struct img** images, float er, float a);
float find_error(struct network* net,  const uint8_t* answers);
void forward(struct network* net, struct img* img);
void backward(struct network* net, const uint8_t* answers, float a);
void print_network(struct network* net);
struct network* network_init(uint8_t level_len,  const uint8_t* neurons_size);

#endif //UNTITLED_NEURO_H
