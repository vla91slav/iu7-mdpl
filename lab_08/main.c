#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#define I 1e9

double add_float(float a, float b) {
    float res;
    time_t beg, end;

    beg = clock();

    for (int i = 0; i < I; i++) {
        res = a + b;
    }

    end = clock();

    return (double)(end - beg) / CLOCKS_PER_SEC; 
}

double add_float_asm(float a, float b) {
    float res;
    time_t beg, end;

    beg = clock();

    for (int i = 0; i < I; i++) {
        asm(
            "FLD %1\n"
            "FLD %2\n"
            "FADDP %%ST(1), %%ST(0)\n"
            "FSTP %0\n"
            : "=m"(res)
            : "m"(a), "m"(b)
        );
    }

    end = clock();

    return (double)(end - beg) / CLOCKS_PER_SEC; 
}

double add_double(double a, double b) {
    double res;
    time_t beg, end;

    beg = clock();

    for (int i = 0; i < I; i++) {
        res = a + b;
    }

    end = clock();

    return (double)(end - beg) / CLOCKS_PER_SEC; 
}

double add_double_asm(double a, double b) {
    double res;
    time_t beg, end;

    beg = clock();

    for (int i = 0; i < I; i++) {
        asm(
            "FLD %1\n"
            "FLD %2\n"
            "FADDP %%ST(1), %%ST(0)\n"
            "FSTP %0\n"
            : "=m"(res)
            : "m"(a), "m"(b)
        );
    }

    end = clock();

    return (double)(end - beg) / CLOCKS_PER_SEC; 
}

double add_long(long double a, long double b) {
    #ifndef SSE
    long double res;
    time_t beg, end;

    beg = clock();

    for (int i = 0; i < I; i++) {
        res = a + b;
    }

    end = clock();

    return (double)(end - beg) / CLOCKS_PER_SEC;
    #endif
    return 0;
}

double add_long_asm(long double a, long double b) {
    long double res;
    time_t beg, end;

    beg = clock();

    for (int i = 0; i < I; i++) {
        asm(
            "FLD %1\n"
            "FLD %2\n"
            "FADDP %%ST(1), %%ST(0)\n"
            "FSTP %0\n"
            : "=m"(res)
            : "m"(a), "m"(b)
        );
    }

    end = clock();

    return (double)(end - beg) / CLOCKS_PER_SEC; 
}

double mul_float(float a, float b) {
    float res;
    time_t beg, end;

    beg = clock();

    for (int i = 0; i < I; i++) {
        res = a * b;
    }

    end = clock();

    return (double)(end - beg) / CLOCKS_PER_SEC; 
}

double mul_float_asm(float a, float b) {
    float res;
    time_t beg, end;

    beg = clock();

    for (int i = 0; i < I; i++) {
        asm(
            "FLD %1\n"
            "FLD %2\n"
            "FMULP %%ST(1), %%ST(0)\n"
            "FSTP %0\n"
            : "=m"(res)
            : "m"(a), "m"(b)
        );
    }

    end = clock();

    return (double)(end - beg) / CLOCKS_PER_SEC; 
}

double mul_double(double a, double b) {
    double res;
    time_t beg, end;

    beg = clock();

    for (int i = 0; i < I; i++) {
        res = a * b;
    }

    end = clock();

    return (double)(end - beg) / CLOCKS_PER_SEC; 
}

double mul_double_asm(double a, double b) {
    double res;
    time_t beg, end;

    beg = clock();

    for (int i = 0; i < I; i++) {
        asm(
            "FLD %1\n"
            "FLD %2\n"
            "FMULP %%ST(1), %%ST(0)\n"
            "FSTP %0\n"
            : "=m"(res)
            : "m"(a), "m"(b)
        );
    }

    end = clock();

    return (double)(end - beg) / CLOCKS_PER_SEC; 
}

double mul_long(long double a, long double b) {
    #ifndef SSE
    long double res;
    time_t beg, end;

    beg = clock();

    for (int i = 0; i < I; i++) {
        res = a * b;
    }

    end = clock();

    return (double)(end - beg) / CLOCKS_PER_SEC;
    #endif
    return 0;
}

double mul_long_asm(long double a, long double b) {
    long double res;
    time_t beg, end;

    beg = clock();

    for (int i = 0; i < I; i++) {
        asm(
            "FLD %1\n"
            "FLD %2\n"
            "FMULP %%ST(1), %%ST(0)\n"
            "FSTP %0\n"
            : "=m"(res)
            : "m"(a), "m"(b)
        );
    }

    end = clock();

    return (double)(end - beg) / CLOCKS_PER_SEC; 
}

double sin_asm() {
    double res;

    asm(
        "FLDPI\n"
        "FSIN\n"
        "FSTP %0\n"
        : "=m"(res)
    );

    return res;
}

double half_sin_asm() {
    double res;
    int d = 2;

    asm(
        "FLDPI\n"
        "FILD %1\n"
        "FDIVP\n"
        "FSIN\n"
        "FSTP %0\n"
        : "=m"(res)
        : "m"(d)
    );
    return res;
}

int main(void) {
    float a1, b1;
    double a2, b2;
    long double a3, b3;

    a1 = a2 = a3 = 123324.32423;
    b1 = b2 = b3 = 6754523.326436456;

    #ifndef SSE
    a1 = a2 = a3 = (double)rand() / RAND_MAX + 1;
    b1 = b2 = b3 = (double)rand() / RAND_MAX + 1;
    #endif

    // ----------------
    printf("---------------------------------------------------------------------\n");
    printf("|                                 C                                 |\n");
    printf("---------------------------------------------------------------------\n");
    printf("|                |      FLOAT     |     DOUBLE     |      LONG      |\n");
    printf("--------------------------------------------------------------------|\n");
    printf("|       ADD      |%16lf|%16lf|%16lf|\n", add_float(a1, b1), add_double(a2, b2), add_long(a3, b3));
    printf("|       MUL      |%16lf|%16lf|%16lf|\n", mul_float(a1, b1), mul_double(a2, b2), mul_long(a3, b3));
    printf("|-------------------------------------------------------------------|\n");
    printf("|                                ASM                                |\n");
    printf("|-------------------------------------------------------------------|\n");
    printf("|       ADD      |%16lf|%16lf|%16lf|\n", add_float_asm(a1, b1), add_double_asm(a2, b2), add_long_asm(a3, b3));
    printf("|       MUL      |%16lf|%16lf|%16lf|\n", mul_float_asm(a1, b1), mul_double_asm(a2, b2), mul_long_asm(a3, b3));
    printf("---------------------------------------------------------------------\n");

    printf("\n\n");

    printf("sin(3.14)         = %.20f\n", sin(3.14));
    printf("sin(3.141596)     = %.20f\n", sin(3.141596));
    printf("ASM sin(PI)       = %.20f\n", sin_asm());

    printf("sin(3.14 / 2)     = %.20f\n", sin(3.14 / 2));
    printf("sin(3.141596 / 2) = %.20f\n", sin(3.141596 / 2));
    printf("ASM sin(PI / 2)   = %.20f\n", half_sin_asm());
}