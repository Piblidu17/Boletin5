#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {
    int i, n1, n2, ac = 0;
    int *cad1, *cad2;
    int *result;
    n1 = 100;
    n2 = 100;
    cad1 = (int*)malloc(n1* sizeof(int));
    cad2 = (int*)malloc(n2* sizeof(int));
    scanf("%d",cad1);
    scanf("%d",cad2);
    result = (int*)malloc(n2*sizeof(int));
    for (i = n1; i >= 0; i--){
        *(result + i) = (*(cad1 + i) + *(cad2 + i) + ac);
        if (*(result + i) >= 10){
            *(result + i) = (*(cad1 + i) + *(cad2 + i)) % 10;
            ac = 1;
        }
        printf("%d",*(result+i));
    }
    free(cad1);
    free(cad2);
    free(result);
}
