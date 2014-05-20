#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int i,j,m,n,licznik,*stack,scount,*stackH,stackHcount;
bool *visitedH;

////////////
int nr = 0, CH = 0, found = 0, e = 0;


void nullify(int **AM, int n);
void dfs(int n, int v, bool* visited, int **AM);

void create_AM(int **AM, int n, int m) { //creat Adjacency matrix
    int x, y, h, i, all_visited;
    bool *visit = malloc (n * sizeof(bool*));

    i = m;
    while(i) {
	y = rand()%n;
	x = rand()%n;
	if(AM[x][y] != 1 && x != y) {
	    AM[x][y] = AM[y][x] = 1;
	    i--;
	}
    }

	for(x = 0; x < n - 1; x++) {
	    h = Check_deg(AM, n, x);
	    if (h%2) {
		y = rand()%(n - x - 1) + x + 1;
		if (AM[x][y]) {
		    AM[x][y] = 0;
		    AM[y][x] = 0;
		    i--;
		}
		else {
		    AM[x][y] = 1;
		    AM[y][x] = 1;
		    i++;
		}
	    }
	}

    e = m + i;
    all_visited = 1;

    dfs(n, 0, visit, AM);

    for(x=0; x < n - 1; x++) {
	if (!visit[x]) {
	    all_visited = 0;
	    break;
	}
    }
    if (all_visited == 0) {
	nullify(AM, n);
	create_AM(AM, n, m);
    }
}

void dfs(int n, int v, bool* visited, int **AM) {
    int x;

    visited[v] = 1;
    for (x = 0; x < n; x++) {
	if (AM[v][x] && !visited[x]) {
	    dfs(n, x, visited, AM);
	}
    }
}

void nullify(int **AM, int n) {
    int i, j;

    for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++)  {
	    AM[i][j] = 0;
	}
    }
}

void copy(int **AM, int **AM_cp, int n) {
    int i, j;

    for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++)  {
	    AM_cp[i][j] = AM[i][j];
	}
    }
}

int Check_deg(int **AM, int n, int x) {
    int i, j;

    j = 0;
    for (i = 0; i < n; i++) {
	if (AM[x][i] == 1)
	    j++;
    }

    return j;
}




///////////////


void adjmatrix_gen(int n, int *adjmatrix[])     //generowanie macierzy sasiedztwa
{
    //int toRemove = 0, tmp;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            adjmatrix[i][j] = 0;
        }
    }

    //Tworzenie cyklu Hamiltona dla n krawedzi:
    generateHamilton(n,0,adjmatrix);

    //Dopelnianie grafu - ta sama funkcja tylko jako argument przekazujemy roznice m - n
    int remaining = m-n;
    while(remaining>n-1)
    {
        generateHamilton(n-1,rand()%n,adjmatrix);
        remaining-=(n-1);
    }
    generateHamilton(remaining,rand()%n,adjmatrix);
}

void generateHamilton(int range, int first, int *adjmatrix[])
{
    int toRemove = first, tmp;      //zaczynamy tworzyc cykl od 0
    int tab[n-1];               //tworzymy tablice n-1 elementow (bez 0)
    for(i=0; i<(n-1); i++) tab[i] = i+1;
    int tmp2, x;
    for(i=0; i<n; i++)
    {
        x = rand()%(n-1);
        tmp2 = tab[i];
        tab[i] = tab[x];
        tab[x] = tmp2;
    }

    for(i=(range-2); i>=0; i--)     //liczba iteracji wynosi range-2 poniewaz nie losujemy 0
    {
        do
        {
            tmp = rand()%(i+1);
        }   while((tab[tmp] == toRemove)/* || (adjmatrix[toRemove][tab[tmp]] == 1)*/);

        adjmatrix[toRemove][tab[tmp]] = 1;
        adjmatrix[tab[tmp]][toRemove] = 1;          //macierz musi byc symetryczna poniewaz graf jest nieskierowany
        licznik++;
        printf("%d \t %d\n",toRemove,tab[tmp]);
        toRemove = tab[tmp];            //w kazdej iterazcji skracamy tablice o 1 - nie chcemy zeby krawedzie sie powtarzaly
        tab[tmp] = tab[i];
    }
    if(range > 1)      //dla 8 m = n, dlatego range = 0, st¹d nie powinna sie tworzyc krawedz
    {
        adjmatrix[toRemove][first] = 1;
        adjmatrix[first][toRemove] = 1;
        licznik++;
        printf("%d \t %d\n\n",toRemove,first);
    }

}

