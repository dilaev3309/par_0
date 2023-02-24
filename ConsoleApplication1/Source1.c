#define CRT_SECURE_NO_WARNING


#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


int main() {

    double pi = 3.14159265358979323846;
    int size = 100000000;

    clock_t start = clock();
    float* sinarrfl = malloc(size * sizeof(float));
    float sumsinfl = 0;
    float x1 = (2 * pi) / size;

#pragma acc kernels
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < size; i++) {
        sinarrfl[i] = sinf(x1 * i);
        sumsinfl = sinarrfl[i];
    }

    clock_t end = clock();
    double time = (end - start) / CLOCKS_PER_SEC;
    printf("time %f\n", time);
    printf("%.50f\n", sumsinfl);

    free(sinarrfl);

    start = clock();
    double* sinarrdb = malloc(size * sizeof(double));
    double sumsindb = 0;
    double x2 = (2 * pi) / size;
printf("assasas");
#pragma acc kernels
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < size; i++) {
        sinarrdb[i] = sin(x2 * i);
        sumsindb += sinarrdb[i];
    }

    end = clock();
    double time2 = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time %f\n", time2);
    printf("%.50lf\n", sumsindb);

    free(sinarrdb);

    return 0;
}
