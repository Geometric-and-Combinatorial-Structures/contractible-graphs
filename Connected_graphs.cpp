#include<string.h>
#include<stdio.h>
#include<stdlib.h>

//Maximun number of vertices 
#define MaxN 10

//Maximun number of nodes of tree
#define MaxNod 54

//Maximun number of new graphs   a subset [card(V),card[E]]
//up to 9 vertices
#define MNG 33367


//up to 10 vertices
//#define MNG 1348675

#define pause getchar();


FILE *IF,*OF,*MN,*IF_C,*OF_C; // input and ouput file pointter


//for check errors
int NumeroDeGrafica;

int MaxNumOfNodes=0;
int NivelConMaxNodos=0;

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

double GtoNum(unsigned short int G[MaxN][MaxN],int n){
	double num=0; int i,j;
	for(i=0;i<n-1;i++) for(j=i+1;j<n;j++) num = num*2+G[i][j];
	return num;
}


void read_graph(unsigned short int G[MaxN][MaxN],int *n){
	int i,j;
	fscanf(IF,"%d",n);
	for(i=0;i<*n;i++) for(j=0;j<*n;j++) {fscanf(IF,"%hd",&G[i][j]); }
	fclose(IF);
}

void print_graph(unsigned short int G[MaxN][MaxN],int n){
	int i,j; 
	printf("\nG=\n  _");for(j=0;j<n;j++) printf("%2d ",j);printf("\n");
	for(i=0;i<n;i++) {printf("%2d ",i); for(j=0;j<n;j++) printf("%2d ",G[i][j]); printf("\n");}printf("\n");
}


void print_graphT(unsigned short int G[MaxN][MaxN], int n,int node[2][MaxNod][2][MaxN+1],int oldornew,int nn){// print with new index
	int i,j; 
	printf("\nG=\n - ");for(j=0;j<n;j++) printf("%2d ",node[oldornew][nn][0][j+1]);printf("\n");
	for(i=0;i<n;i++) {printf("%2d ",node[oldornew][nn][0][i+1]);for(j=0;j<n;j++) printf("%2d ",G[node[oldornew][nn][0][i+1]][node[oldornew][nn][0][j+1]]); printf("\n");}//printf("\n");
}

void ch_status2(int node[2][MaxNod][2][MaxN+1], int n,int num){//,int numnodes[2]){
	int i,j;
	for(i=0;i<2;i++) for(j=0;j<n+1;j++) node[0][num][i][j]=node[1][num][i][j];
}

void prtnode(int node[2][MaxNod][2][MaxN+1],int n,int oldornew,int numn){
	int i,j;printf("\n");
	for(i=0;i<2;i++) {for(j=0;j<=n;j++) printf("%2d ",node[oldornew][numn][i][j]);printf("\n");}
}

void cpynode(int node[2][MaxNod][2][MaxN+1],int n,int from , int to){
	int j;
	for(j=0;j<=n;j++){
		node[1][to][0][j]=node[0][from][0][j];
		node[1][to][1][j]=node[0][from][1][j];
	} 
	node[1][to][0][0]=node[0][from][0][0]+1;//level
}

void pullindex(int node[2][MaxNod][2][MaxN+1],int n,int numn,int to,int from){
	int j,temp=node[1][numn][0][from+1], level=node[1][numn][0][0],nsub=node[1][numn][1][0];
	
	for(j=from+1;j>to;j--) node[1][numn][0][j]= node[1][numn][0][j-1];//push forward
	node[1][numn][0][to]=temp;
	if(level>1){
		if ((node[1][numn][1][level]-node[1][numn][1][level-1]>1)) {// vertex is not sigle only
			for(j=nsub+1;j>level;j--) node[1][numn][1][j]=node[1][numn][1][j-1];
	        node[1][numn][1][level]=to-1; 
	        node[1][numn][1][0]++;
	    }	
	}else{
			for(j=nsub+1;j>level;j--) node[1][numn][1][j]=node[1][numn][1][j-1];
	        node[1][numn][1][level]=to-1; 
	        node[1][numn][1][0]++;
	}
}
	
