#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct
{
  char soyad[15];
  char ad[15];
  int il;
  void *next;
}st;

st * oxufile(st *p,int *N);
void freed(st *p)
{
  st *cur=p;
  while(cur)
  {
    st *del=cur;
    
    printf("silindi %s %s %d\n",cur->soyad,cur->ad,cur->il);
    cur=cur->next;
    free(del);
  }
}
st * TypeMem( st* main)
{
         st* tmp=malloc(sizeof(st));
         if(tmp==NULL)
         {

            printf("No sufficient memory\n");
            return main;
         }
         printf("D.e. adamin melumatlarin girin: ");
         scanf("%s %s %d",tmp->soyad,tmp->ad,&tmp->il);
         tmp->next=NULL;
         return tmp;
}
int Size(st *p);
st *Insert(st *p)
{
   st *main=p;
   printf("Nomreni d.e.: ");
   int k=0;
   scanf("%d",&k);
   if(k>Size(p))
   {
     printf("Error\n");
     return main;
   }
   int i=0;
   st *evelki=NULL,*cur=p;
   bool ff=true;
   while(cur)
   {
      if(i==k)
      {
         st *tmp=TypeMem(main);
         if(tmp==main)
            return main;
         if(i==0)
         {
           ff=false;
           main=tmp;
           tmp->next=cur;
           break; 
         }  
         else
         {
              ff=false;
              tmp->next=evelki->next;
              evelki->next=tmp;
              break; 
         }

               
      }
     i++;   
     evelki=cur;
     cur=cur->next;
   }
   if(ff)
   {
      st *tmp=TypeMem(main);
      if(tmp==main)    
         return main;
      evelki->next=tmp;
  //    tmp->next=NULL; 
   }
   return main; 
}
int Size(st *p)
{
   int N=0;
   st *cur=p;
   while(cur)
   {
      cur=cur->next;
      N++;
   }
   return N;
}

void show(st *p)
{
  st *cur=p;
  while(cur)
  {
    printf("%s %s %d\n",cur->soyad,cur->ad,cur->il);

    cur=cur->next;

  }
}

int main()
{
  st *K231=NULL;
  int N=0;
  K231=oxufile(K231,&N);
  show(K231); 
  printf("===============%d \n",Size(K231));
  K231=Insert(K231);
  show(K231); 
   
  freed(K231);
}

st * oxufile(st *p,int *N)
{
   FILE *f=fopen("text.txt","r");
   if( f==NULL)
   {
     printf("Error\n");
     return NULL;
   }
   st tmp,*cur=NULL;
   while(fscanf(f,"%s %s %d",tmp.soyad,tmp.ad,&tmp.il) !=EOF)
   {
     st *t=malloc(sizeof(st));
     if (t==NULL)
     {
        printf("error\n");
        return p;
     }
     tmp.next=NULL;
     strcpy(t->soyad,tmp.soyad);
     strcpy(t->ad,tmp.ad);
     t->il=tmp.il;
     t->next=tmp.next;
     if(p==NULL)
        p=t;
     else
         cur->next=t;
     cur=t;

   }
   fclose(f);
   return p;
}

