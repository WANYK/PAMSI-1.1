#include <iostream>
#include <time.h>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <cmath>
using namespace std;


/************************************
*									*
*	INSTRUKCJA OBSŁUGI PROGRAMU		*
*	ZNAJDUJE SIĘ POD PROGRAMEM		*
*									*
************************************/

//Sorotowanie szybkie
//*******************
void quicksort (int tab[], int poczatek, int koniec)
{
	int i=poczatek;
	int j=koniec;
	int piwot=(poczatek+koniec)/2;
	int wartosc_srodkowa=tab[piwot];
	while(i<=j)
	{
		//tutaj szukam elementu, który jest mniejszy 
		//od środkowej wartości, zwanego często piwot
		while (tab[i]<wartosc_srodkowa)
		{
			i++;
		}

		//tutaj szukam elementu, który jest większy
		//od środkowej wartości
		while (tab[j]>wartosc_srodkowa)
		{
			j--;
		}

		//teraz sprawdzam, czy elementy się nie minęły
		//jeśli tak się stało, to program zamienia 
		//emelenty stojace po niewlasciwej stronie srodka
		if (i<=j)
		{
			swap(tab[i], tab[j]);
			i++;
			j--;
		}
	} 

	if (poczatek<j) 
	{
		quicksort(tab, poczatek, j);
	}

	if (i<koniec)
	{ 
		quicksort(tab, i, koniec);
	}
}

//Sorotowanie przez scalanie
//**************************
int scal (int tab[], int poczatek, int srodek, int koniec)
{

	int rozmiar1=srodek-poczatek+1;
	int rozmiar2=koniec-srodek;

	// tutaj deklaruje dwie podtablice
	int tab1[rozmiar1];	
	int tab2[rozmiar2];	

	// tutaj tworze te dwie podtablice
	for (int i=0; i<rozmiar1; i++)
	{
		tab1[i]=tab[poczatek+i];
	}
	for (int i=0; i<rozmiar2; i++)
	{
		tab2[i]=tab[srodek+1+i];
	}
	
	int i=0;		// indeks pierwszej tablicy
	int j=0;		// indeks drugiej tablicy
	int k=poczatek;

	//ten while nakazuje wykonywac dopóki
	//nie przejdzie po wszystkich elementach
	while (i<rozmiar1 && j<rozmiar2)
	{
		//teraz porównujemy 2 podtablice
		if (tab1[i]<=tab2[j])
		{
			//dołączamy do głównej tablicy
			//element pierwszej podtablicy 
    		tab[k]=tab1[i];
    		k++;						
    		i++;						
    	}
    	if (tab1[i]>tab2[j])		
    	{
    		tab[k]=tab2[j];
    		k++;
    		j++;
    	}
	}

	//jeżeli jedna z podtablic vędzie 
	//"wyczerpana", to wykona się
	//poniższy while
	while (k<=koniec)
	{
		if (i<rozmiar1)
		{
			tab[k]=tab1[i];
			k++;
			i++;
		}
		if (j<rozmiar2)
		{
			tab[k]=tab2[j];
			k++;
			j++;
		}
	}
}

void sortuj_scalanie (int tab[], int poczatek, int koniec)
{
	if (poczatek<koniec)
	{
		int srodek=(poczatek+koniec)/2;
		sortuj_scalanie (tab, poczatek, srodek);
		sortuj_scalanie (tab, srodek+1, koniec);
		scal (tab, poczatek,srodek,koniec);
	}
}


//Sorotowanie introspektywne
//**************************

//Sortowanie przez wstawnianie 
void sortuj_wstawianie (int tab[], int poczatek, int koniec)
{
	//tutaj funkcja zaczyna się od drugiego
	//elementu w podmacierzy 
	for (int i=poczatek+1; i<=koniec; i++)
	{
		int wartosc=tab[i];
		int j=i;

		//w tym miejscu nasz program szuka 
		//indeksu j, w posortowanym podzbiorze 
		while (j>poczatek && tab[j-1]>wartosc)
		{
			tab[j]=tab[j-1];
			j--;
		}

		tab[j]=wartosc;
	}
}