void refpart(unsigned short int G[MaxN][MaxN],int node[2][MaxNod][2][MaxN+1],int n, int numn){
	int i,j,jj,jjj,temp,nsub=node[1][numn][1][0],sum,level=node[1][numn][0][0],from,to;
	int numsubtoref=nsub-level;
	int range[MaxN],nzeros[MaxN],nones[MaxN];
	int updatesubc[MaxN];
	int k;
    // subset partition
	for(i=0;i<numsubtoref;i++){
		from=node[1][numn][1][level+i]+1;
		to=node[1][numn][1][level+1+i]; range[i]=to-from+1;  
		nones[i]=0;
		for(j=from;j<=to && range[i]>1;j++){
			if(G[ node[1][numn][0][level] ] [node[1][numn][0][j+1] ]==0){// there is one 0 
				for(jj=j+1;jj<=to;jj++){//searching for 1
				   if(G[ node[1][numn][0][level] ] [node[1][numn][0][jj+1] ]==1){// there is 1 
				       nones[i]++;
				       temp=node[1][numn][0][jj+1];// save
				       for(jjj=jj;jjj>j;jjj--) node[1][numn][0][jjj+1]=node[1][numn][0][jjj];
				       node[1][numn][0][j+1]=temp;
				       break;
			       }
			    }				
		    } else nones[i]++;
		}
		updatesubc[i]=nones[i];
		}	
	 
    //update subsets of index
	for(i=0,k=0;i<numsubtoref;i++,k+=2){
		nzeros[i]=range[i]-nones[i];  
		if( (range[i]!=1 && range[i]!=nzeros[i] && range[i]!=nones[i]) ){ //vertix not alone	 
	    	for(jjj=node[1][numn][1][0]+1;jjj>level+k;jjj--) node[1][numn][1][jjj+1]=node[1][numn][1][jjj];
	     	node[1][numn][1][level+1+k]=node[1][numn][1][level+k]+updatesubc[i]; 
	    	node[1][numn][1][0]++;	
		}else {
			k--;
		}
	}	
	
}	
	
void calNum(unsigned short int G[MaxN][MaxN],int node[2][MaxNod][2][MaxN+1],int n, int numn,double  num[MaxNod]){	
	int i,j,cc,level=node[1][numn][0][0];
	num[numn]=0;
    for(i=0,cc=0;i<n-1;i++)
	for(j=i+1;j<n;j++,cc++) {
		   num[numn]=num[numn]*2+G[node[1][numn][0][i+1]][node[1][numn][0][j+1]];
	}
}	

void calB(unsigned short int G[MaxN][MaxN],int node[2][MaxNod][2][MaxN+1],long int  B[MaxNod],int n, int numnodes, int level){
	int i,j;
	for(i=1;i<=numnodes;i++){
		B[i]=G[node[1][i][0][level]][node[1][i][0][level+1]];
        for(j=level+1;j<n;j++) B[i]=2*B[i]+G[node[1][i][0][level]][node[1][i][0][j+1]];	
	}   
}

void chooseBestnodes(long int  B[MaxNod],double  num[MaxNod],int numnodes[2],int survnode[2][MaxNod]){
				int survnodeT[MaxNod],keep[MaxNod];
				long int mayor=B[1]; 
				int i,j,nds=0;//survivor node
				for(i=2;i<=numnodes[1];i++)	if(B[i]>mayor) mayor=B[i];	
				//eliminate node with less number Bi
				for(i=1;i<=numnodes[1];i++){
					if(B[i]==mayor){
						survnodeT[nds+1]=i;
						nds++;
					}
				}
				numnodes[1]=nds;
				// eliminate for automorphis
				for(i=1;i<=nds;i++) keep[i]=1;
				//printf("\n automorphism checking");
				for(i=1;i<numnodes[1];i++){
					for(j=i+1;j<=numnodes[1];j++) if(num[survnodeT[i]]==num[survnodeT[j]]){
					   keep[j]=0;
					} 
				}
				survnode[1][1]=survnodeT[1];nds=1;
				for(i=2;i<=numnodes[1];i++){
					if(keep[i]==1) {survnode[1][nds+1]=survnodeT[i];nds++;}
				}//printf("\n the survivors nodes are\n");for(i=1;i<=nds;i++) printf("%d ",survnode[i]);
				numnodes[1]=nds;
}


void GetNamesFiles(int v, char NomArchV[20],char NomArchV1[20]){
	char Nom[20],Nom1[20],Num[10];
	strcpy(Nom,"CG_num_");strcpy(Nom1,"CG_num_");
	sprintf(Num,"%d",v);
	strcat(Nom,Num);
	sprintf(Num,"%d",v+1);
	strcat(Nom1,Num);
	strcat(Nom,".txt");
	strcat(Nom1,".txt");
	strcpy(NomArchV,Nom);
	strcpy(NomArchV1,Nom1);
}

