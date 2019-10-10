#include<stdio.h>
#include<stdlib.h>
typedef double real;

typedef struct{
    int len;
    real *coef;
}Polinomio,* PL ;
void destroi(PL p){
    free(p->coef);
}
Polinomio new(int len){
    Polinomio ans;
    ans.len=len;
    ans.coef =(real *)calloc(len,sizeof(real));
    return ans;
}
Polinomio newVet(real* v,int len){
    Polinomio ans =new(len);
    int i;
    for(i=0;i<len;i++){
        ans.coef[i]=v[len-i-1];
    }
    return ans;
}
void simplifica(PL p){
    int i = p->len-1;
    for(;p->coef[i]==0.0;i--);
    p->len = i+1;
    p->coef = (real*)realloc(p->coef,p->len*sizeof(real));
}
real get(PL p,int grau){
    if(grau<p->len){
        return p->coef[grau];
    }
    return 0;
}
void set(PL p,int grau,real value){
    if(grau<p->len){
        p->coef[grau] = value;
        return;
    }
    Polinomio ans =new(grau+1);
    int i;
    for(i=0;i<p->len;i++){
        ans.coef[i]=p->coef[i];
    }
    destroi(p);
    *p=ans;
    p->coef[grau] = value;
}

Polinomio soma(PL a,PL b){
    Polinomio ans = new(a->len > b->len?a->len:b->len);
    int i =0;
    for(i=0;i<ans.len;i++){
        ans.coef[i] = get(a,i)+get(b,i);
    }
    simplifica(&ans);
    return ans;
}
Polinomio subtrai(PL a,PL b){
    Polinomio ans = new(a->len > b->len?a->len:b->len);
    int i =0;
    for(i=0;i<ans.len;i++){
        ans.coef[i] = get(a,i)-get(b,i);
    }
    simplifica(&ans);
    return ans;
}

Polinomio multiplica(PL a,PL b){
    Polinomio ans = new(a->len + b->len);
    int i=0,j =0;
    for(i=0;i<a->len;i++){
        for(j=0;j<b->len;j++)
            ans.coef[i+j] += get(a,i)*get(b,j);
    }
    simplifica(&ans);
    return ans;
}
Polinomio divide(PL a,PL b){
    Polinomio ans;
    return ans;
}
void show(PL p){
    int i;
    for(i=0;i<p->len;i++){
        printf("%g ",p->coef[i]);
    }
    printf("\n");
}
void print(PL p){
    int i = p->len-1;
    FILE *out =stdout;
    real k;
    char printei = 0;
    for(;i>=0;i--){
        k =p->coef[i];
        if(k!=0 ){
            if((k!= 1.0 && k!=-1.0 )|| i==0)
                fprintf(out,"%s %g",k<0?" - ":(printei?" + ":""),k>0?k:-k);
            if(i>0)
                fprintf(out," x");
            if(i>1)
                fprintf(out,"^%d",i);
            printei =1;
        }
    }
    if(!printei)
        fprintf(out,"0");
    fprintf(out,"\n");
}
int main(){
    Polinomio a,b,c;
    double v1[] = {1,1};
    double v2[] = {1,-1};

    a = newVet(v1,2);
    b = newVet(v2,2);
    c = multiplica(&a,&b);

    print(&a);
    print(&b);
    print(&c);

    destroi(&a);
    destroi(&b);
    destroi(&c);
    return 0;
}