void adjmatrix_print(int n, int *adjmatrix[])      //wyswietlanie macierzy sasiedztwa
{
    printf("\nMACIERZ SASIEDZTWA: \n");
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            printf("%d\t",adjmatrix[i][j]);
        }
        printf("\n");
    }
}

void hamilton(int value, int *adjmatrix[])
{
    bool test;
    stackH[stackHcount] = value;
    printf("%d\t%d\n",stackHcount, stackH[stackHcount]);
    stackHcount++;
    if (stackHcount < n)
    {
        visitedH[value] = true;
        for(i=0; i<n; i++)
        {
            if((adjmatrix[value][i] == 1) && (!visitedH[i])) hamilton(i, adjmatrix);
        }
        visitedH[value] = false;
    }
    else
    {
        //printf("wchodzi\n");
        test = false;           //zakladamy brak cyklu
            if(adjmatrix[value][0] == 1)
            {
                test = true;
            }
        if(test) printf("Cykl Hamiltona: ");
            else printf("Brak cyklu Hamiltona");

        for(i=0; i<stackHcount; i++)
        {
            printf("%d",stackH[i]);
        }
    }
    stackHcount--;
}

void euler(int value, int *adjmatrix[])
{
    for(i=0; i<n; i++)
    {
        if(adjmatrix[value][i] == 1)
        {
            adjmatrix[value][i] = 0;
            adjmatrix[i][value] = 0;
            euler(i, adjmatrix);
            stack[scount++] = value;
        }
    }

}


int main()
{
    srand(time(NULL));
    n = 0;
    licznik = 0;
    do
    {
        printf("Podaj liczbe wierzcholkow: (min. 8)\n");
        scanf("%d",&n);
    } while (n < 8);


    //INICJALIZACJA TABLICY n x n - macierz sasiedztwa
    int **adjmatrix30;
    adjmatrix30 = (int**)malloc(n*sizeof(int*));
    for (i=0; i<n; i++)
    {
        adjmatrix30[i] = (int*)malloc(n*sizeof(int));
    }

    int **adjmatrix70;
    adjmatrix70 = (int**)malloc(n*sizeof(int*));
    for (i=0; i<n; i++)
    {
        adjmatrix70[i] = (int*)malloc(n*sizeof(int));
    }

    //GENEROWANIE I WYŒWIETLANIE GRAFU 0.3
    printf("\n-----0.3-----\n");
    nullify(adjmatrix30,n);
    m = 0.3*n*(n-1)/2;
    //adjmatrix_gen(n, adjmatrix30);
    /////
    create_AM(adjmatrix30,n,m);
    /////
    adjmatrix_print(n, adjmatrix30);
    //printf("\nliczba krawedzi: %d\n",licznik);

    /*TESTOWE USUWANIE JEDNEJ KRAWEDZI
    int toD, toD2;
    printf("podaj krawedz do usuniecia: ");
    scanf("%d",&toD);
    scanf("%d",&toD2);
    adjmatrix30[toD][toD2] = 0;
    adjmatrix30[toD2][toD] = 0;
    */

    //HAMILTON 0.3

    stackH = (int*)malloc(n*sizeof(int));
    stackHcount = 0;
    visitedH = (bool*)malloc(n*sizeof(bool));
    for(i=0; i<n; i++) visitedH[i] = false;
    printf("\n");
    hamilton(0, adjmatrix30);
    //for(i=0; i<n; i++) printf("%d",stackH[i]);
    printf("\n");

    //EULER 0.3
    stack = (int*)malloc((m+1)*sizeof(int));
    scount = 0;

    euler(0, adjmatrix30);
    printf("Cykl eulera: ");
    for(i=0; i<scount; i++) printf("%d ",stack[i]);
    //adjmatrix_print(n, adjmatrix30);

    /*
    //GENEROWANIE I WYŒWIETLANIE GRAFU 0.7
    printf("\n-----0.7-----\n");
    licznik = 0;
    m = 0.7*n*(n-1)/2;
    adjmatrix_gen(n, adjmatrix70);
    adjmatrix_print(n, adjmatrix70);
    printf("\nliczba krawedzi: %d\n",licznik);*/

    //EULER 0.7
    /*
    stack = (int*)realloc(stack,(m+1)*sizeof(int));
    scount = 0;

    euler(0, adjmatrix70);
    printf("Cykl eulera: ");
    for(i=0; i<scount; i++) printf("%d ",stack[i]);*/




    //ZWALNIANIE PAMIECI
    for (i=0; i<n; i++)
    {
        free(adjmatrix30[i]);
        free(adjmatrix70[i]);
    }
    free(adjmatrix30);
    free(adjmatrix70);
    free(stack);
    free(stackH);
    free(visitedH);
}