void ReadGraph(unsigned short int G[MaxN][MaxN],int v,int *numG){
	int i,j,n;
	fscanf(IF,"%d",numG);
	for(i=0;i<v;i++){
		for(j=0;j<v;j++){
			fscanf(IF,"%hd",&G[i][j]);
		}
	}
}

void LeerGrafica(unsigned short int G[MaxN][MaxN],int v){
	double numero;
	double Num;
	fscanf(IF,"%lf",&numero);
	fscanf(IF,"%lf",&Num); //printf("\n Lei un %10.0lf",Num);
	NumtoG(Num,G,v);
}





void Copia(double G1[MNG],unsigned short int G2[MaxN][MaxN],int k,int v){
	G1[k]=GtoNum(G2,v);
}

void Copiak(unsigned short int G1[MaxN][MaxN],double  G2[MNG],int k,int v){
	NumtoG(G2[k],G1,v);
}

void Copiakk(double G1[MNG],double G2[MNG],int k,int v){
	 G1[k]=G2[k];
}
void InfError( FILE *A,char letrero[80]){
	if(A==NULL){
		printf("\nError to try to open file   %s   \n \a\a\a CUT ejecution\n\n",letrero);
		pause
	}
}



int CheckIFGareIso(double maximum,int n,double MaxNew[MNG]){
	int j,exist=0;
	for(j=1;j<=n && exist==0;j++){
		if(maximum==MaxNew[j]){
			exist=1;
		}
	}	
	return exist;
}
int RevisaEM(double maximo,int n,double MaxNew[MNG]){
	int j,existe=0;
	for(j=1;j<=n && existe==0;j++){
		if(maximo==MaxNew[j]){
			existe=j;
		}
	}	
	return existe;
}



void addGraphToFile(unsigned short int G[MaxN][MaxN], int n,int numG){
	int i,j; 
	fprintf(OF,"%d\n",numG);
	for(i=0;i<n;i++) {for(j=0;j<n;j++) fprintf(OF,"%d ",G[i][j]); fprintf(OF,"\n");}fprintf(OF,"\n");
	//printf("\n %d",numG);
}


void ch_status(int node[2][MaxNod][2][MaxN+1], int n,int survnode[2][MaxNod],int num){
	int i,j,k;
	for(k=1;k<=num;k++){
		    survnode[0][k]=k;
			for(i=0;i<2;i++){
				for(j=0;j<n+1;j++) {
					node[0][k][i][j]=node[1][survnode[1][k]][i][j];
				}
	        }    
	}
}

void nfvc(unsigned short int G[MaxN][MaxN], int n,int k,int summax[MaxNod][MaxN],int cardg_summax[MaxNod],int gs[MaxNod],int node[2][MaxNod][2][MaxN+1],int oldornew,int numnod,int *maxmax){
	int i,j,kk,grade[MaxN],greater,fp,level=node[0][1][0][0];
	int b=node[0][1][1][level+1];  
	 
	for(kk=1;kk<=numnod;kk++){
		greater=-1,fp=-1;
		for(i=k;i<=b;i++){
			grade[i]=0;              
			for(j=k;j<=b;j++) grade[i]+=G[node[oldornew][kk][0][i+1]][node[oldornew][kk][0][j+1]];
			   if(grade[i]>greater) {
			 	 greater=grade[i];
				 fp=i;
			   }
		} summax[kk][0]=fp;gs[kk]=greater;cardg_summax[kk]=1;
		for(i=fp+1;i<=b;i++){
			if(grade[i]==greater) {
			  summax[kk][cardg_summax[kk]]=i;
			  (cardg_summax[kk])++;		  
			}
		}
    }
    (*maxmax)=-1;
	        for(kk=1;kk<=numnod;kk++){
		      if(gs[kk]>(*maxmax)) (*maxmax)=gs[kk];
            }
}

void eliminateBgen(int survnode[2][MaxNod],int gs[MaxN],int maxmax,int numnodes[2]){
			int j,sn=0;
			for(j=1;j<=numnodes[0];j++){
				if(gs[j] ==maxmax){
					survnode[0][sn+1]=j;
					sn++;
				}  
			}
			numnodes[0]=sn;
}

