#include "neuro/neuro.h"
#include "txt_parsing/txt_parser.h"
#include <stdio.h>
#include <sys/time.h>
int main(){
    FILE *square = fopen("C:\\Users\\kurtlike\\CLionProjects\\orgsys_lab1\\data\\square.txt", "r");
    FILE *circle = fopen("C:\\Users\\kurtlike\\CLionProjects\\orgsys_lab1\\data\\circle.txt", "r");
    FILE *triangle= fopen("C:\\Users\\kurtlike\\CLionProjects\\orgsys_lab1\\data\\triangle.txt", "r");
    FILE *square_d_1= fopen("C:\\Users\\kurtlike\\CLionProjects\\orgsys_lab1\\data\\square_d_1.txt", "r");
    FILE *circle_d_1= fopen("C:\\Users\\kurtlike\\CLionProjects\\orgsys_lab1\\data\\circle_d_1.txt", "r");
    FILE *triangle_d_1= fopen("C:\\Users\\kurtlike\\CLionProjects\\orgsys_lab1\\data\\triangle_d_1.txt", "r");
    struct img** images = malloc(sizeof(struct img*) * 3);
    images[0] = parse(square, SQUARE);
    images[1] = parse(circle, CIRCLE);
    images[2] = parse(triangle, TRIANGLE);
    struct img* test_square = parse(square_d_1, UNKNOWN);
    struct img* test_circle = parse(circle_d_1, UNKNOWN);
    struct img* test_triangle = parse(triangle_d_1, UNKNOWN);
    const uint8_t neuro_size[4] = {49,20, 20,3};

    struct network* net = network_init(4, neuro_size);

    struct timeval stop, start;
    gettimeofday(&start, NULL);
    train(net, 3, images, 0.1f, 0.2f);
    gettimeofday(&stop, NULL);
    printf("Train time took %lu ms\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec) / 1000);

    gettimeofday(&start, NULL);
    forward(net,  images[0]);
    gettimeofday(&stop, NULL);
    printf("Forward time took %lu us\n\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    printf("square ");
    print_predicted(net);
    forward(net,  images[1]);
    printf("circle ");
    print_predicted(net);
    forward(net,  images[2]);
    printf("triangle ");
    print_predicted(net);
    printf("\n");
    forward(net,  test_square);
    printf("unknown ");
    print_predicted(net);
    forward(net,  test_circle);
    printf("unknown ");
    print_predicted(net);
    forward(net,  test_triangle);
    printf("unknown ");
    print_predicted(net);
}
