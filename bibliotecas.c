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
bignum add(bignum a, bignum b){ //devolve a suma de dous enteiros grandes
    int i, n1, n2, valor = 0, ac = 0, k;
    bignum result;
    n1 = a.tam;
    n2 = b.tam;
    if(n1 < n2){
        result.tam = n2;
        result.val = (int*)malloc(result.tam*sizeof(int));
        a.val = (int*)realloc(a.val, result.tam*sizeof(int));
        result.sign = b.sign;
    }
    else if(n1 > n2){
        result.tam = n1;
        result.val = (int*)malloc(result.tam*sizeof(int));
        b.val = (int*)realloc(b.val, result.tam*sizeof(int));
        result.sign = a.sign;
    }
    else{ //n1 == n2
        result.val = (int*)malloc(n2*sizeof(int));
        k = 0;
        while(*(a.val + k) == *(b.val + k)){
            k++;
            if(*(a.val + k) > *(b.val + k)){
                result.sign = a.sign;
                break;
            }
            else if(*(a.val + k) < *(b.val + k)){
                result.sign = b.sign;
                break;
            }
        }
    }
    for (i = n1 - 1; i >= 0; i--){
        *(a.val + i) = a.sign * *(a.val + i);
        *(b.val + i) = b.sign * *(b.val + i);
        valor = *(a.val + i) + *(b.val + i);
        if (valor > 9){
            valor -=10;
            *(result.val + i) = valor + ac;
            ac = 1;
        }
        else if (valor < 0){
            valor += 10;
            ac = -1;
        }
        else{
            *(result.val + i) = valor + ac;
            ac = 0;
        }
        printf("%d ",*(result.val + i));
    }
    return result;
}
bignum sub(bignum a,bignum b){          //resta dous enteiros grandes.
}
bignum mult(bignum a,bignum b){        //devolve o produto de dos enteiros grandes
    int i, j, n1, n2, ac;
    bignum result;
    n1 = a.tam;
    n2 = b.tam;
    for(j = 0; j < n2; j++){
        for(i = 0; i < n1; i++){
            *(result.val + i) = *(a.val + i) * pow(*(b.val + j), j);
        }
    }
}
bignum remainders(bignum a,bignum n){    //devolve o resto da division enteira a/n usando o algoritmo descrito en [1].

}
bignum fact(bignum n){                  //devolve n!.
}
bignum multmod(bignum a,bignum b,bignum n){ //devolve a * b módulo n.

}
