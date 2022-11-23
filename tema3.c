#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

//am creat o structura care salveaza capetele arcului si costul

typedef struct arc {
  int u, v;
  float w;
} arc;

//algoritm de parcurgere a grafului 
//salveaza toate nodurile in care se poate ajunge din nodul x

void dfs1(int x, float mat[MAX][MAX], int *s, int n)
{
	int i;
    s[x] = 1;
    for(i = 0 ; i < n ; i++)
        if(s[i] == 0 && mat[x][i] != 0)
        	{
            	dfs1(i, mat, s, n);
        	}
}

//salveaza toate nodurile din care se poate ajunge in nodul x

void dfs2(int x, float mat[MAX][MAX], int *p, int n)
{
	int i;
    p[x] = 1;
    for(i = 0 ; i < n ; i++)
        if(p[i] == 0 && mat[i][x] != 0)
            dfs2(i, mat, p, n);
}

//algoritm pentru determinarea drumului de cost minim

void dijkstra(float mat[MAX][MAX],int n,int startnode, int lastnode)

{
	int succesor[MAX];
    float cost[MAX][MAX],distance[MAX];
	int predecesor[MAX];
    int visited[MAX],count,mindistance,nextnode,i,j,k;
    
    //initializarea matricii de cost 
    
    for(i=0;i<n;i++)
    	for(j=0;j<n;j++)
			{
				if(mat[i][j]==0)
					cost[i][j]=99999;
				else
					cost[i][j]=mat[i][j];
			}
			
	//initializarea predecesorului cu nodul de start
	//initializarea distantelor de la nodul de start catre toate nodurile
	//initializarea cu 0 a vectorului de noduri vizitate
			
	for(i=0;i<n;i++)
		{
			distance[i]=cost[startnode][i];
			predecesor[i]=startnode;
			visited[i]=0;
		}
		
	distance[startnode]=0;
    visited[startnode]=1;
    count=1;
    
    
    while(count<n-1)
   		{
   			//initializam distanta minima cu un numar mai mare decat orice cost
			mindistance=99999;
			
			//verificam daca distanta intre nodul de start si nodul i e mai mica
			//verificam daca s-a mai trecut prin nodul i
			
			for(i=0;i<n;i++)
				if(distance[i]<mindistance&&!visited[i])
					{
						mindistance=distance[i];
						nextnode=i;
					}
					
	//se marcheaza nodul i ca vizitat

    visited[nextnode]=1;
    
    //se verifica daca distanta nou calculata pentru fiecare nod este mai mica decat cea precedenta
    //pred salveaza nodurile prin care s-a trecut pentru a ajunge la distanta minima
    
    for(i=0;i<n;i++)
		if(!visited[i])
			if(mindistance+cost[nextnode][i]<distance[i])
				{
					distance[i]=mindistance+cost[nextnode][i];
					predecesor[i]=nextnode;
				}

    count++;
		}

    j=lastnode;
	k = 0;
    
    //pentru afisare salvez nodurile in ordinea succesiva
    
	do
	    {
	    	j=predecesor[j];
	    	succesor[k] = j;
	    	k++;
	    }while(j!=startnode);

	for(j=k-1; j>=0; j--)
		printf("%d " , succesor[j]);
}

int main()

