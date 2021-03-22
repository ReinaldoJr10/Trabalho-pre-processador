#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
//Trabalho feito em dupla
//Nome: Reinaldo Coutinho
//Nome: Rodrigo Porto

typedef struct arvore{
  int info;
  int FB;
  struct arvore *esq;
  struct arvore *dir;
}AVL;

AVL *LeArvore(FILE *arq){
  char letra;
  int x;
  AVL *a;

  fscanf(arq,"%c",&letra);
  fscanf(arq,"%d",&x);
  if(x==-1){
    fscanf(arq,"%c",&letra);
    return NULL;
  }else{
    a=(AVL*)malloc(sizeof(AVL));
    a->info=x;
    a->esq=LeArvore(arq);
    a->dir=LeArvore(arq);
    fscanf(arq,"%c",&letra);
    return a;
  }
}

int altura(AVL *a)
{
  if(a==NULL)return 0;
  else
  {
    int he,hd;
    he = altura(a->esq);
    hd = altura(a->dir);
    if(he>hd) return he+1;
    else return hd+1;
  }
}

 void AjustaFB(AVL *a){
   if(a!=NULL){
     int he=altura(a->esq);
     int hd=altura(a->dir);
     a->FB=hd-he;

     AjustaFB(a->esq);
     AjustaFB(a->dir);
   }
 }
 AVL *LerAVL(FILE *arq){
   AVL *a=LeArvore(arq);
   AjustaFB(a);
   return a;
 }

void ImprimeNivel(AVL *a,int cont,int nivel){
  if(a!=NULL){
    if(cont==nivel){
      printf(" %d ",a->info);
    }else{
      ImprimeNivel(a->esq,cont+1,nivel);
      ImprimeNivel(a->dir,cont+1,nivel);
    }
  }
}

void ImprimeArvore(AVL *a,int opc)
{
  if(a!=NULL)
  {
      if(opc==1){
        printf("%d\n",a->info);
        ImprimeArvore(a->esq,opc);
        ImprimeArvore(a->dir,opc);
      }
      if(opc==2){
        ImprimeArvore(a->esq,opc);
        printf("%d\n",a->info);
        ImprimeArvore(a->dir,opc);
      }
      if(opc==3){
        ImprimeArvore(a->esq,opc);
        ImprimeArvore(a->dir,opc);
        printf("%d\n",a->info);
      }
      if(opc==4){
        int alt;
        alt=altura(a);
        for(int i=0;i<alt;i++){
          ImprimeNivel(a,0,i);
          printf("\n");
        }
      }
  }
}

int Procura(AVL *a,int num){
  if(a==NULL) return 0;
  else if(a->info==num){
    return 1;
  }else{
    int testa=Procura(a->esq, num);
    if(testa==1)  return 1;
    return Procura(a->dir,num);
  }
}

void ImprimeNo(AVL *a){
  if(a!=NULL){
    if((a->esq==NULL) && (a->dir==NULL))
      printf("%d",a->info);
    ImprimeNo(a->esq);
    ImprimeNo(a->dir);
  }
}

int NivelNo(AVL *a, int num,int acu)
{
  if(a==NULL)
    return 0;
  else if(a->info==num){
    return acu;
  }else{
   int testa1= NivelNo(a->esq,num,acu+1);
   int testa2= NivelNo(a->dir,num,acu+1);
   if(testa1!=0){
      return testa1;
   }else if(testa2!=0){
      return testa2;
   }else{
     return 0;
   }
  }
}

int Existe(AVL *a,int n){
  if(a==NULL){
    return 0;
  }else if(a->info==n){
    return 1;
  }else if(n<a->info){
    return Existe(a->esq,n);
  }else{
    return Existe(a->dir,n);
  }
}


void ImprimeMenor(AVL *a,int n){
  if(a!=NULL){
    if(a->info<n){
      if(a->esq==NULL && a->dir==NULL){
        printf("%d ",a->info);
      }
      ImprimeMenor(a->esq,n);
      ImprimeMenor(a->dir,n);
    }else{
      ImprimeMenor(a->esq,n);
    }
  }
}

