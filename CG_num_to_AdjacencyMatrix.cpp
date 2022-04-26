#include<string.h>
#include<stdio.h>
#include<stdlib.h>

//Maximun number of vertices 
#define MaxN 10
//
////Maximun number of nodes of tree
//#define MaxNod 70
//
////Maximun number of new graphs   a subset [card(V),card[E]]
//#define MNG 85000
//
#define pause system("pause");

FILE *IF,*OF,*MN;

void NumtoG(double Num,unsigned short int G[MaxN][MaxN],int n){
	int i,j,d,res;
	long long int temp=Num;
    for(i=n-2;i>=0;i--){
    	G[i][i]=0;
    	for(j=n-1;j>i;j--){
    		G[i][j]=temp%2; temp/=2; G[j][i]=G[i][j];
		}
	} G[n-1][n-1]=0;
}



void print_graph_to_F(unsigned short int G[MaxN][MaxN],int n){
	int i,j; 
	for(i=0;i<n;i++) { for(j=0;j<n;j++) fprintf(OF,"%d ",G[i][j]); fprintf(OF,"\n");}fprintf(OF,"\n");
}


void GetNamesFiles(int v, char NomArchV[20],char NomArchV1[20]){
	char Nom[20],Nom1[20],Num[10];
	strcpy(Nom,"CG_num_");strcpy(Nom1,"CG_AM_");
	sprintf(Num,"%d",v);
	strcat(Nom,Num);
	sprintf(Num,"%d",v);
	strcat(Nom1,Num);
	strcat(Nom,".txt");
	strcat(Nom1,".txt");
	strcpy(NomArchV,Nom);
	strcpy(NomArchV1,Nom1);
}




int main(){
	char NomArchV[20],NomArchVm1[20];
	unsigned short int G[MaxN][MaxN],Gfcm[MaxN][MaxN];
	
    int N=9; // Max number of vertexs
        
    long int numg;
    double number;
    int k,ng,v,a,V,E;
    
    MN=fopen("SubSets_graphsD.txt","w");
    for(V=1;V<=N;V++){
		GetNamesFiles(V, NomArchV,NomArchVm1); //Names of files to save graphs numbers by [v,e]
	    IF=fopen(NomArchV,"r");	
	    OF=fopen(NomArchVm1,"w");
	    if(IF==NULL){
	    	printf("\n troubleshootings with %s file",NomArchV); pause return 1;	
		}
		for(E=V-1;E<=(V-1)*V/2;E++){
			  fscanf(IF,"%d %d %d",&ng,&v,&a); 
			  fprintf(MN,"%d %d %d\n",v,a,ng);
			  fprintf(OF,"%d \n%d %d\n\n",ng,v,a);
			  for(k=1;k<=ng;k++){ // For each graph of [v,e]
			        fscanf(IF,"%d",&numg);
			        fscanf(IF,"%lf",&number);
			        NumtoG(number,G,V);
			        fprintf(OF,"%d\n",numg);      
			        print_graph_to_F(G,V);
		      }
		}
		fprintf(MN,"\n");
	    fclose(IF);
	    fclose(OF);	
	}
	
	fclose(MN);
    return 0;
}
