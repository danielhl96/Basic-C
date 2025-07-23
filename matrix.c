#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Matrix{
    double** matrix;
    int x;
    int y;

}Matrix;

Matrix make_matrix(int x, int y){
    Matrix matrix;
    matrix.x = x;
    matrix.y = y;
    double** array = malloc(sizeof(double*)*y);
    for(int i = 0; i < y; ++i){
        array[i] = malloc(sizeof(double)*x);
        for(int j = 0; j < x; ++j){
            array[i][j] = 0;
        }
    }
    matrix.matrix = array;
    return matrix;
}

void free_matrix(Matrix matrix){
    for(int i = 0; i < matrix.y; ++i){
       free(matrix.matrix[i]);
    }
    free(matrix.matrix);
}


void print_matrix(Matrix matrix){
    for(int i = 0; i < matrix.y; ++i){
        for(int j = 0; j < matrix.x; ++j){
            printf("%f ",matrix.matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

Matrix fill_matrix(Matrix matrix, double* array){
    for(int i = 0; i < matrix.y; ++i){
        for(int j = 0; j < matrix.x; ++j){
            matrix.matrix[i][j] = array[(i*matrix.x)+j];
        }
    }
    return matrix;
}

int dia_sum(Matrix matrix){
    int sum =0;
    for(int i = 0; i < matrix.y;++i){
        sum += matrix.matrix[i][i];
    }
    return sum;
}

double dia_product(Matrix matrix){
    double product = 1.0;
    for (int i = 0; i < matrix.y;++i){
        product *= matrix.matrix[i][i];
    }
    return product;
}

int* colm_sum(Matrix matrix){

    int* array_sum = malloc(sizeof(int)*matrix.x);
    for(int i = 0; i < matrix.x;++i){
        array_sum[i] = 0;
    }
    for(int i = 0; i < matrix.y; ++i){
        for(int j = 0; j < matrix.x;++j){
            array_sum[i] += matrix.matrix[j][i];  
        }
    }
    return array_sum;
}

int* row_sum(Matrix matrix)
{
    int* array_sum = malloc(sizeof(double)*matrix.y);
    for(int i = 0; i < matrix.x;++i){
        array_sum[i] = 0;
    }
    for(int i = 0; i < matrix.y; ++i){
        for(int j = 0; j < matrix.x;++j){
            array_sum[i] += matrix.matrix[i][j];  
        }
    }
    return array_sum;
}

Matrix add_matrix(Matrix matrix1,Matrix matrix2){
    for(int i = 0; i < matrix1.y; ++i){
        for(int j = 0; j < matrix1.x; ++j){
            matrix1.matrix[i][j] += matrix2.matrix[i][j]; 
        }
    }
    return matrix1;
}

Matrix mult_matrix(Matrix matrix1,Matrix matrix2){
    double value = 0;
    int fail_code = -1;
    if(matrix1.x != matrix2.y){
        fprintf(stderr,"The first matrix do not have the same counts of columns like the rows of matrix two!");
        exit(1);
    }
    
    Matrix result = make_matrix(matrix2.x,matrix1.y);
    for(int i = 0; i < matrix1.y;++i){
        for(int j = 0; j < matrix2.x;++j){
            for(int k = 0; k < matrix2.y; ++k){
                value += matrix1.matrix[i][k]*matrix2.matrix[k][j];                
            }
        result.matrix[i][j] = value;
        value = 0.0;
        }
    }
    return result;
}

Matrix transpose(Matrix matrix){
    Matrix mat = make_matrix(matrix.x,matrix.y);
    for(int i = 0; i < matrix.y; ++i){
        for(int j = 0; j < matrix.x; ++j){
            mat.matrix[j][i] = matrix.matrix[i][j];
        }
    }
    return mat;
}

Matrix tri_form(Matrix matrix){
    double koeff1 = 0.0;
    double koeff2 = 0.0;
    for(int i = 0; i < matrix.y-1; ++i){
        koeff1 = matrix.matrix[i][i];
        for(int j = i; j < matrix.y-1; ++j){
            koeff2 = matrix.matrix[j+1][i];
             for(int k = 0; k < matrix.x; ++k){ 
                matrix.matrix[j+1][k] = matrix.matrix[j+1][k] - (matrix.matrix[i][k]/koeff1)*koeff2;
            }
        }
    }
    return matrix;
}

Matrix reduce_form(Matrix matrix, int x, int y) {
    Matrix reduce_matrix = make_matrix(matrix.x - 1, matrix.y - 1);
    int i1 = 0;

    for (int i = 0; i < matrix.y; ++i) {
        if (i == y) continue;
        int j1 = 0;
        for (int j = 0; j < matrix.x; ++j) {
            if (j == x) continue;
            reduce_matrix.matrix[i1][j1] = matrix.matrix[i][j];
            j1++;
        }
        i1++;
    }
    return reduce_matrix;
}


double two_determinant(Matrix matrix){
    return (matrix.matrix[0][0]*matrix.matrix[1][1])-(matrix.matrix[1][0]*matrix.matrix[0][1]);
}
double three_determinant(Matrix matirx){
    return (matirx.matrix[0][0]*matirx.matrix[1][1]*matirx.matrix[2][2]+matirx.matrix[0][1]*matirx.matrix[1][2]*matirx.matrix[2][0]+matirx.matrix[1][0]*matirx.matrix[0][2]*matirx.matrix[2][1])
    -(matirx.matrix[2][0]*matirx.matrix[1][1]*matirx.matrix[0][2])-(matirx.matrix[2][1]*matirx.matrix[1][2]*matirx.matrix[0][0])-(matirx.matrix[2][2]*matirx.matrix[1][0]*matirx.matrix[0][1]);
}

double laplace(Matrix matrix){

    if (matrix.x != matrix.y) {
        fprintf(stderr, "Error: Non-square matrix\n");
        exit(1);
    }

   int n = matrix.x;

    if (n == 1) {
        return matrix.matrix[0][0];
    }
    if (n == 2) {
        return two_determinant(matrix);
    }
    if (n == 3) {
        return three_determinant(matrix);
    }

    double det = 0.0;
    for (int i = 0; i < n; ++i) {
        Matrix minor = reduce_form(matrix, i, 0);
        det += pow(-1, i) * matrix.matrix[i][0] * laplace(minor);
    }
    return det;
}

int main(void) {
    double* mat1 = malloc(sizeof(double)*16);
    for(int i = 0; i < 16;++i){
        mat1[i] = i+1;
    }


    Matrix d = make_matrix(3,4);
    d = fill_matrix(d,mat1);
    d.matrix[0][2] = 74.0;
    d.matrix[0][3] = 33.0;
    d.matrix[1][0] = 22.0;

    printf("DET(%d)\n",laplace(d));
    print_matrix(d);
    free_matrix(d);
    return 0;
}