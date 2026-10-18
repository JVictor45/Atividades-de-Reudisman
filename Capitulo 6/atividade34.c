#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 8
typedef struct { int id; char nome[32]; int pontos; int vida; } Jogador;
typedef struct { long comparacoes, trocas, deslocamentos, passagens; } Metricas;
void numeros(int v[],const int o[],int n){for(int i=0;i<n;i++)v[i]=o[i];}
void jogadores(Jogador v[],const Jogador o[],int n){for(int i=0;i<n;i++)v[i]=o[i];}
void mostrar(int v[],int n){for(int i=0;i<n;i++)printf("%d ",v[i]);printf("\n");}
void mostrarJ(Jogador v[],int n){for(int i=0;i<n;i++)printf("%d %s pontos:%d vida:%d\n",v[i].id,v[i].nome,v[i].pontos,v[i].vida);}
void metricas(Metricas m){printf("Comparacoes: %ld | Trocas: %ld | Deslocamentos: %ld | Passagens: %ld\n",m.comparacoes,m.trocas,m.deslocamentos,m.passagens);}
int cmpJ(Jogador a,Jogador b,int criterio,int crescente){
 int r=0;
 if(criterio==1)r=strcmp(a.nome,b.nome);
 else if(criterio==2)r=(a.vida>b.vida)-(a.vida<b.vida);
 else r=(a.pontos>b.pontos)-(a.pontos<b.pontos);
 if(r==0)r=(a.id>b.id)-(a.id<b.id);
 return crescente?r:-r;
}
int validar(int v[],int n){for(int i=1;i<n;i++)if(v[i-1]>v[i])return 0;return 1;}
int validarJ(Jogador v[],int n,int criterio,int crescente){for(int i=1;i<n;i++)if(cmpJ(v[i-1],v[i],criterio,crescente)>0)return 0;return 1;}
int menor(int v[],int inicio,int n,Metricas *m){int k=inicio;for(int j=inicio+1;j<n;j++){m->comparacoes++;if(v[j]<v[k])k=j;}return k;}
void selection(int v[],int n,Metricas *m){for(int i=0;i<n-1;i++){int k=menor(v,i,n,m);if(k!=i){int t=v[i];v[i]=v[k];v[k]=t;m->trocas++;}}}
void selectionJ(Jogador v[],int n,int criterio,int crescente,Metricas *m){for(int i=0;i<n-1;i++){int k=i;for(int j=i+1;j<n;j++){m->comparacoes++;if(cmpJ(v[j],v[k],criterio,crescente)<0)k=j;}if(k!=i){Jogador t=v[i];v[i]=v[k];v[k]=t;m->trocas++;}}}
void inserir(int v[],int pos,Metricas *m){int valor=v[pos],j=pos-1;while(j>=0){m->comparacoes++;if(v[j]<=valor)break;v[j+1]=v[j];m->deslocamentos++;j--;}v[j+1]=valor;}
void insertion(int v[],int n,Metricas *m){for(int i=1;i<n;i++)inserir(v,i,m);}
void insertionJ(Jogador v[],int n,int criterio,int crescente,Metricas *m){for(int i=1;i<n;i++){Jogador atual=v[i];int j=i-1;while(j>=0){m->comparacoes++;if(cmpJ(v[j],atual,criterio,crescente)<=0)break;v[j+1]=v[j];m->deslocamentos++;j--;}v[j+1]=atual;}}
void demonstrar(int etapa){
    int original[N]={8,3,7,2,9,1,5,4};
Jogador origJ[N]={{1,"Ana",50,80},{2,"Bruno",30,90},{3,"Ana",50,60},{4,"Carla",70,70},{5,"Davi",50,85},{6,"Eva",20,60},{7,"Bia",70,90},{8,"Caio",30,80}};

    int v[N];Jogador j[N];Metricas m={0};
    numeros(v,original,N);jogadores(j,origJ,N);
    printf("Original: ");mostrar(original,N);
    if(etapa==32)selection(v,N,&m);
    if(etapa==33||etapa==34)insertion(v,N,&m);
    if(etapa==35||etapa==36)bubble(v,N,&m);
    if(etapa==37){int a[4]={1,3,5,7},b[4]={2,4,6,8};intercalar(a,4,b,4,v,&m);}
    if(etapa==38)mergeSort(v,N,&m);
    if(etapa==39||etapa==40)quickSort(v,N,&m);
    printf("Ordenado: ");mostrar(v,N);metricas(m);
    printf("Validacao numeros: %s\n",validar(v,N)?"OK":"ERRO");
    if(etapa==32){m=(Metricas){0};selectionJ(j,N,0,1,&m);}
    if(etapa==34){m=(Metricas){0};insertionJ(j,N,1,1,&m);}
    if(etapa==36){m=(Metricas){0};bubbleJ(j,N,2,0,&m);}
    if(etapa==38){m=(Metricas){0};mergeSortJ(j,N,0,1,&m);}
    if(etapa==40){m=(Metricas){0};quickJ(j,N,0,1,&m);}
    if(etapa==32||etapa==34||etapa==36||etapa==38||etapa==40){
        mostrarJ(j,N);metricas(m);
        int c=etapa==34?1:etapa==36?2:0;
        int asc=etapa==36?0:1;
        printf("Validacao jogadores: %s\n",validarJ(j,N,c,asc)?"OK":"ERRO");
    }
    if(etapa==35){
        int ordenado[N]={1,2,3,4,5,6,7,8};
        int inverso[N]={8,7,6,5,4,3,2,1};
        int aleatorio[N]={5,1,8,2,7,3,6,4};
        int *casos[3]={ordenado,inverso,aleatorio};
        for(int i=0;i<3;i++){m=(Metricas){0};bubble(casos[i],N,&m);printf("Caso %d: ",i+1);metricas(m);}
    }
    if(etapa==39){int aux[N];m=(Metricas){0};int p=particaoAux(original,N,aux,&m);printf("Pivo auxiliar na posicao %d: ",p);mostrar(aux,N);metricas(m);}
}
int main(void){demonstrar(34);return 0;}
