#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//Max number of vertices
#define MaxN 10

//Max number of rows
#define MaxNumRen 513

FILE *IF,*OF;


#define pause system("pause");



void read_graph(unsigned short int G[MaxN][MaxN],int *n){
	int i,j;
	fscanf(IF,"%d",n);
	for(i=0;i<*n;i++) for(j=0;j<*n;j++) {fscanf(IF,"%d",&G[i][j]); }
	fclose(IF);
}

void print_graph(unsigned short int G[MaxN][MaxN],int n){
	int i,j; 
	printf("\nG=\n  _");for(j=0;j<n;j++) printf("%2d ",j);printf("\n");
	for(i=0;i<n;i++) {printf("%2d ",i); for(j=0;j<n;j++) printf("%2d ",G[i][j]); printf("\n");}printf("\n");
}

void print_graph_to_F(unsigned short int G[MaxN][MaxN],int n){
	int i,j; 
	fprintf(OF,"\n");
	for(i=0;i<n;i++) { for(j=0;j<n;j++) fprintf(OF,"%d ",G[i][j]); fprintf(OF,"\n");}fprintf(OF,"\n");
}

void GetNamesFiles(int v, char NomArchV[30],char NomArchV1[30]){
	char Nom[30],Nom1[30],Num[10];
	strcpy(Nom,"CG_num_");strcpy(Nom1,"Contractible_graphs_");
//	strcpy(Nom,"V");strcpy(Nom1,"V");	
	sprintf(Num,"%d",v);
	strcat(Nom,Num);
	sprintf(Num,"%d",v);
	strcat(Nom1,Num);

	strcat(Nom,".txt");
	strcat(Nom1,".txt");
	//printf("\n%s   %s",Nom,Nom1);
	strcpy(NomArchV,Nom);
	strcpy(NomArchV1,Nom1);
}



//Calculate grades of vertices
void CalVal(unsigned short int A[MaxN][MaxN],  int n,unsigned short int Val[MaxN]){
	unsigned short int i,j;
	for(i=0;i<n;i++){
        Val[i]=0;
        for(j=0;j<n;j++) if(A[i][j]==1) Val[i]++;
	}
}



//Calcuate neighborhood of v_i  
void CalLk(unsigned short int A[MaxN][MaxN],  int n,unsigned short int Val[MaxN], int k,
           unsigned short int Lk[MaxN][MaxN], int *m){
	unsigned short int i,j;
	unsigned short int Isobre[MaxN];
	unsigned short int Cont=0;
	*m=Val[k];
	for(j=0;j<n;j++) {
		if(A[k][j]==1) {
		  Isobre[Cont]=j;
		  Cont++;	
		}
	}
	
	for(i=0;i<*m;i++){
		for(j=0;j<*m;j++){
			Lk[i][j]=A[Isobre[i]][Isobre[j]];
		}
	}
}


