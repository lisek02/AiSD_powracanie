#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int i,j,m,n,licznik,*stack,scount,*stackH,stackHcount,K;
bool *visitedH, test;

///////////////

void generowanie(int N, int *tab[])
{
        //zeruję macierz sąsiedztwa
	int i, j;
	for (i = 0; i < N; i++)
	for (j = 0; j < N; j++)
		tab[i][j] = 0;

        //Dodaję tablicę, w której stworzę jeden pełny cykl Hamiltona.
	int *los = (int*)malloc(n*sizeof(int));

        //Losuję cykl Hamiltona  (pseudolosowa tablica, w której każdy element występuje tylko jeden raz - gdzieś wcześniej już to tak robiliśmy).
	int k;
	for (k = 0; k < N; k++)
	{
		los[k] = k;
	}
	srand(time(0));
	int pom, losowa, l;
	for (l = 0; l < N; l++)
	{
		losowa = rand() % N;
		pom = los[l];
		los[l] = los[losowa];
		los[losowa] = pom;
	}

        //Przepisuję wcześniej otrzymany cykl do macierzy sąsiedztwa.
	int m;
	for (m = 0; m < N; m++)
	{
		tab[los[m]][los[(m + 1) % N]] = 1;
		tab[los[(m + 1) % N]][los[m]] = 1;
	}


        //Dopełniam graf do globalnego K krawędzi dodając cykl złożony z 3 jeszcze wierzchołków, pomiędzy którymi nie ma krawędzi i które się nie powtarzają.
	int wygenerowane = N;
	while (wygenerowane < K)
	{
		int a = rand() % N;
		int b = rand() % N;
		int c = rand() % N;

		if (tab[a][b] == 0 && tab[b][c] == 0 && tab[c][a] == 0 && a!=b && b!=c && a!=c)
		{
			tab[a][b] = 1;
			tab[b][a] = 1;
			tab[b][c] = 1;
			tab[c][b] = 1;
			tab[c][a] = 1;
			tab[a][c] = 1;
			wygenerowane = wygenerowane + 3;
		}
	}

    //A to do zadania B - Hamiltona - graf niespójny.
	/*
	for (int i = 0; i < N; i++)
	{
		tab[N-1][i] = 0;
		tab[i][N-1] = 0;
	}*/

	free(los);

}

void generowanie_niesp(int N, int *tab[])
{
        //zeruję macierz sąsiedztwa
	int i, j;
	for (i = 0; i < N; i++)
	for (j = 0; j < N; j++)
		tab[i][j] = 0;

        //Dodaję tablicę, w której stworzę jeden pełny cykl Hamiltona.
	int *los = (int*)malloc(n*sizeof(int));

        //Losuję cykl Hamiltona  (pseudolosowa tablica, w której każdy element występuje tylko jeden raz - gdzieś wcześniej już to tak robiliśmy).
	int k;
	for (k = 0; k < N; k++)
	{
		los[k] = k;
	}
	srand(time(0));
	int pom, losowa, l;
	for (l = 0; l < N; l++)
	{
		losowa = rand() % N;
		pom = los[l];
		los[l] = los[losowa];
		los[losowa] = pom;
	}

        //Przepisuję wcześniej otrzymany cykl do macierzy sąsiedztwa.
	int m;
	for (m = 0; m < N; m++)
	{
		tab[los[m]][los[(m + 1) % N]] = 1;
		tab[los[(m + 1) % N]][los[m]] = 1;
	}


        //Dopełniam graf do globalnego K krawędzi dodając cykl złożony z 3 jeszcze wierzchołków, pomiędzy którymi nie ma krawędzi i które się nie powtarzają.
	int wygenerowane = N;
	while (wygenerowane < K)
	{
		int a = rand() % N;
		int b = rand() % N;
		int c = rand() % N;

		if (tab[a][b] == 0 && tab[b][c] == 0 && tab[c][a] == 0 && a!=b && b!=c && a!=c)
		{
			tab[a][b] = 1;
			tab[b][a] = 1;
			tab[b][c] = 1;
			tab[c][b] = 1;
			tab[c][a] = 1;
			tab[a][c] = 1;
			wygenerowane = wygenerowane + 3;
		}
	}

    //A to do zadania B - Hamiltona - graf niespójny.

	for (i = 0; i < N; i++)
	{
		tab[N-1][i] = 0;
		tab[i][N-1] = 0;
	}

	free(los);

}

///////////