int cal_canonicalform(unsigned short int G[MaxN][MaxN],int n, double *NumMax,unsigned short int CFG[MaxN][MaxN]){
	int level;
	int node[2][MaxNod][2][MaxN+1];
	int i,j,ii,jj,k;
	int Stop=0;
	int places[MaxNod][MaxN],dimplaces[MaxNod]; // places of neibors to choose vertex, his dimention
	int gs[MaxNod];
	int nneib; // numer of neibors
	int numnodes[2]; // number of nodes  0: last level 1: new level

	int survnode[2][MaxNod]; // survivor  nodes  0: old   1: new
	int maxmax;
		
	double Num[MaxNod],temp,best;
	long int  B[MaxNod];	
	int allarefix;	
		
	//Root node
	level=0; 
	node[1][1][0][0]=level;
	for(j=0;j<n;j++) node[1][1][0][j+1]=j;//index
	node[1][1][1][0]=1;// number of nodes of level
	node[1][1][1][1]=n-1;// until last one
	for(j=2;j<=n;j++) node[1][1][1][j]=0;
    numnodes[1]=1;               
	//prtnode(node,n,1,1);getch();
	survnode[1][1]=1;numnodes[1]=1;
    ch_status(node,n,survnode,numnodes[1]); numnodes[0]=numnodes[1];
    

    for(level=1;level<n && Stop==0;level++){
			for(i=1;i<=numnodes[1];i++) ch_status(node,n,survnode,numnodes[1]);
			numnodes[0]=numnodes[1];
			// next follow vextex candidate
		    nfvc(G,n,level-1,places,dimplaces,gs,node,0,numnodes[0],&maxmax);
		    
		    //eliminate by minus first part of Blevel before to generate
	       if(level>1) eliminateBgen(survnode,gs,maxmax,numnodes);	   
			numnodes[1]=0;
			for(i=1;i<=numnodes[0];i++){//for each old node
			   for(j=1;j<=dimplaces[survnode[0][i]];j++){
			   	  numnodes[1]++;
			   	  if(numnodes[1]>MaxNumOfNodes) MaxNumOfNodes=numnodes[1];
			   	  if(numnodes[1]>=MaxNod){
			   	     	printf("\nProblem MaxNod must be incresed    at the beginning of source code\n\n");
			   	     	pause
			   	     	return 1;
				  }
			   	  
			   	  cpynode(node,n,survnode[0][i],numnodes[1]);// from (old) to (new)
			      pullindex(node,n,numnodes[1],level,places[survnode[0][i]][j-1]); // ... int numn,int to,int from   	
			      refpart(G,node,n,numnodes[1]);//numn
			      calNum(G,node,n,numnodes[1],Num); 
			   }
			}
			
	        calB(G,node,B,n,numnodes[1],level); 
	        chooseBestnodes(B,Num,numnodes,survnode);
	        
	        // check if all nodes are fixed
	        allarefix=1;
		    for(i=1;i<=numnodes[1] && allarefix==1;i++){
		    	if(node[1][survnode[1][i]][1][0]<n) allarefix=0;
			}
	        if(allarefix==1){
	        	Stop=1;
	        	if(numnodes[1]==1){
	        		(*NumMax)=Num[survnode[1][1]];
	        		for(ii=0;ii<n;ii++) for(jj=0;jj<n;jj++) CFG[ii][jj]=G[node[1][survnode[1][1]][0][ii+1]][node[1][survnode[1][1]][0][jj+1]];
				}else{
					
				   best=-1;
			       for(i=1;i<=numnodes[1];i++){
			    	  if(Num[survnode[1][i]]>best) {
			    	       best=Num[survnode[1][i]];	
			    	       k=survnode[1][i];
					  }
				   }
				  (*NumMax)=best;	
				  for(ii=0;ii<n;ii++) for(jj=0;jj<n;jj++) CFG[ii][jj]=G[node[1][k][0][ii+1]][node[1][k][0][jj+1]];
				}
			}			
	}
	return 0;
}




