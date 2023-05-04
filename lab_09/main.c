#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4
#define I 1e5

typedef struct {
    float list[N];
} vector_t;

double dot_product(const vector_t v1, const vector_t v2) {
    float res = 0;
    time_t beg, end;

    beg = clock();
    for (int i = 0; i < I; i++) {
        res = 0;
        for (int i = 0; i < N; i++)
            res += v1.list[i] * v2.list[i];
    }
    end = clock();
    return (double)(end - beg) / CLOCKS_PER_SEC; 
}

double dot_product_asm(const vector_t v1, const vector_t v2) {
    float res = 0;
    time_t beg, end;

    beg = clock();
    for (int i = 0; i < I; i++) {
        asm(
            "movups %1, %%xmm0\n"
            "movups %2, %%xmm1\n"

            "mulps %%xmm1, %%xmm0\n"

            "movhlps %%xmm0, %%xmm1\n"
            "addps %%xmm1, %%xmm0\n"
            "movaps %%xmm0, %%xmm1\n"
            "shufps $1, %%xmm0, %%xmm0\n"
            "addps %%xmm1, %%xmm0\n"
            "movss %%xmm0, %0\n"
            : "=m"(res)
            : "m"(v1.list), "m"(v2.list)
            : "xmm0", "xmm1"
        );
    }
    end = clock();
    return (double)(end - beg) / CLOCKS_PER_SEC; 
}

int main(void) {
    vector_t v1 = { 1e-5, 2.32 ,4.45, 1.78};
    vector_t v2 = {2.900, 3.0, 4.43, 1.2};

    printf("C   - %lf\n", dot_product(v1, v2));
    printf("ASM - %lf\n", dot_product_asm(v1, v2));

    return 0;
}