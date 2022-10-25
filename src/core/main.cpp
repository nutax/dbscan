#include "core/main.h"

int main(int argc, char **argv)
{
    rand_seed(0);
    doors_normal();
    doors_simd();
    hello();
    return EXIT_SUCCESS;
}