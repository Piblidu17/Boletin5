#include "Bibliotecas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void mostrar(bignum a){
    int i;
    if (a.sign == 1){
        printf("O resultado e: ");
    }
    else{
        printf("O resultado e: -");
    }
    i = 0;
    while (i <= a.tam){
        printf("%d", *(a.val + i));
        i++;
    }
}

//Pre:str es un puntero de tipo de char(una cadena), y la función str2bignum se encarga de convertir una cadena a bignum
//Post:La función nos acaba devolviendo el bignum ya transformado
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


//Pre:a y b son dos bignum,y add es una función que suma cifra a cifra,empezando de derecha a izquierda,teniendo en cuenta el acarreo
//y teniendo en cuenta tanto el signo como el tamaño de a y b.LOS NUMEROS DEBEN DE SER DEL MISMO TAMAÑO(100,098)
//Post:Se devuelve el resultado final tras realizar la suma de a y b(cumpliendo las precondiciones claro está)
bignum add(bignum a, bignum b){ //devolve a suma de dous enteiros grandes
    int i, j = 0, n1, n2, valor = 0, ac = 0, k;
    int max, min;
    bignum result;
    n1 = a.tam;
    n2 = b.tam;
    if(n1 < n2){
        result.tam = n2;
        result.val = (int*)malloc((result.tam + 1)*sizeof(int));
        result.sign = b.sign;
    }
    else if(n1 > n2){
        result.tam = n1;
        result.val = (int*)malloc((result.tam + 1)*sizeof(int));
        result.sign = a.sign;
    }
    else{ //n1 == n2
        result.val = (int*)malloc(n2*sizeof(int));
        k = 0;
        while(*(a.val + k) == *(b.val + k)){
            if(*(a.val + k) > *(b.val + k)){
                result.sign = a.sign;
            }
            else if(*(b.val + k) > *(a.val + k)){
                result.sign = b.sign;
            }
            k++;
        }

    }
    for (i = n1 - 1; i >= 0; i--){
        *(a.val + i) = a.sign * *(a.val + i);
        *(b.val + i) = b.sign * *(b.val + i);
        valor = *(a.val + i) + *(b.val + i);
        if (valor > 9){
            if (i != 0){
                valor -=10;
                *(result.val + i) = valor + ac;
                ac = 1;
            }
            else {
                *(result.val + i) = valor + ac;
            }
        }
        else if (valor < 0){
            if ((b.sign == -1 && a.sign == 1) || (b.sign == 1 && a.sign == -1)){
                valor = fabs(valor);
                valor = valor % 10;
                *(result.val + i) = valor + ac;
                ac = 0;
            }
            else{
                if (i != 0){
                    valor = fabs(valor);
                    *(result.val + i) = valor + ac;
                    ac = 0;
                }
                else {
                    *(result.val + i) = valor + ac;
                }
            }
        }
        else{ //valor entre 0 e 9
            if (a.sign == b.sign){
                *(result.val + i) = valor + ac;
                ac = 0;
            }
            if (b.sign == -1){
                valor -= 10;
                valor = fabs(valor);
                *(result.val + i) = valor + ac;
                ac = -1;
            }
            *(result.val + i) = valor + ac;
            ac = 0;
        }
        *(result.val + i) = fabs(*(result.val + i));
    }
    return result;
}

//Pre:a y b son dos bignum,y sub es una funcion que se encarga de restar cifra a cifra,empezando de derecha a izquierda,teniendo en cuenta el acarreo
//y teniendo en cuenta tanto el signo como el tamaño de a y b,y se le invierte el signo de b para poder realizar la funcion suma anterior.
//LOS NUMEROS DEBEN DE SER DEL MISMO TAMAÑO(100,098)
//Post:Se devuelve el resultado final tras realizar la suma de a y b(cumpliendo las precondiciones claro está)
bignum sub(bignum a,bignum b){          //resta dous enteiros grandes.
    bignum result;
    if(b.sign == 1){                    // a resta e igual a suma invertindolle o signo ao segundo sumando
        b.sign = -1;
    }
    else{
        b.sign = 1;
    }
    result = add(a, b);
    return result;
}


