#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int i,j,m,n,licznik,*stack,scount,*stackH,stackHcount;
bool *visitedH;

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
    while(remaining>n-1)
    {
        generateHamilton(n-1,adjmatrix);
        remaining-=(n-1);
    }
    generateHamilton(remaining,adjmatrix);
}

void generateHamilton(int range, int *adjmatrix[], int *stack)
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

void hamilton(int value, int *adjmatrix[])
{
    bool test;
    stackH[stackHcount++] = value;
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
        printf("wchodzi\n");
        test = false;           //zakladamy brak cyklu
        for(i=0; i<n; i++)
        {
            if(adjmatrix[value][i] == 1)
            {
                test = true;
                break;
            }
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
        while(adjmatrix[value][i] == 1)
        {
            adjmatrix[value][i] = 0;
            adjmatrix[i][value] = 0;
            euler(i, adjmatrix);
        }
    }
    stack[scount++] = value;
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
    m = 0.3*n*(n-1)/2;
    adjmatrix_gen(n, adjmatrix30);
    adjmatrix_print(n, adjmatrix30);
    printf("\nliczba krawedzi: %d\n",licznik);

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
    hamilton(0, adjmatrix30);
    //for(i=0; i<n; i++) printf("%d",stackH[i]);

    //EULER 0.3
    /*
    stack = (int*)malloc((m+1)*sizeof(int));
    scount = 0;

    euler(0, adjmatrix30);
    printf("Cykl eulera: ");
    for(i=0; i<scount; i++) printf("%d ",stack[i]);
    adjmatrix_print(n, adjmatrix30);*/

    //GENEROWANIE I WYŒWIETLANIE GRAFU 0.7
    printf("\n-----0.7-----\n");
    licznik = 0;
    m = 0.7*n*(n-1)/2;
    adjmatrix_gen(n, adjmatrix70);
    adjmatrix_print(n, adjmatrix70);
    printf("\nliczba krawedzi: %d\n",licznik);

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
