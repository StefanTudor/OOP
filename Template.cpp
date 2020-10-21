#include<iostream>
#include<string>

using namespace std;

class Timbru
{
	int an;
	string tara;
	float pret;
public:
	Timbru(int an, string tara, float pret)
	{
		this->an = an;
		this->tara = tara;
		this->pret = pret;
	}

	float getPret()
	{
		return pret;
	}

	 operator float()
	{
		return this->pret;
	}

	 Timbru() :an(0), tara("Romania"), pret(0) {};

	Timbru operator+(Timbru t)
	{
		Timbru timbru = *this;
		timbru.pret = this->pret + t.pret;
		return timbru;
	}

};

template <class cl>
class Colectionar
{
	cl* colectie;
	int nr_elemente;
	string nume; //ocupa cat ocupa stringul, 4 octeti
public:
	
	Colectionar(cl* colectie, int nr_elemente, string nume)
	{
		this->nr_elemente = nr_elemente;
		this->colectie = new cl[nr_elemente];
		for (int i = 0; i < nr_elemente; i++)
		{
			this->colectie[i] = colectie[i];
		}
		this->nume = nume;
	}

	Colectionar()
	{
		this->nume = " ";
		this->nr_elemente = 0;
		this->colectie = NULL;
	}
	~Colectionar()
	{
		if (this->colectie != NULL)
			delete[] this->colectie;
	}

	Colectionar(const Colectionar &col)
	{
		this->nr_elemente = col.nr_elemente;
		this->nume = col.nume;
		this->colectie = new cl[col.nr_elemente];
		for (int i; i < col.nr_elemente; i++)
		{
			this->colectie[i] = col.colectie[i];
		}
	}

	Colectionar operator=(const Colectionar &c)
	{
		this->nume = c.nume;
		this->nr_elemente = c.nr_elemente;
		if (this->colectie != NULL)
			delete[] this->colectie;
		this->colectie = new cl[c.nr_elemente];
		for (int i = 0; i < c.nr_elemente; i++)
		{
			this->colectie[i] = c.colectie[i];
		}
	}
	float CalculareValoare()
	{
		float sum = 0;
		for (int i = 0; i < this->nr_elemente; i++)
		{
			sum =sum + this->colectie[i];
		}
		return sum;
	}

};

class Carte
{
	int nr_pagini;
	string titlu;
	string autor;
public:
	Carte(int nr_pagini, string titlu, string autor)
	{
		this->nr_pagini = nr_pagini;
		this->titlu = titlu;
		this->autor = autor;
	}

	Carte()
	{
		this->nr_pagini = 20;
		this->titlu = "Titlu";
		this->autor = "Autor";
	}

	Carte operator+(Carte &c)
	{
		Carte carte = *this;
		carte.nr_pagini = this->nr_pagini + c.nr_pagini;
		return carte;
	}
	int getNrPagini()
	{
		return nr_pagini;
	}

	operator int()
	{
		return nr_pagini;
	}
};

float operator+(float s, Carte c)
{
	return s + c.getNrPagini();
}


template <class T>// <class T, class T2>
T adunare(T a, T b)
{
	return a + b;
}

void main()
{
	cout << adunare(1, 2) << endl;
	cout << adunare(1.578f, 2.678f) << endl; //punem f ca sa le vada de tip float
	Timbru t1(2019, "Romania", 100);
	Timbru t2(2018, "Romania", 20);
	Timbru t3 = adunare(t1, t2);
	cout << t3.getPret() << endl;

	Colectionar<int> c1;
	Colectionar<float> c2(new float[3]{ 4.6f, 5.8f, 2.7f }, 3, "Popescu"); //colectionar care colectioneaza valori float
	cout << c2.CalculareValoare() << endl;


	Colectionar<Timbru> c3(new Timbru[2]{ t1,t2 }, 2, "Vasilescu");
	//trebuie sa fac 2 carti si apoi ...
	Carte c6, c7;
	Colectionar<Carte> cart(new Carte[2]{ c6,c7 }, 2, "Manea");
	cout << cart.CalculareValoare() << endl;


}