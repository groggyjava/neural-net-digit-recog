#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 
    basic neural network for image recognition
    based on the following resources
    https://www.youtube.com/watch?v=aircAruvnKk&list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi
    http://neuralnetworksanddeeplearning.com/chap1.html
*/

const int PIXEL_DEPTH = 28 * 28;
const int HIDDEN_LAYER_DEPTH = 16;
const int OUTPUT_DEPTH = 10;

typedef struct
{
    int input_count;
    float *input;
    float *weights;

    int output_count;
    float *biases;
    float *output;
} Layer;

/* function declarations */
Layer create_layer(int output_count, int input_count, float *input);
void randomize_array(float arr[], int n);
float activation(float weights[], float inputs[], int n, float bias);
float sigmoid(float x);
void display_weights(Layer foo);

int main()
{
    srand(time(NULL));

    float pixels[PIXEL_DEPTH];

    Layer net[3];
    net[0] =
        create_layer(HIDDEN_LAYER_DEPTH, PIXEL_DEPTH, pixels);
    net[1] =
        create_layer(HIDDEN_LAYER_DEPTH, HIDDEN_LAYER_DEPTH, net[0].output);
    net[2] =
        create_layer(OUTPUT_DEPTH, HIDDEN_LAYER_DEPTH, net[0].output);

    display_weights(net[2]);

    return 0;
}

void display_weights(Layer foo)
{
    for (int i = 0; i < foo.output_count; i++)
    {
        for (int j = 0; j < foo.input_count; j++)
        {
            printf("%1.6f  ", *(foo.weights + i * foo.input_count + j));
        }
        printf("\n");
    }
}

Layer create_layer(int output_count, int input_count, float *input)
{
    Layer layer;
    layer.input_count = input_count;
    layer.output_count = output_count;

    layer.input = input;

    /* weights: allocate memory for 2d matriarrayrandomize_array */
    layer.weights = (float *)malloc(output_count * input_count * sizeof(float));
    randomize_array(layer.weights, output_count * input_count);

    /* biases: allocate memory for vectoarrayrandomize_array */
    layer.biases = (float *)malloc(output_count * sizeof(float));
    randomize_array(layer.biases, output_count);

    layer.output = (float *)malloc(output_count * sizeof(float));
    return layer;
}

/* assigns a value between (0.000000..1.000000)
   to each element of the array pararameter */
void randomize_array(float arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int r = rand();
        arr[i] = (float)rand() / (float)RAND_MAX;
        if (r % 2 == 0)
        {
            arr[i] *= -1;
        }
    }
}

float activation(float weights[], float inputs[], int n, float bias)
{
    float act = bias;
    for (int i = 0; i < n; i++)
    {
        act += inputs[i] * weights[i];
    }
    return sigmoid(act);
}

float sigmoid(float x)
{
    float exp_value;
    float return_value;

    /*** Exponential calculation ***/
    exp_value = exp((double)-x);

    /*** Final sigmoid value ***/
    return_value = 1.0 / (1.0 + exp_value);

    printf("   x: %f\n exp: %f\n sig: %f\n", x, exp_value, return_value);

    return return_value;
}