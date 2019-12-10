bignum str2bignum(char *str) {        //converte unha cadea a bignum.
    bignum bn;
    int i,j;
    j = 0;
    if(str[0] == '-'){
        bn.sign = -1;
    }
    else if (str[0] == '+'){
        bn.sign = 1;
    }
    bn.tam = strlen(str)-1;
    bn.val = (int*)malloc(bn.tam*(sizeof(int)));
    for(i = 1; i <= bn.tam; i++){
        *(bn.val + j) = *(str + i) % 48;
        j++;
    }
    return bn;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {
    int i, n1, n2, valor = 0, ac = 0;
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
        valor = *(cad1 + i) + *(cad2 + i);
        if (valor > 9){ 
             valor -=10; 
            *(result + i) = valor + ac;
            ac = 1;
        }
        else{
            *(result + i) = valor + ac;
            ac = 0;
        }
    }
    printf("%d", *result);
    free(cad1);
    free(cad2);
    free(result);