//Sortowanie przez kopcowanie
void sortowanie_kopcowanie (int *poczatek, int *koniec)
{
	make_heap (poczatek, koniec);
	sort_heap (poczatek, koniec);
}

int podzial (int tab[], int poczatek, int koniec)
{
	//funkcja działająca na identycznej 
	//zasadzie jak w sortowaniu szybkim
    int piwot=tab[(poczatek+koniec)/2], i=poczatek, j=koniec; 
    while (true)
    {
        while (tab[j]>piwot) 
        {
        	j--;
        }

        while (tab[i]<piwot) 
        {
        	i++;
        }

        if (i<j)  
        {
        	std::swap(tab[i++], tab[j--]);
        }
        else return j;
    }
}

//Sortowanie introspektywne
void sortowanie_introspektywne (int tab[], int *poczatek, int *koniec, int max_glebokosc)
{
	//jeżeli rozmiar po podziale jest 
	//mniejszy niż 16 wykona się funkcja
	if ((koniec-poczatek)<16) 
	{
		sortuj_wstawianie (tab, poczatek-tab, koniec-tab);
	}
	//jeżeli nie to wykonaj sortowanie
	//przez kopcowanie 
	else if (max_glebokosc==0) 
	{
		sortowanie_kopcowanie (poczatek, koniec+1);
	}
	//dla reszty wykonaj quicksorta 
	else 
	{
		int piwot=podzial(tab, poczatek-tab, koniec-tab);
		sortowanie_introspektywne(tab, poczatek, tab+piwot-1, max_glebokosc-1);
		sortowanie_introspektywne(tab, tab+piwot+1, koniec, max_glebokosc-1);
	}
}

void stworz_tablice_rand (int tab[], int rozmiar)
{
	srand(time(NULL));
	for (int i=0; i<rozmiar; i++)
	{
		tab[i]=(rand()%100);
	}
}

//funkcja ta dotyczy wyłącznie sortowania introspektywnego,
//ponieważ w pozostałych dwóch algorytmach procent posortowania
//tablicy zmieniam w int main()
void stworz_tablice_proc (int tab[], int rozmiar, double procent)
{
	int p=(int)((procent*rozmiar)/100);
	srand(time(NULL));
	for (int i=0; i<rozmiar; i++)
	{
		if (i<=p) tab[i]=i+1;
		else tab[i]=(rand()%100);
	}
}

//funkcja służąca do odwtotnego sortowania,
//czyli do zamiany tablicy posortowanej 
//na nieposortowaną
void odwroc (int tab[], int rozmiar)
{
	int tab_tymczasowa[rozmiar];
	for(int i=0; i<rozmiar; i++)
	{
		tab_tymczasowa[i]=tab[rozmiar-1-i];
	}
	for(int j=0; j<rozmiar; j++)
	{
		tab[j]=tab_tymczasowa[j];
	}
}

void daj_czas (double tab_czasow[])
{
	long double sredni_czas;
	long double najmniejszy_czas;
	long double najwiekszy_czas;

	long double suma_czasow=0;


	najmniejszy_czas=tab_czasow[0];
	najwiekszy_czas=tab_czasow[0];

	for(int i=0; i<100; i++)
	{
		suma_czasow=suma_czasow+tab_czasow[i];
		
		if(tab_czasow[i]<najmniejszy_czas)
		{
			najmniejszy_czas=tab_czasow[i];	
		}
		if(tab_czasow[i]>=najwiekszy_czas)
		{
			najwiekszy_czas=tab_czasow[i];
		}
	}
	sredni_czas=suma_czasow/100;
	cout<<endl<<"Najmniejszy czas to : "<< najmniejszy_czas<<endl;
	cout<<"Najwiekszy czas to : " <<najwiekszy_czas<<endl;	
	cout<<"Sredni czas to : "<< sredni_czas<<endl;
}

/***********************************************
***********************************************/