//Pre:a y b son dos bignum, y la función mult que nos devuelve la multiplicación entre a y b
//Post:La función se encarga de ir sumando los resultados de la multiplicación de a por el número de b*10^p(de derecha a izquierda)
//p=posición de numero dentro del bignum b
bignum mult(bignum a,bignum b){        //devolve o produto de dos enteiros grandes
    int i, j, k = 0, n1, n2, ac;
    int *n, *m;
    int x = 1, y;
    int *res;
    int suma;
    bignum result;

    n1 = a.tam;
    n2 = b.tam;
    n = (int*)malloc(n1 * sizeof(int));
    m = (int*)malloc(n2 * sizeof(int));
    res = (int*)malloc((n1 + n2) * sizeof(int));

    if (a.sign != b.sign){
        result.sign = -1;
    }
    else{
        result.sign = 1;
    }

    for(i = n2; i>=0; i--){
        ac = 0;
        for(j = n1; j>=0; j--){
            *(res + k) = (*(m + i) * *(n + j) + ac) % 10;
            ac = (*(m + i) * *(n + j) + ac)/10;
            k++;
        }
        *(res + k) = ac;
        k++;
        for(y = 0;y < x;y++){
            *(res + k) = 0;
            k++;
        }
    }

    k = 0;
    ac = 0;
    for(i=0;i < n1 + n2 + 2; i++){
        suma = 0;
        y=0;
        for(j = 1;j <= n2 + 1; j++){
            if(i <= n1 + j){
                suma = suma + *(res + y + i);
            }
            y += j + n1 + 1;
        }
         *(result.val + k) = (suma + ac) % 10;
        k++;
        ac = (suma + ac)/10;
    }
    *(result.val + k) = ac;
    return result;
}


//Pre:a y b son dos bignum, y remainders es una función que devuelve el resto de la división entera a/b
//Post:Se devuelve  el valor tras realizar a-b hasta que a<b,y el resultado sería a módulo b
bignum remainders(bignum a,bignum b){
    //Pre:a y n son dos bignum, y remainders es una función que devuelve el resto de la división entera a/n
    //Post:Se devuelve  el valor tras realizar a-n hasta que a<n,y el resultado sería a módulo n
    bignum r;
    int i, comp1, comp2;

    if(a.sign==b.sign){
        r.sign=a.sign;
        do{
            r = sub(a,b);
        }while(*a.val > *b.val);
        return r;
    }
    else if(a.sign==1 && b.sign==-1){
        r.sign=-1;
        do{
            r = sub(a,b);
        }while(*a.val > *b.val);
        return r;
    }
    else if(a.sign==-1 && b.sign==1){
        r.sign=1;
        do{
            r = sub(a,b);
        }while(*a.val > *b.val);
        return r;
    }
}

//Pre:n es un bignum, fact es una función encargada de devolver el factorial de n
//Post:Se devuelve el valor del productorio de(n-1) hasta llegar al 1
bignum fact(bignum n){                  //devolve n!.
    bignum un;
    bignum a;
    bignum b;
    bignum auxa;
    bignum auxb;
    int i;
    int max = 100;
    un.tam=1;
    un.sign = 1;
    un.val = (int*)malloc(sizeof(int));
    un.val[0]=1;
    if(un.tam==1 && un.val[0]==1){
        return un;
    }
    else if(un.tam==1 && un.val[0]==0){
        return un;
    }
    b = sub(n,un);
    auxb.val=b.val;
    a = mult(n,b);
    auxa.val=a.val;
    for(i=0;i<max;i++){
        b=sub(b,un);
        a=mult(a,b);
        free(auxa.val);
        free(auxb.val);
        auxb.val=b.val;
        auxa.val=a.val;
        if(b.tam==1 && b.val[0]==1){
            break;
        }
        printf("%d", *(a.val + i));
    }
    return a;
}


bignum multmod(bignum a,bignum b,bignum n){ //devolve a * b módulo n.
    
}