int main(){
	char NomArchV[20],NomArchVm1[20];
	int i,j,k,p,q,v,V,A,a,AA,ng,nGnew,nGold;
	unsigned short int Gcand[MaxN][MaxN],Gfcm[MaxN][MaxN];
	double Gold[MNG],Gnew[MNG];
	
	int NumGant=1;	//first grap is done    ( k(1)   )
    int N=9;
    
    int donde,agrega;
    double maximo;
    double MaxNew[MNG],MaxOld[MNG];
    
    OF=fopen("CG_num_1.txt","w");fprintf(OF,"1\n1 0\n1\n0");fclose(OF);
    
    MN=fopen("MaxNumLC_CG.txt","w");
    fprintf(MN,"    %d  %d  %d          %d\n",1,1,0,0);

    for(V=1;V<=N-1;V++){
		GetNamesFiles(V, NomArchV,NomArchVm1); //Names of files to save praphs numbers by  [v,e]
	    IF=fopen(NomArchV,"r");	
	    OF=fopen(NomArchVm1,"w");
	    if(IF==NULL){
	    	printf("\n troubleshootings with %s file",NomArchV); pause return 1;	
		}
		//Add edges 
		for(AA=V;AA<=(V+1)*V/2;AA++){
			    nGnew=0; // Number of new graphs
			    //Add vertex and edge
			    if(AA<=V*(V-1)/2+1){
			    		 fscanf(IF,"%d %d %d",&ng,&v,&a);
			    		 for(k=1;k<=ng;k++){ // For each graph of [v,e]
						 		 //Get candidate graph
					    		 LeerGrafica(Gcand,v);
					    		 for(i=0;i<V+1;i++){// Add row & column
					    		 	Gcand[i][V]=0;
					    		 	Gcand[V][i]=0;
								 }
					    		 for(i=V-1;i>=0;i--){
					    		 	 Gcand[i][V]=1;Gcand[i+1][V]=0;	// Delete old 1 & get new one
					    		 	 Gcand[V][i]=1;Gcand[V][i+1]=0;
					    		 	 cal_canonicalform(Gcand,V+1,&maximo,Gfcm);
					    		 	 if(RevisaEM(maximo,nGnew,MaxNew)==0){
					    		 	 	 //Here a new graph is generated
					    		 	 	 // stored in Gcand    or   GFcm   (canonical form)
										 //adyacence Matrix     
//*****************************************************************************
										 
					    		 		 nGnew++;					    		 						    	
										 //Copia(Gnew,Gfcm,nGnew,V+1);// for save in canonical form (number) 	 		 
					    		 		 Copia(Gnew,Gcand,nGnew,V+1);
					    		 		 MaxNew[nGnew]=maximo;
					    		 		 fprintf(MN,"%5d %2d %2d %10.0lf\n",NumGant+nGnew,V+1,AA,maximo);
									 }
								 }
						} 
				}
		        //Add new edge only
			    if(AA>V){
		    		    for(k=1;k<=nGold;k++){
		    		    	Copiak(Gcand,Gold,k,V+1);// Get candidate graph
			    		    //Add edge
				    		for(i=0;i<=V;i++){  //Upper left corner 
				    			for(j=i+1;j<=V;j++){ 
				    				if( Gcand[i][j]==0){
				    					Gcand[i][j]=1;
				    					Gcand[j][i]=1; 
	  				    		 	    cal_canonicalform(Gcand,V+1,&maximo,Gfcm);
						    		 	 if(RevisaEM(maximo,nGnew,MaxNew)==0){
						    		 	 	 //Here a new graph is generated
					    		 	 	     // stored in Gcand    or   GFcm   (canonical form)
										     //adyacence Matrix 
//*****************************************************************************										     

						    		 		 nGnew++;					    		 						    		 		 
						    		 		 //Actualice new graphs
						    		 		 //Copia(Gnew,Gfcm,nGnew,V+1);// for save in canonical form (number)
						    		 		 Copia(Gnew,Gcand,nGnew,V+1);
						    		 		 MaxNew[nGnew]=maximo;
						    		 		 fprintf(MN,"%5d %2d %2d %10.0lf\n",NumGant+nGnew,V+1,AA,maximo);
						    		 		 //printf("%d %d %d %10.0lf\n",NumGant+nGnew,V+1,AA,maximo);
										 }
				    					Gcand[i][j]=0;// Let candidate graph like new
				    					Gcand[j][i]=0;
									}
								}
							}
						}
					}
					
					// Save new graphs to memory & file
					for(k=1;k<=nGnew;k++) Copiakk(Gold,Gnew,k,V+1);
					nGold=nGnew;
					fprintf(OF,"%d\n", nGnew);
					fprintf(OF,"%d %d\n\n",V+1,AA);
					for(k=1;k<=nGnew;k++){
						fprintf(OF,"%d ",NumGant+k);
						fprintf(OF,"%1.0lf\n",Gnew[k]);
					} fprintf(OF,"\n");
					NumGant+=nGnew;
		}
	    fclose(IF);
	    fclose(OF);	
	}
	
	fclose(MN);
	printf("MaxNumOfNodes=%d",MaxNumOfNodes);
    return 0;
}