int main()
{
	int tab[10000];
	int rozmiar = sizeof(tab)/sizeof(tab[0]);
	int max_glebokosc = log(rozmiar) * 2;
	double tab_czasow[100];
	
	for(int l=0; l<100; l++)
	{
		//funkcje dla quicksort oraz mergesort
		stworz_tablice_rand(tab, rozmiar);
		//odwroc(tab, rozmiar);

		//funkcje dla sortowania introspektywnego
		//stworz_tablice_proc( tab, rozmiar, 99.7);
		//odwroc(tab, rozmiar);

		auto start_time = chrono::high_resolution_clock::now();

		//SCALANIE
		sortuj_scalanie(tab,0, (rozmiar-1)*0.25);

		//SZYBKIE
		//quicksort(tab,0, (rozmiar-1)*0.25);

		//INTROSPEKTYWNE
		//sortowanie_introspektywne(tab, tab, tab+rozmiar-1, max_glebokosc); 

		auto koniec_time = chrono::high_resolution_clock::now();
		tab_czasow[l]= chrono::duration_cast<chrono::microseconds>(koniec_time - start_time).count() ;
	}
	daj_czas(tab_czasow);
	return 0;
}


/******************************************************************
INSTRUKCJA OBSŁUGI PROGRAMU:
1. ABY DOKONAĆ KOMPILACJI NALEŻY WPISAĆ: g++ sortowania-2.cpp
2. ABY URUCHOMIĆ PROGRAM NALEŻEY WPISAĆ: ./a.out
*******************************************************************
INSTRUKCJA POSŁUGIWANIA SIĘ KODEM:
1. W CELU ZMANY ROZMIARU TABLICY NALEŻY WPISAĆ W NAWIASY
   KWADRATOWE W int tab[] WARTOŚCI TAKIE JAK 10000, 50000,
   100000, 500000, 1000000 (WERS 298)

2. W CELU WYKONANIA SORTOWANIA QUICSORT NALEŻEY UMIEŚCIĆ W 
   KOMENTARZU WERSY TAKIE JAK: 307, 310, 311, 316, 322
3. W CELU WYKONANIA SORTOWANIA ODWROTNEGO QUICSORT NALEŻEY 
   UMIEŚCIĆ W KOMENTARZU WERSY TAKIE JAK: 306, 310, 311, 316, 322
4. W CELU WYKONANIA SORTOWANIA PRZEZ SCALANIE NALEŻEY UMIEŚCIĆ W 
   KOMENTARZU WERSY TAKIE JAK: 307, 310, 311, 319, 322
5. W CELU WYKONANIA SORTOWANIA ODWROTNEGO SCALANIA NALEŻEY 
   UMIEŚCIĆ W KOMENTARZU WERSY TAKIE JAK: 306, 310, 311, 319, 322
6. W CELU WYKONANIA SORTOWANIA INTROSPEKTYWNEGO NALEŻEY UMIEŚCIĆ W 
   KOMENTARZU WERSY TAKIE JAK: 306, 307, 311, 316, 319
7. W CELU WYKONANIA SORTOWANIA ODWROTNEGO SCALANIA NALEŻEY 
   UMIEŚCIĆ W KOMENTARZU WERSY TAKIE JAK: 306, 307, 310, 316, 319

8. W CELU PROCENTOWEJ ZMIANY ILOSCI POSORTOWANIA 
   ELEMENTOW TABLICY NALEŻY:
   -> DLA SORTOWANIA SZYBKIEGO I PRZEZ SCALANIE:
      W WERSACH 316 LUB 319 NALEŻY DOKONAĆ ZMIAN W ILOCZYNIE
      0.25-25% , 0.5-50% ANALOGICZNIE RESZTA PRZYPADKÓW
   -> DLA SORTOWANIA INTROSPEKTYWNEGO:
   	  W WERSIE 310 NALEŻY WPISAĆ LICZBĘ, KTÓRA OKREŚLA ILE
   	  PROCENT ELEMENTÓW TABLICY MA BYĆ POSORTOWANA 
********************************************************************/