//Delete vertex of graph
void EliminaVert(unsigned short int A[MaxN][MaxN],  int n, int k,unsigned short int B[MaxN][MaxN], int *m){
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


// Recursive function to verify if G \in I or not
unsigned short int BtoI(unsigned short int G[MaxN][MaxN],int n){
	int i,m;
	unsigned short int Val[MaxN];
    unsigned short int Lk[MaxN][MaxN];
   // unsigned short int ValLk[MaxN];
	unsigned short int GmV[MaxN][MaxN];//,EtGmV[N];
	
    if(n==0 || n==1) {
	  return n;	
	}
    else{
        //Try to delete some vertex
        for(i=0;i<n;i++){
            //Calcuate neighborhood of v_i   
			CalVal(G,n,Val); //grades
			CalLk(G,n,Val,i,Lk,&m);
			if(BtoI(Lk,m)==1){
			  	  EliminaVert(G,n,i,GmV,&m);
			  	  return BtoI(GmV,m);
			}	
		}
		//If cannot eliminate vertices return 0
		return 0;
	}	
}


void GenConjPot( int n, unsigned short int P[MaxNumRen][MaxN], int Card[MaxNumRen]){
	short int I[MaxN],j;
	int k=0;

    if(n>=0){
    	P[0][0]=-1;Card[0]=0;
	}

    if(n>=1){
    	//vertices
		for(I[0]=0;I[0]<n;I[0]++) {
			k++; P[k][0]=I[0];Card[k]=1;
		}
	}
 
    if(n>=2){
    	//edges
		for(I[0]=0;I[0]<n;I[0]++) {
			for(I[1]=I[0]+1;I[1]<n;I[1]++) {
				k++; P[k][0]=I[0];P[k][1]=I[1];Card[k]=2;
	        }
	    }
	}
	
	if(n>=3){
	    //triangles K(3)
		for(I[0]=0;I[0]<n;I[0]++) {
		 for(I[1]=I[0]+1;I[1]<n;I[1]++) {
		  for(I[2]=I[1]+1;I[2]<n;I[2]++) {
				 k++; for(j=0;j<3;j++) P[k][j]=I[j];Card[k]=3;
		  }
	     }	
	    }
	}
	
	if(n>=4){
        //K(4)
		for(I[0]=0;I[0]<n;I[0]++) {
		 for(I[1]=I[0]+1;I[1]<n;I[1]++) {
		  for(I[2]=I[1]+1;I[2]<n;I[2]++) {
		  	for(I[3]=I[2]+1;I[3]<n;I[3]++) {
				 k++; for(j=0;j<4;j++) P[k][j]=I[j];Card[k]=4;
		    }
		  }
	     }
	    }		
	}
	
	if(n>=5){
	    //K(5)
		for(I[0]=0;I[0]<n;I[0]++) {
		 for(I[1]=I[0]+1;I[1]<n;I[1]++) {
		  for(I[2]=I[1]+1;I[2]<n;I[2]++) {
		  	for(I[3]=I[2]+1;I[3]<n;I[3]++) {
		  		for(I[4]=I[3]+1;I[4]<n;I[4]++) {
				  k++; for(j=0;j<5;j++) P[k][j]=I[j];Card[k]=5;
			    }
		    }
		  }
	     }
	    }		
	}

    if(n>=6){
	    //K(6)
		for(I[0]=0;I[0]<n;I[0]++) {
		 for(I[1]=I[0]+1;I[1]<n;I[1]++) {
		  for(I[2]=I[1]+1;I[2]<n;I[2]++) {
		  	for(I[3]=I[2]+1;I[3]<n;I[3]++) {
		  		for(I[4]=I[3]+1;I[4]<n;I[4]++) {
		  			for(I[5]=I[4]+1;I[5]<n;I[5]++) {
				     k++; for(j=0;j<6;j++) P[k][j]=I[j];Card[k]=6;
			      }
			    }
		    }
		  }
	     }
	    }    	
	}
	
	if(n>=7){
		//K(7)
		for(I[0]=0;I[0]<n;I[0]++) {
		 for(I[1]=I[0]+1;I[1]<n;I[1]++) {
		  for(I[2]=I[1]+1;I[2]<n;I[2]++) {
		  	for(I[3]=I[2]+1;I[3]<n;I[3]++) {
		  		for(I[4]=I[3]+1;I[4]<n;I[4]++) {
		  			for(I[5]=I[4]+1;I[5]<n;I[5]++) {
		  				for(I[6]=I[5]+1;I[6]<n;I[6]++) {
		  				  k++; for(j=0;j<7;j++) P[k][j]=I[j];Card[k]=7;
			            
			          }
			      }
			    }
		    }
		  }
	     }
	    } 		
	}
	
	if(n>=8){
	    //k(8)
		for(I[0]=0;I[0]<n;I[0]++) {
		 for(I[1]=I[0]+1;I[1]<n;I[1]++) {
		  for(I[2]=I[1]+1;I[2]<n;I[2]++) {
		  	for(I[3]=I[2]+1;I[3]<n;I[3]++) {
		  		for(I[4]=I[3]+1;I[4]<n;I[4]++) {
		  			for(I[5]=I[4]+1;I[5]<n;I[5]++) {
		  				for(I[6]=I[5]+1;I[6]<n;I[6]++) {
		  				 for(I[7]=I[6]+1;I[7]<n;I[7]++) {	
				          k++; for(j=0;j<8;j++) P[k][j]=I[j];Card[k]=8;
			            }
			          }
			      }
			    }
		    }
		  }
	     }
	    } 		
	}
	
	if(n>=9){
	    //k(9)
		for(I[0]=0;I[0]<n;I[0]++) {
		 for(I[1]=I[0]+1;I[1]<n;I[1]++) {
		  for(I[2]=I[1]+1;I[2]<n;I[2]++) {
		  	for(I[3]=I[2]+1;I[3]<n;I[3]++) {
		  		for(I[4]=I[3]+1;I[4]<n;I[4]++) {
		  			for(I[5]=I[4]+1;I[5]<n;I[5]++) {
		  				for(I[6]=I[5]+1;I[6]<n;I[6]++) {
		  				 for(I[7]=I[6]+1;I[7]<n;I[7]++) {	
		  				  for(I[8]=I[7]+1;I[8]<n;I[8]++) {
				            k++;  for(j=0;j<9;j++) P[k][j]=I[j];Card[k]=9;
			              }
			            }
			          }
			      }
			    }
		    }
		  }
	     }
	    }		
	}
	
	if(n>=10){
	    //k(10)
		for(I[0]=0;I[0]<n;I[0]++) {
		 for(I[1]=I[0]+1;I[1]<n;I[1]++) {
		  for(I[2]=I[1]+1;I[2]<n;I[2]++) {
		  	for(I[3]=I[2]+1;I[3]<n;I[3]++) {
		  		for(I[4]=I[3]+1;I[4]<n;I[4]++) {
		  			for(I[5]=I[4]+1;I[5]<n;I[5]++) {
		  				for(I[6]=I[5]+1;I[6]<n;I[6]++) {
		  				 for(I[7]=I[6]+1;I[7]<n;I[7]++) {	
		  				  for(I[8]=I[7]+1;I[8]<n;I[8]++) {
		  				  	for(I[9]=I[8]+1;I[9]<n;I[9]++) {
					            k++; for(j=0;j<10;j++) P[k][j]=I[j];Card[k]=10;
			                }
			              }
			            }
			          }
			      }
			    }
		    }
		  }
	     }
	    } 		
	}
	
}

int VsonKn(int np,unsigned short int P[MaxNumRen][MaxN], int Card[MaxNumRen],unsigned short int G[MaxN][MaxN]){
	short int i,j,esta=1;
	for(i=0;i<Card[np] && esta==1;i++){
		for(j=i+1;j<Card[np] && esta==1;j++){
			if(G[P[np][i]][P[np][j]]==0) esta=0;
	    }
	}
	return esta;
}

void CalDeltaDeG(unsigned short int Nv,unsigned short int P[MaxNumRen][MaxN], int Card[MaxNumRen], unsigned short int I_DG[MaxNumRen], int *NumSim,unsigned short int G[MaxN][MaxN]){
  int i,k;
  //El vacio y los vertices forman parte de Delta(G)
  for(i=0;i<=Nv;i++) I_DG[i]=i;
  k=Nv; 
  *NumSim=Nv+1;
  for(i=Nv+1; i < pow(2,Nv);i++){
  	  if(VsonKn(i,P,Card,G)==1) {
		  k++;	I_DG[k]=i;(*NumSim)++;
		}
  } 
}

int AsubB(int i,int i2,unsigned short int I_DG[MaxNumRen],unsigned short int P[MaxNumRen][MaxN],int Card[MaxNumRen]){
	int j1,j2,es=1,pertenece;
	for(j1=0;j1<Card[I_DG[i]]&&es==1;j1++){
	  pertenece=0;	
	  for(j2=0;j2<Card[I_DG[i2]]&&pertenece==0;j2++){
		if(P[I_DG[i]][j1]==P[I_DG[i2]][j2]) pertenece=1;
	  }	
	  if(pertenece==0) es=0;
	}
	return es;
}

void CalCont(unsigned short int I_DG[MaxNumRen], int NumSim,unsigned short int P[MaxNumRen][MaxN], int Card[MaxNumRen],unsigned short int Contencion[MaxNumRen][MaxNumRen],unsigned short int DimCont[MaxNumRen]){
 int i,i2,j,k;
 //Begin values zero
 for(i=0;i<NumSim;i++){
   DimCont[i]=0;	
   for(j=0;j<NumSim;j++){
      Contencion[i][j]=0;	
   }	
 }
 //Empty set
 DimCont[0]=NumSim;
 for(j=0;j<NumSim;j++) {
   Contencion[0][j]=1;
 }
 // the rest
 for(i=1;i<NumSim;i++){
 	for(k=i+1;k<NumSim && Card[I_DG[k]]==Card[I_DG[i]];k++);
	for(i2=k;i2<NumSim;i2++){
		if(AsubB(i,i2,I_DG,P,Card)==1){
              DimCont[i]++;
              Contencion[i][i2]=1;
		}
	} 
 }	
}
 	
int LocalizaPL(unsigned short int I_DG[MaxNumRen], int Card[MaxNumRen],unsigned  short int Contencion[MaxNumRen][MaxNumRen],unsigned short int DimCont[MaxNumRen],unsigned short int Vive[MaxNumRen], int NumSim,unsigned short int PL[2]){	  	
	int hay=0,i,i2,ya;
	for(i=NumSim-1;i>=1 && hay==0;i--){
		if(Vive[i]==1){
			if(DimCont[i]==1){
				ya=0;
				for(i2=NumSim-1;i2>=1 && ya==0;i2--){
					if(Vive[i2]==1){
						if(Contencion[i][i2]==1){
						  ya=1;
						  PL[1]=i2;
					    }
					}
				}
				if(ya==1 && DimCont[PL[1]]==0 && (Card[I_DG[i]]+1==Card[I_DG[PL[1]]])){
					hay=1;
					PL[0]=i;
				}
			}
		}
	}
	return hay;
}


int BtoColl(unsigned short int G[MaxN][MaxN], int n,unsigned short int P[MaxNumRen][MaxN], int Card[MaxNumRen]){
	int NumSim;//Number of Simplex
	unsigned short int I_DG[MaxNumRen]; // Index of delta of Graph
	unsigned short int Contencion[MaxNumRen][MaxNumRen],DimCont[MaxNumRen];
	int i,k,NumSobre,ExistenPL; 
	unsigned short int Vive[MaxNumRen];
	unsigned short int PL[2]; //Pair FRee
	CalDeltaDeG(n,P,Card,I_DG,&NumSim,G); 
	CalCont(I_DG,NumSim,P,Card,Contencion,DimCont);
    NumSobre=NumSim;
    for(i=0;i<NumSim;i++) Vive[i]=1;
	do{
       ExistenPL=0;
 
	   if(LocalizaPL(I_DG,Card,Contencion,DimCont,Vive,NumSim,PL)==1){
	   	  ExistenPL=1;
          Vive[PL[0]]=0;
          Vive[PL[1]]=0;
          NumSobre-=2;
          for(k=0;k<NumSim;k++){
          	 if(Contencion[k][PL[0]]==1){
          	 	Contencion[k][PL[0]]=0;
          	 	DimCont[k]--;
			 }
			 if(Contencion[k][PL[1]]==1){
          	 	Contencion[k][PL[1]]=0;
          	 	DimCont[k]--;
			 }
          }
	   }	
	}while(ExistenPL==1);
    
	if(NumSobre<=2)	return 1; else return 0;
}

   	

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




int main(){
	char NomArchV[30],NomArchVm1[30];
	unsigned short int G[MaxN][MaxN],Gfcm[MaxN][MaxN];
	unsigned short int P[MaxNumRen][MaxN];
	int Card[MaxNumRen];
	
    int N=9; // Max number of vertexs
    
    
    long int numg;
    double number;
    int V,E,ng,v,a,k;
    
    int BI,BC;
    

    for(V=1;V<=N;V++){
		GetNamesFiles(V, NomArchV,NomArchVm1); //Names of files to save graphs numbers by [v,e]
	    IF=fopen(NomArchV,"r");	
	    OF=fopen(NomArchVm1,"w");
	    if(IF==NULL){
	    	printf("\nThere is a problem with the file %s", NomArchV); pause return 1;	
		}
		GenConjPot(V,P,Card);
		for(E=V-1;E<=(V-1)*V/2;E++){
			  fscanf(IF,"%d %d %d",&ng,&v,&a); 
	//		  fprintf(MN,"%d %d %d\n",ng,v,a);
	//		  fprintf(OF,"%d\n%d %d\n",ng,v,a);
			  for(k=1;k<=ng;k++){ // For each graph of [v,e]
			        fscanf(IF,"%d",&numg);
			        fscanf(IF,"%lf",&number);
			        NumtoG(number,G,V);
			        
			        
			        BI=BtoI(G,V);
			        BC=BtoColl(G,V,P,Card);
			        if( BI==1 && BC==1){
			        	fprintf(OF,"%d %d %d",numg,v,a);
			        	print_graph_to_F(G,V);
					}
					
					
					 //fprintf(OF,"%d\n",numg);  

                    if( BI==0 && BC==1){
                    	//apparently this situation does not happen
                    	printf("\nCollapsible and not contractible graph found! (a counterexample)");
                    	pause
                    	return 1;
					} 		
					if( BI==1 && BC==0){
                    	//this situation does not happen
                    	printf("\nSomething is wrong!");
                    	pause
                    	return 2;
					}	       
		      }
		}
	    fclose(IF);
	    fclose(OF);
	}
    return 0;
}
