#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 8
typedef struct {
     int id;
     char nome[32];
     int pontos;
     int vida;
}
 Jogador;
typedef struct {
     long comparacoes, trocas, deslocamentos, passagens;
}
 Metricas;
void numeros(int v[],const int o[],int n) {
    for(int i=0;i<n;i++)v[i]=o[i];
}
void jogadores(Jogador v[],const Jogador o[],int n) {
    for(int i=0;i<n;i++)v[i]=o[i];
}
void mostrar(int v[],int n) {
    for(int i=0;i<n;i++)printf("%d ",v[i]);
    printf("\n");
}
void mostrarJ(Jogador v[],int n) {
    for(int i=0;i<n;i++)printf("%d %s pontos:%d vida:%d\n",v[i].id,v[i].nome,v[i].pontos,v[i].vida);
}
void metricas(Metricas m) {
    printf("Comparacoes: %ld | Trocas: %ld | Deslocamentos: %ld | Passagens: %ld\n",m.comparacoes,m.trocas,m.deslocamentos,m.passagens);
}
int cmpJ(Jogador a,Jogador b,int criterio,int crescente) {

     int r=0;

     if(criterio==1)r=strcmp(a.nome,b.nome);

     else if(criterio==2)r=(a.vida>b.vida)-(a.vida<b.vida);

     else r=(a.pontos>b.pontos)-(a.pontos<b.pontos);

     if(r==0)r=(a.id>b.id)-(a.id<b.id);

     return crescente?r:-r;
}
int validar(int v[],int n) {
    for(int i=1;i<n;i++)if(v[i-1]>v[i])return 0;
    return 1;
}
int validarJ(Jogador v[],int n,int criterio,int crescente) {
    for(int i=1;i<n;i++)if(cmpJ(v[i-1],v[i],criterio,crescente)>0)return 0;
    return 1;
}
int menor(int v[],int inicio,int n,Metricas *m) {
    int k=inicio;
    for(int j=inicio+1;j<n;j++) {
        m->comparacoes++;
        if(v[j]<v[k])k=j;
    }
    return k;
}
void selection(int v[],int n,Metricas *m) {
    for(int i=0;i<n-1;i++) {
        int k=menor(v,i,n,m);
        if(k!=i) {
            int t=v[i];
            v[i]=v[k];
            v[k]=t;
            m->trocas++;
        }
    }
}
void selectionJ(Jogador v[],int n,int criterio,int crescente,Metricas *m) {
    for(int i=0;i<n-1;i++) {
        int k=i;
        for(int j=i+1;j<n;j++) {
            m->comparacoes++;
            if(cmpJ(v[j],v[k],criterio,crescente)<0)k=j;
        }
        if(k!=i) {
            Jogador t=v[i];
            v[i]=v[k];
            v[k]=t;
            m->trocas++;
        }
    }
}
void inserir(int v[],int pos,Metricas *m) {
    int valor=v[pos],j=pos-1;
    while(j>=0) {
        m->comparacoes++;
        if(v[j]<=valor)break;
        v[j+1]=v[j];
        m->deslocamentos++;
        j--;
    }
    v[j+1]=valor;
}
void insertion(int v[],int n,Metricas *m) {
    for(int i=1;i<n;i++)inserir(v,i,m);
}
void insertionJ(Jogador v[],int n,int criterio,int crescente,Metricas *m) {
    for(int i=1;i<n;i++) {
        Jogador atual=v[i];
        int j=i-1;
        while(j>=0) {
            m->comparacoes++;
            if(cmpJ(v[j],atual,criterio,crescente)<=0)break;
            v[j+1]=v[j];
            m->deslocamentos++;
            j--;
        }
        v[j+1]=atual;
    }
}
void bubble(int v[],int n,Metricas *m) {
    for(int fim=n-1;fim>0;fim--) {
        int trocou=0;
        m->passagens++;
        for(int j=0;j<fim;j++) {
            m->comparacoes++;
            if(v[j]>v[j+1]) {
                int t=v[j];
                v[j]=v[j+1];
                v[j+1]=t;
                m->trocas++;
                trocou=1;
            }
        }
        if(!trocou)break;
    }
}
void bubbleJ(Jogador v[],int n,int criterio,int crescente,Metricas *m) {
    for(int fim=n-1;fim>0;fim--) {
        int trocou=0;
        m->passagens++;
        for(int j=0;j<fim;j++) {
            m->comparacoes++;
            if(cmpJ(v[j],v[j+1],criterio,crescente)>0) {
                Jogador t=v[j];
                v[j]=v[j+1];
                v[j+1]=t;
                m->trocas++;
                trocou=1;
            }
        }
        if(!trocou)break;
    }
}
void intercalar(const int a[],int na,const int b[],int nb,int s[],Metricas *m) {
    int i=0,j=0,k=0;
    while(i<na&&j<nb) {
        m->comparacoes++;
        s[k++]=a[i]<=b[j]?a[i++]:b[j++];
        m->deslocamentos++;
    }
    while(i<na) {
        s[k++]=a[i++];
        m->deslocamentos++;
    }
    while(j<nb) {
        s[k++]=b[j++];
        m->deslocamentos++;
    }
}
void mergeParte(int v[],int aux[],int inicio,int fim,Metricas *m) {
    if(inicio>=fim)return;
    int meio=inicio+(fim-inicio)/2;
    mergeParte(v,aux,inicio,meio,m);
    mergeParte(v,aux,meio+1,fim,m);
    intercalar(v+inicio,meio-inicio+1,v+meio+1,fim-meio,aux+inicio,m);
    for(int i=inicio;i<=fim;i++)v[i]=aux[i];
}
int mergeSort(int v[],int n,Metricas *m) {
    int *aux=malloc((size_t)n*sizeof(int));
    if(!aux)return 0;
    mergeParte(v,aux,0,n-1,m);
    free(aux);
    return 1;
}
void mergeJParte(Jogador v[],Jogador aux[],int inicio,int fim,int c,int asc,Metricas *m) {
    if(inicio>=fim)return;
    int meio=inicio+(fim-inicio)/2;
    mergeJParte(v,aux,inicio,meio,c,asc,m);
    mergeJParte(v,aux,meio+1,fim,c,asc,m);
    int i=inicio,j=meio+1,k=inicio;
    while(i<=meio&&j<=fim) {
        m->comparacoes++;
        aux[k++]=cmpJ(v[i],v[j],c,asc)<=0?v[i++]:v[j++];
        m->deslocamentos++;
    }
    while(i<=meio) {
        aux[k++]=v[i++];
        m->deslocamentos++;
    }
    while(j<=fim) {
        aux[k++]=v[j++];
        m->deslocamentos++;
    }
    for(i=inicio;i<=fim;i++)v[i]=aux[i];
}
int mergeSortJ(Jogador v[],int n,int c,int asc,Metricas *m) {
    Jogador *aux=malloc((size_t)n*sizeof(Jogador));
    if(!aux)return 0;
    mergeJParte(v,aux,0,n-1,c,asc,m);
    free(aux);
    return 1;
}
int particaoAux(int v[],int n,int saida[],Metricas *m) {
    if(n<=0)return -1;
    int pivo=v[n-1],k=0;
    for(int i=0;i<n-1;i++) {
        m->comparacoes++;
        if(v[i]<=pivo) {
            saida[k++]=v[i];
            m->deslocamentos++;
        }
    }
    int pos=k;
    saida[k++]=pivo;
    for(int i=0;i<n-1;i++) {
        m->comparacoes++;
        if(v[i]>pivo) {
            saida[k++]=v[i];
            m->deslocamentos++;
        }
    }
    return pos;
}
int particao(int v[],int inicio,int fim,Metricas *m) {
    int pivo=v[fim],i=inicio;
    for(int j=inicio;j<fim;j++) {
        m->comparacoes++;
        if(v[j]<=pivo) {
            if(i!=j) {
                int t=v[i];
                v[i]=v[j];
                v[j]=t;
                m->trocas++;
            }
            i++;
        }
    }
    if(i!=fim) {
        int t=v[i];
        v[i]=v[fim];
        v[fim]=t;
        m->trocas++;
    }
    return i;
}
void quickParte(int v[],int inicio,int fim,Metricas *m) {
    if(inicio>=fim)return;
    int p=particao(v,inicio,fim,m);
    quickParte(v,inicio,p-1,m);
    quickParte(v,p+1,fim,m);
}
void quickSort(int v[],int n,Metricas *m) {
    if(n>0)quickParte(v,0,n-1,m);
}
void demonstrar(void) {

     int original[N]= {
        8,3,7,2,9,1,5,4
    };

     Jogador origJ[N]= { {
            1,"Ana",50,80
        }, {
            2,"Bruno",30,90
        }, {
            3,"Ana",50,60
        }, {
            4,"Carla",70,70
        }, {
            5,"Davi",50,85
        }, {
            6,"Eva",20,60
        }, {
            7,"Bia",70,90
        }, {
            8,"Caio",30,80
        }
    };

     int v[N];
    Jogador j[N];
    Metricas m= {
        0
    };

     numeros(v,original,N);
    jogadores(j,origJ,N);

     printf("Original: ");
    mostrar(original,N);

     quickSort(v,N,&m);

     printf("Ordenado: ");
    mostrar(v,N);
    metricas(m);

     printf("Validacao numeros: %s\n",validar(v,N)?"OK":"ERRO");

     int aux[N];
    m=(Metricas) {
        0
    };
    int p=particaoAux(original,N,aux,&m);
    printf("Pivo auxiliar na posicao %d: ",p);
    mostrar(aux,N);
    metricas(m);
}
int main(void) {
    srand((unsigned)time(NULL));
    demonstrar();
    return 0;
}