int ProcuraNo(AVL *a,int n,int acu){
  if(a!=NULL){
    if(a->info==n){
      return acu;
    }else if(a->info<n){
      return ProcuraNo(a->dir,n,acu+1);
    }else{
      return ProcuraNo(a->esq,n,acu+1);
    }
  }
}

AVL *RotacaoesqSimples(AVL *r){
  AVL *a=r;
  AVL *b=a->dir;

  a->dir=b->esq;
  b->esq=a;
  if(b->FB==1){
    a->FB=0;
    b->FB=0;
  }else{
    a->FB=1;
    b->FB=-1;
  }
  r=b;
  return r;
}

AVL *RotacaoesqDupla(AVL *r){
  AVL *a=r;
  AVL *c=a->dir;
  AVL *b=c->esq;

  c->esq=b->dir;
  a->dir=b->esq;
  b->esq=a;
  b->dir=c;

  switch(b->FB){
    case -1:
      a->FB=0;
      c->FB=1;
    break;
    case 0:
      a->FB=0;
      c->FB=0;
    break;
    case +1:
      a->FB=-1;
      c->FB=0;
    break;
  }
  b->FB=0;
  r=b;
  return r;
}

AVL *Rotacaoesq(AVL *r){
  if(r->dir->FB==-1){
    r=RotacaoesqDupla(r);
  }else{
    r=RotacaoesqSimples(r);
  }
  return r;
}

AVL *RotacaodirSimples(AVL *r){
  AVL *a=r->esq;
  AVL *b=r;

  a->esq=b->dir;
  a->dir=b;
  if(a->FB==-1){
    a->FB=0;
    b->FB=0;
  }else{
    a->FB=1;
    b->FB=-1;
  }
  r=a;
  return r;
}

AVL *RotacaodirDupla(AVL *r){
  AVL *c=r;
  AVL *a=c->esq;
  AVL *b=a->dir;

  c->esq=b->dir;
  a->dir=b->esq;
  b->esq=a;
  b->dir=c;

  switch(b->FB){
    case -1:
      a->FB=0;
      c->FB=1;
    break;
    case 0:
      a->FB=0;
      c->FB=0;
    break;
    case +1:
      a->FB=-1;
      c->FB=0;
    break;
  }
  b->FB=0;
  r=b;
  return r;
}

AVL *Rotacaodir(AVL *r){
  if(r->esq->FB==1){
    r=RotacaodirDupla(r);
  }else{
    r=RotacaodirSimples(r);
  }
  return r;
}

AVL *Inserir(AVL *r,int x, int *hmudou){
  if(r==NULL){
    r=(AVL*)malloc(sizeof(AVL));
    r->info=x;
    r->esq=NULL;
    r->dir=NULL;
    r->FB=0;
    *hmudou=1;
  }else{
    if(x<=r->info){
      r->esq=Inserir(r->esq,x,hmudou);
      if(*hmudou==1){
        switch(r->FB){
          case -1:
            r=Rotacaodir(r);
            *hmudou=0;
          break;
          case 0:
            r->FB=-1;
            *hmudou=1;
          break;
          case +1:
            r->FB=0;
            *hmudou=0;
          break;
        }
      }
    }else{
      r->dir=Inserir(r->dir,x,hmudou);
      if(*hmudou==1){
        switch(r->FB){
          case -1:
            r->FB=0;
            *hmudou=0;
          break;
          case 0:
            r->FB=+1;
            *hmudou=1;
          break;
          case +1:
            r=Rotacaoesq(r);
            *hmudou=0;
          break;
        }
      }
    }
  }
  return r;
}

