//Autor: Marek Górski, nr indeksu 155647, grupa D1, semestr II, kierunek Informatyka,
//Wydział Informatyki, Zarządzania i Transportu, rok akademicki 2022/2023

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct Punkt
{
	double x;
	double y;
	double odl;
};

struct odleglosc
{
	double max;
	int indexMax;
	double min;
	int indexMin;
};

void WypelnienieTablicy(Punkt *, unsigned int);
void WypisanieTablicyJedenWymiar (Punkt *, unsigned int);
double Pitagoras (double, double);
double Modul (double);
double Pierwiastek (double);
int Porownanie (Punkt *, unsigned int, double);
void WypisaniePunktowWewnatrzOkregu (Punkt *, unsigned int, double);
void WypisanieTablicyTrojkatnej(double **, int);
void ObliczenieOdleglosciMiedzyPunktami(double **, int, Punkt *, odleglosc *);
void WypisanieEkstremowOdleglosci (odleglosc *, Punkt *, int);

int main ()
{
	srand(time(0));
	int N;
	char wybor;
	double R;
	cout << "Program Zadanie 2.3" << endl;
	cout << "Struktury i dynamiczne tablice" << endl;
	
	cout << endl << "Podaj prosze N (liczba elementow tablicy): ";
	cin >> N;
	Punkt *tab = new Punkt [N];
	WypelnienieTablicy (tab, N);
	
	cout << "Czy chesz wyswietlic zawartosc calej tablicy [t/n]? ";
	cin >> wybor;
	if (wybor == 't' || wybor == 'T')
		WypisanieTablicyJedenWymiar (tab, N);
	
	cout << "Podaj promien okregu: ";
	cin >> R;
	cout << "Liczba punktow znajdujacych sie wewnatrz okregu: " << Porownanie (tab, N, R) << endl;
	
	cout << "Czy chesz wyswietlic punkty znajdujace sie wewnatrz okregu [t/n]? ";
	cin >> wybor;
	if (wybor == 't' || wybor == 'T')
		WypisaniePunktowWewnatrzOkregu (tab, N, R);
	
	double **odlegloscMiedzyPunktami = new	double *[N] {0};
	for (int i=0; i<N; i++)
	{
		odlegloscMiedzyPunktami[i] = new double [i+1] {0};
	}
	odleglosc *ekstremum = new odleglosc [N] {0};
	for (int i=0; i<N; i++)
	{
		ekstremum[i].min=100.0;
	}

	ObliczenieOdleglosciMiedzyPunktami (odlegloscMiedzyPunktami, N, tab, ekstremum);
	
	cout << "Czy chcesz wyswietlic ekstrema odleglosc miedzy punktami [t/n]? ";
	cin >> wybor;
	if (wybor == 't' || wybor == 'T')
		WypisanieEkstremowOdleglosci (ekstremum, tab, N);
	
	cout << "Czy chesz wyswietlic tablice trojkatna z odleglosciami miedzy punktami [t/n]? ";
	cin >> wybor;
	if (wybor == 't' || wybor == 'T')	
		WypisanieTablicyTrojkatnej (odlegloscMiedzyPunktami, N);
	
	for (int i=0; i<N; i++)
	{
		delete []odlegloscMiedzyPunktami[i];
	}
	delete []odlegloscMiedzyPunktami;
	delete []ekstremum;
	delete []tab;
	return 0;
}

void WypelnienieTablicy (Punkt tablica[], unsigned int rozmiar)
{
	for (int i=0; i<rozmiar; i++)
	{
		tablica[i].x = (rand()%101)/10.0;
		tablica[i].y = (rand()%101)/10.0;
		tablica[i].odl = Pitagoras(tablica[i].x, tablica[i].y);
	}
}

double Pitagoras (double a, double b)
{
	double c=0;
	if (a==0 && b!=0) c = Modul(b);
	else if (b==0 && a!=0) c = Modul(a);
	else if (b!=0 && a!=0) c = Pierwiastek (a*a+b*b);
	return c;
}

double Modul (double x)
{
	if (x>=0) return x;
	else return (-x);
}

double Pierwiastek (double a)
{
	double p = a/2;
	double x;
	const double eps = 1e-12;
	const int maxIter = 100;
	for (int i=0; i<maxIter; i++)
	{
		x=(p+a/p)/2;
		if (Modul(p-x) < eps) break;
		p=x;
	}
	return x;
}

