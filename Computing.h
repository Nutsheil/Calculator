#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define PI 3.14159265358979323846264338327950288419716939937510

int Pre_Compute(char* string_to_compute, int string_size, double* result);

int Primary_Check(char* str, int size);

int Secondary_Check(char* string, int size);

int DelSpace(char* string, int size);

int Lexeme_Check(char* string, int size);