AVL *Remover(AVL *r,int x,int *hmudou){
  if(r!=NULL){
    if(r->info==x){
      if(r->esq==NULL && r->dir==NULL){
        free(r);
        *hmudou=1;
        return NULL;
      }else if(r->esq==NULL || r->dir==NULL){
        AVL *aux;
        if(r->esq==NULL)
          aux=r->dir;
        else
          aux=r->esq;
        *hmudou=1;
        return aux;
      }else {
        AVL *maiorEsq=r->esq;
        while(maiorEsq->dir!=NULL)
          maiorEsq=maiorEsq->dir;
        r->info=maiorEsq->info;
        r->esq=Remover(r->esq,r->info,hmudou);

        if(*hmudou==1){
          switch(r->FB){
            case -1:
              r->FB=0;
              *hmudou=1;
            break;
            case 0:
              r->FB=1;
              *hmudou=0;
            break;
            case +1:
            {
              int aux=r->dir->FB;
              r=Rotacaoesq(r);

              if(aux==0)
                *hmudou=0;
              else
                *hmudou=1;
            break;
            }
          }
        }
      }
    }else if(x<r->info){
      r->esq=Remover(r->esq,x,hmudou);
      if(*hmudou==1){
        switch(r->FB){
          case -1:
            r->FB=0;
            *hmudou=1;
          break;
          case 0:
            r->FB=1;
            *hmudou=0;
          break;
          case +1:
          {
            int aux=r->dir->FB;
            r=Rotacaoesq(r);

            if(aux==0)
              *hmudou=0;
            else
              *hmudou=1;
          break;
          }
        }
      }
    }else{
      r->dir=Remover(r->dir,x,hmudou);
      if(*hmudou==1){
        switch(r->FB){
          case +1:
            r->FB=0;
            *hmudou=1;
          break;
          case 0:
            r->FB=-1;
            *hmudou=0;
          break;
          case -1:
          {
            int aux=r->esq->FB;
            r=Rotacaodir(r);

            if(aux==0)
              *hmudou=0;
            else
              *hmudou=1;
          break;
          }
        }
      }
    }
    return r;
  }
}
int main(void) {
  setlocale(LC_ALL, "Portuguese");
  FILE *arq;
  AVL *eucalipto;
  char nome_arq[30],comando;
  int verifica=1,ordem,resultado,num_procura,nivel,hmudou;

  while(verifica==1){
    printf("\nDigite uma opção:\n");
    printf("1-Ler arvore informada pelo usuario\n");//OK
    printf("2-Imprimir arvore\n");//OK
    printf("3-Verificar se um elemento x existe na arvore\n");//OK
    printf("4-Imprimir o nivel de um no x\n");//OK
    printf("5-Imprimir as folhas menores que um valor x\n");//OK
    printf("6-Inserir um nó x na árvore\n");//OK
    printf("7-Remover um nó x na árvore\n");
    printf("8-Sair\n");
    fgets (&comando, 2, stdin);
    fflush(stdin);

    switch (comando)
    {
      case '1':
        printf("Digite o nome do arquivo:\n");
        scanf("%s",nome_arq);
        fflush(stdin);
        arq=fopen(nome_arq,"rt");
        if(arq==NULL) printf("erro ao abrir o arquivo\n");
        else{
          eucalipto=LerAVL(arq);
          printf("\nArquivo lido com sucesso!");
        }
        fclose(arq);
      break;
      case '2':
        printf("============================\n");
        printf("1 - Pré-Ordem\n");
        printf("2 - Em-Ordem\n");
        printf("3 - Pós-Ordem\n");
        printf("4 - Em largura\n");
        scanf("%d",&ordem);
        ImprimeArvore(eucalipto,ordem);
      break;
      case '3':
        printf("Digite um numero para procurar:");
        scanf("%d",&num_procura);
        resultado=Existe(eucalipto,num_procura);
        if(resultado==1)  printf("Número informado está na arvore\n");
        else  printf("Número informado não encontrado\n");
      break;
      case '4':
        printf("Digite um numero para achar o nivel:");
        scanf("%d",&num_procura);
        resultado=Existe(eucalipto,num_procura);
        if(resultado==1)  {
          nivel=ProcuraNo(eucalipto,num_procura,0);
          printf("\n Nivel: %d",nivel);
        }else{
          printf("Número informado não existe\n");
        }
      break;
      case '5':
        printf("Digite um numero:");
        scanf("%d",&num_procura);
        ImprimeMenor(eucalipto,num_procura);
      break;
      case '6':
        printf("Digite um numero para inserir:");
        scanf("%d",&num_procura);
        eucalipto=Inserir(eucalipto,num_procura,&hmudou);
      break;
      case '7':
        printf("Digite um numero para remover: ");
        scanf("%d",&num_procura);
        eucalipto = Remover(eucalipto,num_procura,&hmudou);
      break;
      case '8':
        verifica=0;
      break;
      default:
        printf("erro\n");
    }
  }
}
