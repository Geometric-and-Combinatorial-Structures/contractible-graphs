#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Numero maximo de vertice
#define MaxNumV 142
#define NvMax 142
#define N 142

FILE *AE,*AS;

void ImpG(unsigned short int G[MaxNumV][MaxNumV],int nV){
	int i,j;
	printf("\n");
	for(i=0;i<nV;i++){
		for(j=0;j<nV;j++)printf("%d ",G[i][j]);printf("\n");
	}	
	printf("\n");
}

void ImpG_A(unsigned short int G[MaxNumV][MaxNumV],int nV){
	int i,j;
	fprintf(AS,"\n");
	for(i=0;i<nV;i++){
		for(j=0;j<nV;j++)fprintf(AS,"%d ",G[i][j]);fprintf(AS,"\n");
	}	
	fprintf(AS,"\n");
}

//Calcula grados o valencias de vertices
void CalVal(unsigned short int A[N][N], unsigned short int n,unsigned short int Val[N]){
	unsigned short int i,j;
	for(i=0;i<n;i++){
        Val[i]=0;
        for(j=0;j<n;j++) if(A[i][j]==1) Val[i]++;
	}
}

//Calcula el Link del vertice k de una grafica
void CalLk(unsigned short int A[N][N], unsigned short int n, unsigned short int Val[N], unsigned short int k, unsigned short int Lk[N][N], unsigned short int *m){
	unsigned short int i,j;
	unsigned short int Isobre[N];
	unsigned short int Cont=0;
	*m=Val[k];
	for(j=0;j<n;j++) {
		if(A[k][j]==1) {
		  Isobre[Cont]=j;
		  //EtLk[Cont]=Et[j]; 
		  Cont++;	
		}
	}
	
	for(i=0;i<*m;i++){
		for(j=0;j<*m;j++){
			Lk[i][j]=A[Isobre[i]][Isobre[j]];
		}
	}
	//ImpMat(Lk,*m,EtLk);
}


//Elimina el vertice k de una grafica
void EliminaVert(unsigned short int A[N][N], unsigned short int n,unsigned short int k, unsigned short int B[N][N], unsigned short int *m){
	unsigned short int i,j;	
	*m=n-1;
	for(i=0;i<*m;i++){
		for(j=0;j<*m;j++){
			if(i<k && j<k) B[i][j]=A[i][j];
			if(!(i<k) && j<k) B[i][j]=A[i+1][j];
			if(i<k && !(j<k)) B[i][j]=A[i][j+1];
			if(!(i<k) && !(j<k)) B[i][j]=A[i+1][j+1];
		}
	}    
}


//Función recursiva que devuelve 1 si G \in T
unsigned short int PaT(unsigned short int G[MaxNumV][MaxNumV],unsigned short int n){
	int i;
	unsigned short int Val[MaxNumV];
    unsigned short int m;           
    unsigned short int Lk[MaxNumV][MaxNumV];
    unsigned short int ValLk[MaxNumV];

	unsigned short int GmV[MaxNumV][MaxNumV],EtGmV[N];
    if(n==0 || n==1) {
	  return n;	
	}
    else{
        //Intentar eliminar un vertice
        for(i=0;i<n;i++){
              //Calcula Lk de v_i
            CalVal(G,n,Val);
			CalLk(G,n,Val,i,Lk,&m);
			  if(PaT(Lk,m)==1){
			  	  EliminaVert(G,n,i,GmV,&m);
			  	  return PaT(GmV,m);
			  }	
        	
		}
		//Si no pude elminar algun vertice devuelve 0
		return 0;
	}	
}


void CalN(short unsigned int GN[MaxNumV][MaxNumV], short unsigned int GCand[MaxNumV][MaxNumV],int nV,int v,int *val){
	int i,j,Indice[MaxNumV];*val=0;
	//Extraer indices
	for(j=0;j<nV;j++){
		if(GCand[v][j]==1){
			Indice[*val]=j;(*val)++;
		}
	}
	for(i=0;i<*val;i++){
	   for(j=0;j<*val;j++){
		  GN[i][j]=GCand[Indice[i]][Indice[j]];
	   }	
	}

}

void Calc_GmV(	short unsigned int Gcand[MaxNumV][MaxNumV],int *nV,int v){
	int i,j;
	short unsigned int GmV[MaxNumV][MaxNumV];
	for(i=0;i<v;i++) for(j=0;j<v;j++) GmV[i][j]=Gcand[i][j];
	
	for(i=0;i<v;i++) for(j=v+1;j<*nV;j++) GmV[i][j-1]=Gcand[i][j];
	for(i=v+1;i<*nV;i++) for(j=0;j<v;j++) GmV[i-1][j]=Gcand[i][j];
	for(i=v+1;i<*nV;i++) for(j=v+1;j<*nV;j++) GmV[i-1][j-1]=Gcand[i][j];
	(*nV)--;
    for(i=0;i<*nV;i++) for(j=0;j<*nV;j++) Gcand[i][j]=GmV[i][j];
}

// 	    RedIv_G(GCand,&n,V,S,&nn);
void RedIv_G(short unsigned int GCand[MaxNumV][MaxNumV], int *n, short unsigned int V[MaxNumV], short unsigned int S[MaxNumV], int *nn){
	int reduced=0,i=0,j,m;
	short unsigned int GN[MaxNumV][MaxNumV];
	*nn=0;
	do{
	   CalN(GN,GCand,*n,i,&m);	
	   if(PaT(GN,m)==1){
	       S[*nn]=V[i];(*nn)++;
		   for(j=i;j<*n-1;j++) V[j]=V[j+1];   	
	   	   Calc_GmV(GCand,n,i);
	   	   i=0;
	   }else{
	   	   i++;
	   	   if(i>*n-1) reduced=1;
	   }	
	}while(i<*n && reduced==0);
}

// version para aplicacion de contracciones de ivashenko en persistencia....
int main(){
	short unsigned int GCand[MaxNumV][MaxNumV],V[MaxNumV],S[MaxNumV];
  int nGnm,nG,n,nn,m,nrespaldo;
  int i,j,k,kk;
  
AE=fopen("graph.txt","r");
AS=fopen("reduced_graph.txt","w");
fscanf(AE,"%d",&n); 

		//Leer grafica de archivo
		for(i=0;i<n;i++){
		   for(j=0;j<n;j++){
		      fscanf(AE,"%d",&GCand[i][j]);	
		   }
		}
	
		ImpG(GCand,n);
		
		for(i=0;i<n;i++) V[i]=i+1;
	    RedIv_G(GCand,&n,V,S,&nn);
        for(i=0;i<n;i++) fprintf(AS,"%d ",V[i]);
        fprintf(AS,"\n");
  	fclose(AE);
  	fclose(AS);
}
