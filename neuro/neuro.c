//
// Created by kurtlike on 12.09.2023.
//


#include "neuro.h"

struct network* network_init(uint8_t level_len,  const uint8_t* neurons_size){
    struct network* net = (struct network*)malloc(sizeof(struct network));
    net->level_size = level_len;
    net->layers = (struct layer*)malloc(sizeof(struct layer) * level_len);

    net->layers[0].size = neurons_size[0];
    net->layers[0].neurons = (struct neuron*) malloc(sizeof(struct neuron) * neurons_size[0]);
    net->layers[0].neurons->in_size = 0;
    for(int j = 0; j < neurons_size[0]; j++) {
        net->layers[0].neurons[j].in_size = 1;
        net->layers[0].neurons[j].in = (float*)malloc(sizeof(float));
        net->layers[0].neurons[j].in[0] = 1;
        net->layers[0].neurons[j].out = 0;
    }

    for(int l = 1; l < level_len; l++){
        net->layers[l].size = neurons_size[l];
        net->layers[l].neurons = (struct neuron*) malloc(sizeof(struct neuron) * neurons_size[l]);
        for(int i = 0; i < neurons_size[l]; i++){
            net->layers[l].neurons[i].in_size = neurons_size[l-1];
            net->layers[l].neurons[i].in = (float*)malloc(sizeof(float) * neurons_size[l-1]);
            for(int j = 0; j < net->layers[l].neurons[i].in_size; j++){
                net->layers[l].neurons[i].in[j] =(float)(rand()%100)/500;
            }
        }

    }
    return net;
}
float sigm(float x){
    return 1 / (1 + expf(-x));
}
void forward(struct network* net, struct img* img){
    for(int i = 0; i < net->layers[0].size; i++){
        net->layers[0].neurons[i].out = img->data[i];
    }
    for(int l = 1; l < net->level_size; l++){
        for(int i = 0; i < net->layers[l].size; i++){
            float sum = 0;
            for(int j = 0; j < net->layers[l].neurons[i].in_size; j++){
                sum+= net->layers[l].neurons[i].in[j] * net->layers[l - 1].neurons[j].out;
            }
            float s = sigm(sum);
            net->layers[l].neurons[i].out = s;
        }
    }
}
uint8_t** create_answers_from_images_type(uint8_t size, struct img** images){
    uint8_t **answ = malloc(sizeof(uint8_t*) * size);
    for(int i = 0; i < size; i++){
        answ[i] = malloc(sizeof(uint8_t) * size);
        uint8_t n = images[i]->type;
        for(int j = 0; j < size; j++){
            if(j == n) answ[i][j] = 1;
            else  answ[i][j] = 0;
        }
    }
    return answ;
}
void train(struct network* net, uint8_t size, struct img** images, float er, float a){
    float error = 1;
    uint8_t **answers = create_answers_from_images_type(size, images);
    int epoch = 0;
    while(error > er){
        error = 0;
        for(int n = 0; n < size; n++){
            forward(net, images[n]);
            float local_err = find_error(net, answers[n]);
            if(local_err > er){
                backward(net, answers[n], a);
            }
            error += local_err;
        }
        error/= size;
        epoch++;
    }
    printf("number of epochs = %d\n", epoch);
}

float find_error(struct network* net, const uint8_t *answers){
    float error = 0;
    for(int i = 0; i < net->layers[net->level_size - 1].size; i++){
        error+= fabs((float)answers[i] - net->layers[net->level_size - 1].neurons[i].out);
    }
    return error/2;

}
float find_delta(struct network* net, uint8_t layer_n, uint16_t neuron_i, const uint8_t* answers){
    float delta;
    float y;
    float delta_sum = 0;
    if(net->level_size == layer_n + 1){
        y = net->layers[net->level_size - 1].neurons[neuron_i].out;
        delta = y * (1 - y) * ((float)answers[neuron_i] - y);
        net->layers[net->level_size - 1].neurons[neuron_i].delta_error = delta;
    }else{
        y = net->layers[layer_n].neurons[neuron_i].out;
        for(int j = 0; j < net->layers[layer_n + 1].size; j++){
            float next_delta = net->layers[layer_n + 1].neurons[j].delta_error;
            float next_w = net->layers[layer_n + 1].neurons[j].in[neuron_i];
            delta_sum += next_delta * next_w;
        }
        delta = y * (1 - y) * delta_sum;
        net->layers[layer_n].neurons[neuron_i].delta_error = delta;
    }
    return delta;
}
void backward(struct network* net, const uint8_t* answers, float a){
    float delta_w;
    for(int k = net->level_size - 1; k > 0; k--){
        for(int i = 0; i < net->layers[k].size; i++){
            for(int j = 0; j < net->layers[k].neurons[i].in_size; j++){
                delta_w = a * net->layers[k - 1].neurons[j].out * find_delta(net, k, i, answers);
                net->layers[k].neurons[i].in[j] += delta_w;
            }
        }
    }
}
void print_predicted(struct network* net){
    for(int i = 0; i < net->layers[net->level_size - 1].size; i++){
        printf("%4f ", net->layers[net->level_size - 1].neurons[i].out);
    }
    printf("\n");
}
void print_network(struct network* net){
    char strings[50][100] = {0};
    for(int i = 0; i < net->level_size; i++){
        for(int j = 0; j < net->layers[i].size; j++){
            char str[10];
            sprintf(str, "%3.2f    ", net->layers[i].neurons[j].out);
            strcat(&strings[j][i], str);
        }
    }
    for(int i = 0; i < 50; i++){
        printf("%s\n", strings[i]);
    }
}