{
	arc arce[MAX];
	char id[3];
	float mat[MAX][MAX];
	int depozite[MAX];
	int n,m,d,i,j,ex,u,v,s,l,x;
	int mag[MAX];
	scanf("%d", &n);
	scanf("%d", &m);
	scanf("%d", &d);
	
	//se citesc datele de intrare in formatul specificat
	//salvez detaliile muchilor intr-un vector de structuri
	
	for(i=0; i<m; i++)
		{
			scanf("%d", &arce[i].u);
			scanf("%d", &arce[i].v);
			scanf("%f", &arce[i].w);
		}
		
	//salvez depozitele intr-un vector 
		
	for(i=0; i<d; i++)
		{
			scanf("%d", &depozite[i]);
		}
		
	//se creeaza matricea de adiacenta	
		
	for(i=0; i<n; i++)
		{
			for(j=0; j<n; j++)
				{
					mat[i][j] = 0;
				}
		}
		
	for(i=0; i<m; i++)
		{
			u=arce[i].u;
			v=arce[i].v;
			mat[u][v]=arce[i].w;	
		}
		
	scanf("%d", &ex);
	for(x=1; x<=ex; x++)
	{	
		scanf("%s", id);
		if(strcmp(id, "e1") == 0)
			{
				int a,k;
				float suma=0;
				scanf("%d", &s);
				scanf("%d", &k);
				for(i=0; i<k; i++)
					{
						scanf("%d", &mag[i]);
					}
			    float m[MAX][MAX];
			    
			    //algoritm de determinare a distantelor minime
			    //distantele sunt salvate intr-o matrice de costuri minime
			    
			    for(i = 0; i < n; i++)
			        for(j = 0; j < n ; j++)
						{
				            if(mat[i][j] != 0 ||  i == j)
				                m[i][j] = mat[i][j];
				            else
				                m[i][j] = 99999;
				        }
			    for(l = 0; l < n; l++)
			        for(i = 0; i < n; i++)
			            for(j = 0; j < n; j++)
			                if(m[i][j] > m[i][l] + m[l][j])
			                    m[i][j] = m[i][l] + m[l][j];
			                    
			    //valorile minime sunt afisate din matrice
				//drumurile sunt afisate prin functia dijkstra                
			                    
				for(i=0; i<k; i++)
			    {	
					a = mag[i];
			    	printf("%d\n" , mag[i]);
			    	printf("%.1f %.1f\n", m[s][a] , m[a][s]);
			    	suma = suma+m[s][a]+m[a][s];
			    	dijkstra(mat,n,s,a);
			    	dijkstra(mat,n,a,s);
			    	printf("%d",s);
					printf("\n");
				}
				printf("%.1f", suma);
				if(x!=ex) 
					printf("\n");

			}
		if(strcmp(id, "e2") == 0)

			{
				int ok=0,spatiu=0,anterior;
				for(i=0; i<d; i++)
					{
						//marchez cu 0 toate drumurile catre si din spre depozite
						
						int y;
						y = depozite[i];
						for(j=0; j<n; j++)
							{
								mat[j][y] = 0;
								mat[y][j] = 0;
							}
					}
				int *s = malloc(n * sizeof(int));
				int *p = malloc(n * sizeof(int));
				int nrcom = 0;
				
				//vectorul ctc marcheaza din ce componenta conexa face parte fiecare nod
				
				int ctc[MAX];
				for(i = 0 ; i < n; i++)
					{
						ctc[i] = 0;
					}


				for(i = 0 ; i < n; i++)
				{	
					for(l=0; l<d; l++)
						{
							if(i == depozite[l])
								ok=1;
						}
					if(ctc[i] == 0 && ok==0)
        				{
          					for(j = 0; j < n ; j++)
               					{
									s[j] = 0;
									p[j] = 0;
								}
							nrcom++;
							
					//se verifica fiecare nod in parte cu ce alte noduri este componenta tare conexa
					
							if(ok==0)
								{
									dfs1(i, mat, s, n);
									dfs2(i, mat, p, n);
									for(j = 0; j < n ; j++)
										if(s[j] == 1 && p[j] == 1)
											ctc[j] = nrcom;
								}
							
        				}
					ok=0;
        		}
        		printf("%d\n" , nrcom);	
				ok=0;	
				
				//afisez pe rand fiecare nod din fiecare componenta tare conexa
				
        		for(i = 1; i <= nrcom; i++)
        			{
        				for(j=0; j<n; j++)
        					{
        						if(ctc[j] == i)
									{
										if(ok==0 && spatiu!=0 && j!=anterior)
													{
													printf(" ");
													printf("%d", j);
													spatiu++;
													anterior=j;}
										else if(ok==0 && spatiu==0)
													{printf("%d" , j);
													spatiu++;
													anterior=j;}
									}
							}
						anterior=100;
						if(i<nrcom && spatiu!=0)	
							printf("\n");
						ok=0;
						spatiu = 0;
					}
				free(s);
				free(p);
			}
		if(strcmp(id, "e3") == 0)
			{
				int r, contor1[MAX],contor2[MAX],ok=0;
				float costuri[MAX];
				for(i=0; i<d; i++)
					{
						contor1[i] = 0;
						contor2[i] = 0;
						costuri[i] = 0;
					}
				scanf("%d" , &r);
				int k;
				scanf("%d" , &k);
				int zona[MAX];
				for(i=0; i<k; i++)
					{
						scanf("%d" , &zona[i]);
					}
				int inceput[MAX][MAX];

				for(i=0; i<k; i++)
					{
						for(j=0; j<d; j++)
							{
								inceput[i][j]=0;
							}
					}
				int sfarsit[MAX][MAX];

				for(i=0; i<k; i++)
					{
						for(j=0; j<d; j++)
							{
								sfarsit[i][j]=0;
							}
					}
				int copie1,copie2;
				
				//marchez intr-o matrice nodurile in care se poate ajunge in fiecare depozit
				//marchez intr-o matrice nodurile din care se poate ajunge in fiecare depozit
				
				for(i=0; i<k; i++)
					{
						copie1 = zona[i];
						for(j=0; j<d; j++)
							{
								copie2 = depozite[j];
								if(mat[copie2][copie1] != 0)
									{
										inceput[i][j] = 1;
										contor1[j]++;
									}
								if(mat[copie1][copie2] != 0)
									{
										sfarsit[i][j] = 1;
										contor2[j]++;
									}
							}
					}

			//marchez in matrice cu 0 toate nodurile care nu apartin zonei sau nu sunt depozite

				for(i=0; i<n ; i++)
					{
						for(l=0; l<k; l++)
							{
								if(zona[l] == i)
									ok++;
							}
						if(ok==0)
							{
								for(l=0; l<d; l++)
									if(depozite[l] == i)
										ok++;
							}
						if(ok==0)
							{
								for(j=0; j<n; j++)
									{
										mat[i][j]=0;
										mat[j][i]=0;
									}
							}
						ok=0;
					}

			//salvez costul minim dintre fiecare doua noduri intr-o matrice

				float m[MAX][MAX];
			    for(i = 0; i < n; i++)
			        for(j = 0; j < n ; j++)
						{
				            if(mat[i][j] != 0 ||  i == j)
				                m[i][j] = mat[i][j];
				            else
				                m[i][j] = 99999;
				        }
			    for(l = 0; l < n; l++)
			        for(i = 0; i < n; i++)
			            for(j = 0; j < n; j++)
			                if(m[i][j] > m[i][l] + m[l][j])
			                    m[i][j] = m[i][l] + m[l][j];

				int copie3,copie4;

			//adaug intr-un vector de costuri minime pentr fiecare depozit
			//fac suma dintre drumul de plecare din depozit
			//drumul de ajungere in depozit
			//si drumul de cost minim dintre nodurile de plecare si sosire
			
				for(j=0; j<d; j++)
					{
						copie3 = depozite[j];
						if(contor1[j] == 1 && contor2[j] == 1)
							{
								for(i=0; i<k; i++)
								{
									copie4=zona[i];
									if(inceput[i][j] == 1)
										{
											copie1=zona[i];
											costuri[j] = costuri[j]+mat[copie3][copie4];
										}
												
										if(sfarsit[i][j] == 1)
											{
												copie2 = zona[i];
												costuri[j] = costuri[j]+mat[copie4][copie3];
											}
										}

									costuri[j] = costuri[j] + m[copie1][copie2];
								}
					}
					
				//compar drumurile minime de la ambele depozite
				//afisez drmul de cost minim	
					
				float min=1000.000;
				for(i=0; i<d; i++)
					{
						if(costuri[i] < min && costuri[i]>0)
							min = costuri[i];
					}
				printf("%.1f" , min);

			}
	}

	return 0;
}
