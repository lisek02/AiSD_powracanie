#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i,j,m,n,licznik;

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
    generateHamilton(n,adjmatrix);

    //Dopelnianie grafu - ta sama funkcja tylko jako argument przekazujemy roznice m - n
    int remaining = m-n;
    while(remaining>n)
    {
        generateHamilton(n,adjmatrix);
        remaining-=n;
    }
    generateHamilton(remaining,adjmatrix);
}

void generateHamilton(int range, int *adjmatrix[])
{
    int toRemove = 0, tmp;      //zaczynamy tworzyc cykl od 0
    int tab[n-1];               //tworzymy tablice n-1 elementow (bez 0)
    for(i=0; i<(n-1); i++) tab[i] = i+1;

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
        adjmatrix[toRemove][0] = 1;
        adjmatrix[0][toRemove] = 1;
        licznik++;
        printf("%d \t %d\n\n",toRemove,0);
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
    printf("\n-----0.3-----\n");
    m = 0.3*n*(n-1)/2;
    adjmatrix_gen(n, adjmatrix30);
    adjmatrix_print(n, adjmatrix30);
    printf("\nliczba krawedzi: %d\n",licznik);

    printf("\n-----0.7-----\n");
    licznik = 0;
    m = 0.7*n*(n-1)/2;
    adjmatrix_gen(n, adjmatrix70);
    adjmatrix_print(n, adjmatrix70);
    printf("\nliczba krawedzi: %d\n",licznik);
}