/*
void adjmatrix_gen2(int n, int *adjmatrix[])
{
    //int rem;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            adjmatrix[i][j] = 0;
        }
    }
    generateHamilton2(n, adjmatrix);
    int rem = m-n;
    while(rem > n-1)
    {
        complementHamilton2(n-1, adjmatrix);
        rem -= n-1;
    }
    complementHamilton2(rem, adjmatrix);
}

void generateHamilton2(int n, int *adjmatrix[])
{
    int tab[n-1];
    randomArray(n-1, tab);
    adjmatrix[0][tab[0]] = 1;
    adjmatrix[tab[0]][0] = 1;
    printf("0 - %d\n",tab[0]);
    for(i=0; i<n-2; i++)
    {
        adjmatrix[tab[i]][tab[i+1]] = 1;
        adjmatrix[tab[i+1]][tab[i]] = 1;
        printf("%d - %d\n",tab[i],tab[i+1]);
    }
    adjmatrix[tab[n-2]][0] = 1;
    adjmatrix[0][tab[n-2]] = 1;
    printf("%d - 0\n",tab[n-2]);
}

void complementHamilton2(int size, int *adjmatrix[])
{
    int r1,r2,rpocz;
    r1 = rand()%n;
    rpocz = r1;
    printf("\n");
    for(i=0; i<size-1; i++)
    {
        do
        {
            r2 = rand()%n;
        } while((r1 == r2) || (adjmatrix[r1][r2] == 1));

        adjmatrix[r1][r2] = 1;
        adjmatrix[r2][r1] = 1;
        printf("%d - %d\n",r1,r2);

        r1 = r2;
    }
    adjmatrix[r1][rpocz] = 1;
    adjmatrix[rpocz][r1] = 1;
    printf("%d - %d\n",r1,rpocz);
}

void randomArray(int size, int *tab[])
{
    for(i=0; i<size; i++)
    {
        tab[i] = i+1;
    }
    for(i=0; i<size; i++)
    {
        int tmp, index;
        index = rand()%size;
        tmp = tab[index];
        tab[index] = tab[size-1];
        tab[size-1] = tmp;
    }
}
*/

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

void nullify(int **AM, int n) {
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            AM[i][j] = 0;
        }
    }
}

void hamilton2(int value, int *adjmatrix[])
{
    stackH[stackHcount] = value;
    stackHcount++;
    if(stackHcount < n)
    {
        visitedH[value] = true;
        for(i=0; i<n; i++)
        {
            if((adjmatrix[value][i] == 1) && (visitedH[i] == false))
            {
                hamilton2(i, adjmatrix);
            }
        }
        visitedH[value] = false;
    }
    else
    {
        if((adjmatrix[value][0] == 1) && (test == true))
        {
            printf("Cykl Hamiltona: ");
            for(i=0; i<stackHcount; i++)
            {
                printf("%d ",stackH[i]);
            }
            printf("0");
            test = false;
            //return;

        }
    }
    if(test == false) return;
    stackHcount--;
    i = value;
}

void euler(int value, int *adjmatrix[])
{
    for(i=0; i<n; i++)
    {
        while(adjmatrix[value][i] == 1)
        {
            adjmatrix[value][i] = 0;
            adjmatrix[i][value] = 0;
            euler(i, adjmatrix);
            stack[scount++] = value;
        }

    }
    i = value;
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


/*-----INICJALIZACJA TABLICY n x n - macierz sasiedztwa-----*/

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

/*-----GENEROWANIE I WYŒWIETLANIE GRAFU 0.3-----*/

    printf("\n-----0.3-----\n");
    nullify(adjmatrix30,n);
    K = 0.3*n*(n-1)/2;

    //generateHamilton2(n,adjmatrix30);
    //adjmatrix_gen2(n, adjmatrix30);

    generowanie(n,adjmatrix30);

    //adjmatrix_print(n, adjmatrix30);
    //printf("\nliczba krawedzi: %d\n",licznik);

  /*---HAMILTON 0.3---*/

    stackH = (int*)malloc((n+1)*sizeof(int));
    stackHcount = 0;
    visitedH = (bool*)malloc(n*sizeof(bool));
    for(i=0; i<n; i++) visitedH[i] = false;
    printf("\n");
    test = true;
    hamilton2(0, adjmatrix30);
    printf("\n");

  /*---EULER 0.3---*/

    stack = (int*)malloc((K+1)*sizeof(int));
    scount = 0;

    euler(0, adjmatrix30);
    printf("Cykl eulera: ");
    for(i=0; i<scount; i++) printf("%d ",stack[i]);
    //adjmatrix_print(n, adjmatrix30);



/*-----GENEROWANIE I WYŒWIETLANIE GRAFU 0.7-----*/

    printf("\n-----0.7-----\n");
    licznik = 0;
    K = 0.7*n*(n-1)/2;

    //adjmatrix_gen2(n, adjmatrix70);

    generowanie(n, adjmatrix70);

    //adjmatrix_print(n, adjmatrix70);
    //printf("\nliczba krawedzi: %d\n",licznik);

  /*---HAMILTON 0.7---*/
    stackHcount = 0;
    for(i=0; i<n; i++) visitedH[i] = false;
    printf("\n");
    test = true;
    hamilton2(0, adjmatrix70);
    printf("\n");

  /*---EULER 0.7---*/
    stack = (int*)realloc(stack,(K+1)*sizeof(int));
    scount = 0;

    euler(0, adjmatrix70);
    printf("Cykl eulera: ");
    for(i=0; i<scount; i++) printf("%d ",stack[i]);


/*-----GENEROWANIE I WYŒWIETLANIE GRAFU 0.5-----*/

    printf("\n-----0.7-----\n");
    licznik = 0;
    K = 0.5*n*(n-1)/2;

    generowanie_niesp(n, adjmatrix70);

  /*---HAMILTON 0.5---*/
    stackHcount = 0;
    for(i=0; i<n; i++) visitedH[i] = false;
    printf("\n");
    test = true;
    hamilton2(0, adjmatrix70);
    printf("\n");


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