void WypisanieTablicyJedenWymiar (Punkt tablica[], unsigned int rozmiar)
{
	cout << "Punkty w tablicy:" << endl;
	
	for (int i=0;i<rozmiar;i++)
	{
		cout << defaultfloat << setw(2) << i+1 << ". ";
		cout << fixed << setprecision(1);
		cout << "(" << setw(4) << tablica[i].x << ";" << setw(4) << tablica[i].y << ") ";
		cout << setprecision(5);
		cout << "- odleglosc od (0;0) wynosi: " << setw(9) << tablica[i].odl << endl;
	}
}

int Porownanie (Punkt tablica[], unsigned int rozmiar, double promien)
{
	int counter=0;
	for (int i=0;i<rozmiar;i++)
	{
		if (tablica[i].odl<promien) ++counter;
	}
	return counter;
}

void WypisaniePunktowWewnatrzOkregu (Punkt tablica[], unsigned int rozmiar, double promien)
{
	int counter=0;
	cout << "Wspolrzedne punktow znajdujacych sie wewnatrz okregu:" << endl;
	for (int i=0;i<rozmiar;i++)
	{
		if (tablica[i].odl<promien)
		{
			counter++;
			cout << defaultfloat << setw(2) << i+1 << ". ";
			cout << fixed << setprecision(1);
			cout << "(" << setw(4) << tablica[i].x << ";" << setw(4) << tablica[i].y << ")" << endl;
		}
	}
	if (counter==0) cout << "Nie ma punktow spelniajacych podane kryteria." << endl;
}

void ObliczenieOdleglosciMiedzyPunktami(double **odlegloscMiedzyPunktami, int N, Punkt *tab, odleglosc *ekstremum)
{
	int i, j;
	for (i=0; i<N; i++)
	{
		for (j=0; j<i; j++)
		{
			odlegloscMiedzyPunktami[i][j] = Pitagoras (tab[i].x-tab[j].x, tab[i].y-tab[j].y);
			if (odlegloscMiedzyPunktami[i][j] > ekstremum[i].max)
			{
				ekstremum[i].max = odlegloscMiedzyPunktami[i][j];
				ekstremum[i].indexMax = j;
			}
			if (odlegloscMiedzyPunktami[i][j] > ekstremum[j].max)
			{
				ekstremum[j].max = odlegloscMiedzyPunktami[i][j];
				ekstremum[j].indexMax = i;
			}
			if (odlegloscMiedzyPunktami[i][j] < ekstremum[i].min)
			{
				ekstremum[i].min = odlegloscMiedzyPunktami[i][j];
				ekstremum[i].indexMin = j;
			}
			if (odlegloscMiedzyPunktami[i][j] < ekstremum[j].min)
			{
				ekstremum[j].min = odlegloscMiedzyPunktami[i][j];
				ekstremum[j].indexMin = i;
			}
		}
	}
}

void WypisanieTablicyTrojkatnej(double **tab, int iloscWierszy)
{
	cout << "indeks|";
	for (int i=0; i<iloscWierszy; i++)
		cout << defaultfloat << setw(6) << i+1 << "|";
	cout << endl;
	for (int i=0; i<iloscWierszy; i++)
	{
		cout << defaultfloat << setw(6) << i+1 << "|";
		for (int j=0; j<=i; j++)
		{
			cout << fixed << setprecision(3) << setw(6) << tab [i][j] << "|";
		}
		cout << endl;
	}
}

void WypisanieEkstremowOdleglosci (odleglosc *ekstremum, Punkt *tab, int N)
{
	cout << "   Punkt   | Max.Odl.  | Max.Pkt.  | Min.Odl.  | Min.Pkt.  " << endl;
	for (int i=0; i<N; i++)
	{
		cout << fixed << setprecision(1);
		cout << "(" << setw(4) << tab[i].x << ";" << setw(4) << tab[i].y << ")";
		cout << "|" << setprecision(3) << setw(10) << ekstremum[i].max << " |";
		cout << setprecision(1) << "(" << setw(4) << tab[ekstremum[i].indexMax].x << ";" << setw(4) << tab[ekstremum[i].indexMax].y << ")";
		cout << "|" << setprecision(3) << setw(10) << ekstremum[i].min << " |";
		cout << setprecision(1) << "(" << setw(4) << tab[ekstremum[i].indexMin].x << ";" << setw(4) << tab[ekstremum[i].indexMin].y << ")";
		cout << endl;
	}
}
