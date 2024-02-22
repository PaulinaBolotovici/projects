#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

class CustomException {
	string mesaj;
public:
	CustomException(string mesaj) : mesaj(mesaj) {}
	string getMesaj() { return this->mesaj; }
};

class MateriePrima {
	const int idMateriePrima; 
	char* denumireMateriePrima = nullptr; 
	int stoc = 0; 
public:
	int getIdMateriePrima() const {
		return this->idMateriePrima;
	}

	const char* getDenumireMateriePrima() {
		if (this->denumireMateriePrima != nullptr)
			return this->denumireMateriePrima;
		else
			return " - ";
	}

	void setDenumireMateriePrima(const char* denumire) {
		if (denumire != nullptr && strlen(denumire) >= 3)
		{
			this->denumireMateriePrima = new char[strlen(denumire) + 1];
			strcpy(this->denumireMateriePrima, denumire);
		}
		else
			throw new CustomException("\nInput invalid!");
	}

	int getStoc() {
		return this->stoc;
	}

	void setStoc(int stoc) {
		if (stoc >= 0)
			this->stoc = stoc;
		else
			throw new CustomException("\nInput invalid!");
	}

	MateriePrima(int id) :idMateriePrima(id) {
		this->denumireMateriePrima = nullptr;
		this->stoc = 0;
	}

	MateriePrima(int id, const char* denumire, int stoc) : idMateriePrima(id) {
		if (denumire != nullptr && strlen(denumire) >= 3)
		{
			this->denumireMateriePrima = new char[strlen(denumire) + 1];
			strcpy(this->denumireMateriePrima, denumire);
		}
		else
			this->denumireMateriePrima = nullptr;
		if (stoc >= 0)
			this->stoc = stoc;
		else
			this->stoc = 0;
	}

	MateriePrima(const MateriePrima& m) : idMateriePrima(m.idMateriePrima)
	{
		if (m.denumireMateriePrima != nullptr)
		{
			this->denumireMateriePrima = new char[strlen(m.denumireMateriePrima) + 1];
			strcpy(this->denumireMateriePrima, m.denumireMateriePrima);
		}
		else
			this->denumireMateriePrima = nullptr;
		this->stoc = m.stoc;
	}

	MateriePrima& operator=(const MateriePrima& m)
	{
		if (this != &m)
		{
			if (this->denumireMateriePrima != nullptr)
			{
				delete[] this->denumireMateriePrima;
				this->denumireMateriePrima = nullptr;
			}
			if (m.denumireMateriePrima != nullptr)
			{
				this->denumireMateriePrima = new char[strlen(m.denumireMateriePrima) + 1];
				strcpy(this->denumireMateriePrima, m.denumireMateriePrima);
			}
			else
				this->denumireMateriePrima = nullptr;
			this->stoc = m.stoc;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const MateriePrima& m) {
		out << "\nId mp: " << m.idMateriePrima;
		out << "\nDenumire mp: ";
		if (m.denumireMateriePrima != nullptr)
			out << m.denumireMateriePrima;
		else
			out << " - ";
		out << "\nCantitate mp: " << m.stoc;
		return out;
	}

	friend istream& operator>>(istream& in, MateriePrima& m)
	{
		delete[] m.denumireMateriePrima;
		m.denumireMateriePrima = nullptr;
		cout << "\nDenumire mp: ";
		char buffer[30];
		in >> buffer;
		if (buffer != nullptr)
		{
			m.denumireMateriePrima = new char[strlen(buffer) + 1];
			strcpy(m.denumireMateriePrima, buffer);
		}
		else
			m.denumireMateriePrima = nullptr;
		cout << "\nCantitate: ";
		int val;
		in >> val;
		if (val >= 0)
			m.stoc = val;
		else
			m.stoc = 0;
		return in;

	}

	bool operator!()
	{
		if (this->stoc == 0)
			return true;
		else
			return true;
	}

	MateriePrima& operator+=(int stocNou)
	{
		if (stocNou > 0)
			this->stoc += stocNou;
	}

	int scadeStoc(int stocNou)
	{
		if (stocNou > 0)
		{
			if (this->stoc - stocNou >= 0)
			{
				this->stoc -= stocNou;
			}
			else
				throw new CustomException("\nStoc indisponibil!");
		}
		else
			throw new CustomException("\nInput invalid!");
	}

	~MateriePrima() {
		if (this->denumireMateriePrima != nullptr)
		{
			delete[] this->denumireMateriePrima;
			this->denumireMateriePrima = nullptr;
		}
	}
	
	friend class Stoc;
	friend class Retetar;
	friend class Produs;
};
class Stoc 
{
	int nrMateriiPrime;
	MateriePrima** materiiPrime;
public:
	
	void setStoc(int nrMateriiPrime, MateriePrima** materiiPrime)
	{
		if (nrMateriiPrime > 0 && materiiPrime != nullptr)
		{
			for (int i = 0; i < this->nrMateriiPrime; i++)
			{
				delete this->materiiPrime[i];
				this->materiiPrime[i] = nullptr;
			}
			delete[] this->materiiPrime;
			this->materiiPrime = nullptr;
			this->nrMateriiPrime = nrMateriiPrime;
			this->materiiPrime = new MateriePrima * [this->nrMateriiPrime];
			for (int i = 0; i < this->nrMateriiPrime; i++)
			{
				this->materiiPrime[i] = new MateriePrima(*materiiPrime[i]);
			}
		}
		else
			throw new CustomException("\nInput invalid!");

	}

	int getNrMateriiPrime()
	{
		return this->nrMateriiPrime;
	}

	MateriePrima getMateriePrima(int index)
	{
		return *this->materiiPrime[index];
	}

	int getStocMateriePrima(int id)
	{
		if (this->nrMateriiPrime > 0 && this->materiiPrime != nullptr)
		{
			for (int i = 0; i < this->nrMateriiPrime; i++)
			{
				if (this->materiiPrime[i]->idMateriePrima == id)
					return this->materiiPrime[i]->stoc;
			}
			throw new CustomException("\nNu exista materii prime cu acest id!");

		}
		else
			return 0;
	}

	Stoc(string denumire)
	{
		this->nrMateriiPrime = 0;
		this->materiiPrime = nullptr;
	}

	Stoc(int nrMateriiPrime, MateriePrima** materiiPrime)
	{
		if (nrMateriiPrime > 0 && materiiPrime != nullptr)
		{
			this->nrMateriiPrime = nrMateriiPrime;
			this->materiiPrime = new MateriePrima*[this->nrMateriiPrime];
			for (int i = 0; i < this->nrMateriiPrime; i++)
			{
				this->materiiPrime[i] = new MateriePrima(*materiiPrime[i]);
			}
		}
		else
		{
			this->nrMateriiPrime = 0;
			this->materiiPrime = nullptr;
		}
	}

	Stoc(const Stoc& s)
	{
		this->nrMateriiPrime = s.nrMateriiPrime;
		if (s.materiiPrime != nullptr && s.nrMateriiPrime > 0)
		{
			this->materiiPrime = new MateriePrima*[this->nrMateriiPrime];
			for (int i = 0; i < s.nrMateriiPrime; i++)
				this->materiiPrime[i] = new MateriePrima(*s.materiiPrime[i]);
		}
		else
			this->materiiPrime = nullptr;
	}

	Stoc& operator=(const Stoc& s)
	{
		if (this != &s)
		{
			for (int i = 0; i < this->nrMateriiPrime; i++)
			{
				delete this->materiiPrime[i];
				this->materiiPrime[i] = nullptr;
			}
			delete[] this->materiiPrime;
			this->materiiPrime = nullptr;
			this->nrMateriiPrime = s.nrMateriiPrime;
			if (s.materiiPrime != nullptr && s.nrMateriiPrime > 0)
			{
				this->materiiPrime = new MateriePrima*[this->nrMateriiPrime];
				for (int i = 0; i < s.nrMateriiPrime; i++)
					this->materiiPrime[i] = new MateriePrima(*s.materiiPrime[i]);
			}
			else
				this->materiiPrime = nullptr;

		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Stoc s)
	{
		out << "\nNumar materii prime: " << s.nrMateriiPrime;
		out << "\nMaterii prime: ";
		if (s.nrMateriiPrime > 0 && s.materiiPrime != nullptr)
		{
			for (int i = 0; i < s.nrMateriiPrime; i++)
				out << endl << *s.materiiPrime[i];
		}
		else
			cout << " - ";
		return out;
	}

	friend istream& operator>>(istream& in, Stoc& s)
	{
		for (int i = 0; i < s.nrMateriiPrime; i++)
		{
			delete s.materiiPrime[i];
			s.materiiPrime[i] = nullptr;
		}
		delete[] s.materiiPrime;
		s.materiiPrime = nullptr;
		cout << "\nNumar materii prime: ";
		int val;
		in >> val;
		if (val > 0)
		{
			s.nrMateriiPrime = val;
			s.materiiPrime = new MateriePrima*[s.nrMateriiPrime];
			for (int i = 0; i < s.nrMateriiPrime; i++)
			{
				int aux;
				cout << "\nId mp: ";
				in >> aux;
				s.materiiPrime[i] = new MateriePrima(aux);
				in >> *s.materiiPrime[i];
			}
		}
		else
		{
			s.nrMateriiPrime = 0;
			s.materiiPrime = nullptr;
		}
		return in;
	}

	void adaugaMateriePrima(MateriePrima* m)
	{
		Stoc copie = *this;
		for (int i = 0; i < this->nrMateriiPrime; i++)
		{
			delete this->materiiPrime[i];
			this->materiiPrime[i] = nullptr;
		}
		delete[] this->materiiPrime;
		this->materiiPrime = nullptr;
		this->materiiPrime = new MateriePrima * [this->nrMateriiPrime+1];
		for (int i = 0; i < this->nrMateriiPrime; i++)
		{
			this->materiiPrime[i] = new MateriePrima(*copie.materiiPrime[i]);
		}
		this->materiiPrime[this->nrMateriiPrime] = new MateriePrima(*m);
		this->nrMateriiPrime++;

	}

	void scadeStocul(int id, int stoc)
	{
		if (this->nrMateriiPrime > 0 && this->materiiPrime != nullptr)
		{
			for (int i = 0; i < this->nrMateriiPrime; i++)
			{
				if (this->materiiPrime[i]->idMateriePrima == id)
				{
					this->materiiPrime[i]->scadeStoc(stoc);
					return;
				}
			}
			throw new CustomException("\nNu exista materii prime cu acest id!");
		}
		else
			throw new CustomException("\nNu exista materii prime in stoc!");

	}

	void suplinesteStoc(int id, int stoc)
	{
		if (this->nrMateriiPrime > 0 && this->materiiPrime != nullptr)
		{
			for (int i = 0; i < this->nrMateriiPrime; i++)
			{
				if (this->materiiPrime[i]->idMateriePrima == id)
				{
					this->materiiPrime[i]->stoc+=(stoc);
					return;
				}
			}
			throw new CustomException("\nNu exista materii prime cu acest id!");
		}
		else
			throw new CustomException("\nNu exista materii prime in stoc!");
	}

	MateriePrima& operator[](int id)
	{
		if (this->nrMateriiPrime > 0 && this->materiiPrime != nullptr)
		{
			for (int i = 0; i < this->nrMateriiPrime; i++)
			{
				if (this->materiiPrime[i]->idMateriePrima == id)
					return *materiiPrime[i];
			}
			throw new CustomException("\nNu exista materii prime cu acest id!");
		}
		else
			throw new CustomException("\nNu exista materii prime in stoc!");
	}

	~Stoc()
	{
		for (int i = 0; i < this->nrMateriiPrime; i++)
		{
			delete this->materiiPrime[i];
			this->materiiPrime[i] = nullptr;
		}
		delete[] this->materiiPrime;
		this->materiiPrime = nullptr;
	}
	friend class Retetar;
	friend class Produs;
	friend class Comanda;
	
};

class Retetar {
	string denumireReteta;
	int nrMateriiPrimeNecesare;
	MateriePrima** materiePrimaNecesara;
	int timpPreparare;
public:
	const string getDenumireReteta()
	{
		if (this->denumireReteta != "")
		{
			return this->denumireReteta;
		}
		else
			return " - ";
	}

	void setDenumireReteta(string denumire)
	{
		if (denumire.length() >= 3)
			this->denumireReteta = denumire;
	}
	int getCantitateMateriePrimaNecesara(int id) const
	{
		if (materiePrimaNecesara != nullptr)
		{
			if (id > 0 && id < this->nrMateriiPrimeNecesare)
				for (int i = 0; i < this->nrMateriiPrimeNecesare; i++)
					if (this->materiePrimaNecesara[i]->idMateriePrima == id)
						return this->materiePrimaNecesara[i]->stoc;
		}
		else
			throw new CustomException("\nVECTOR FARA ELEMENTE!");
	}
	int getNrMateriiPrimeNecesare() const
	{
		return this->nrMateriiPrimeNecesare;
	}

	void setMateriiPrimeNecesare(int nr, MateriePrima** materii)
	{
		if (nr > 0 && materii != nullptr)
		{
			for (int i = 0; i < this->nrMateriiPrimeNecesare; i++)
			{
				delete this->materiePrimaNecesara[i];
				this->materiePrimaNecesara[i] = nullptr;
			}
			delete[] this->materiePrimaNecesara;
			this->materiePrimaNecesara = nullptr;
			this->nrMateriiPrimeNecesare = nr;
			this->materiePrimaNecesara = new MateriePrima * [this->nrMateriiPrimeNecesare];
			for (int i = 0; i < this->nrMateriiPrimeNecesare; i++)
			{
				this->materiePrimaNecesara[i] = new MateriePrima(*materii[i]);
			}
		}
		else
			throw new CustomException("\nInput invalid!");
	}

	int getTimpPreparare()
	{
		return this->timpPreparare;
	}

	void setTimpPreparare(int timp)
	{
		if (timp >= 5)
			this->timpPreparare = timp;
	}

	MateriePrima& getMateriePrimaNecesara(int i) const
	{
		if (this->nrMateriiPrimeNecesare > 0 && this->materiePrimaNecesara != nullptr)
		{
					return *materiePrimaNecesara[i];
		}
		else
			throw new CustomException("\nNu exista materii prime in stoc!");
	}

	Retetar()
	{
		this->denumireReteta = "N/A";
		this->nrMateriiPrimeNecesare = 0;
		this->materiePrimaNecesara = nullptr;
		this->timpPreparare = 0;
	}
	Retetar(string denumire)
	{
		if (denumire != "")
			this->denumireReteta = denumire;
		else
			this->denumireReteta = "N/A";
		this->nrMateriiPrimeNecesare = 0;
		this->materiePrimaNecesara = nullptr;
		this->timpPreparare = 0;
	}

	Retetar(string denumire, int nrMateriiPrime, MateriePrima** materiiPrime, int timp)
	{
		if (denumire != "")
			this->denumireReteta = denumire;
		else
			this->denumireReteta = "N/A";
		if (nrMateriiPrime > 0 && materiiPrime != nullptr)
		{
			this->nrMateriiPrimeNecesare = nrMateriiPrime;
			this->materiePrimaNecesara = new MateriePrima * [this->nrMateriiPrimeNecesare];
			for (int i = 0; i < this->nrMateriiPrimeNecesare; i++)
			{
				this->materiePrimaNecesara[i] = new MateriePrima(*materiiPrime[i]);
			}
		}
		else
		{
			this->nrMateriiPrimeNecesare = 0;
			this->materiePrimaNecesara = nullptr;
		}
		if (timp >= 5)
			this->timpPreparare = timp;
		else
			this->timpPreparare = 0;
	}

	Retetar(const Retetar& r)
	{
		this->denumireReteta = r.denumireReteta;
		if (r.nrMateriiPrimeNecesare > 0 && r.materiePrimaNecesara != nullptr)
		{
			this->nrMateriiPrimeNecesare = r.nrMateriiPrimeNecesare;
			this->materiePrimaNecesara = new MateriePrima * [this->nrMateriiPrimeNecesare];
			for (int i = 0; i < this->nrMateriiPrimeNecesare; i++)
			{
				this->materiePrimaNecesara[i] = new MateriePrima(*r.materiePrimaNecesara[i]);
			}
		}
		else
		{
			this->nrMateriiPrimeNecesare = 0;
			this->materiePrimaNecesara = nullptr;
		}

		this->timpPreparare = r.timpPreparare;
	}

	Retetar& operator=(const Retetar& r)
	{
		if (this != &r)
		{
			for (int i = 0; i < this->nrMateriiPrimeNecesare; i++)
			{
				delete this->materiePrimaNecesara[i];
				this->materiePrimaNecesara[i] = nullptr;
			}
			delete[] this->materiePrimaNecesara;
			this->materiePrimaNecesara = nullptr;
			this->denumireReteta = r.denumireReteta;
			if (r.nrMateriiPrimeNecesare > 0 && r.materiePrimaNecesara != nullptr)
			{
				this->nrMateriiPrimeNecesare = r.nrMateriiPrimeNecesare;
				this->materiePrimaNecesara = new MateriePrima * [this->nrMateriiPrimeNecesare];
				for (int i = 0; i < this->nrMateriiPrimeNecesare; i++)
				{
					this->materiePrimaNecesara[i] = new MateriePrima(*r.materiePrimaNecesara[i]);
				}
			}
			else
			{
				this->nrMateriiPrimeNecesare = 0;
				this->materiePrimaNecesara = nullptr;
			}

			this->timpPreparare = r.timpPreparare;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Retetar& r)
	{
		out << "\nDenumire reteta: " << r.denumireReteta;
		out << "\nNumar materii prime necesare: " << r.nrMateriiPrimeNecesare;
		out << "\nMaterii prime necesare: ";
		if (r.materiePrimaNecesara != nullptr)
		{
			for (int i = 0; i < r.nrMateriiPrimeNecesare; i++)
				out << *r.materiePrimaNecesara[i];
		}
		else
			out << " - ";
		out << "\nTimp de preparare: " << r.timpPreparare;
		return out;
	}

	friend istream& operator>>(istream& in, Retetar& r)
	{
		for (int i = 0; i < r.nrMateriiPrimeNecesare; i++)
		{
			delete r.materiePrimaNecesara[i];
			r.materiePrimaNecesara[i] = nullptr;
		}
		delete[] r.materiePrimaNecesara;
		r.materiePrimaNecesara = nullptr;
		cout << "\nDenumire reteta: ";
		in >> r.denumireReteta;
		cout << "\nNumar materii prime necesare: ";
		int aux;
		in >> aux;
		if (aux > 0)
		{
			r.nrMateriiPrimeNecesare = aux;
			r.materiePrimaNecesara = new MateriePrima * [r.nrMateriiPrimeNecesare];
			int id;
			for (int i = 0; i < r.nrMateriiPrimeNecesare; i++)
			{
				cout << "\nId materie prima necesara: ";
				in >> id;
				r.materiePrimaNecesara[i] = new MateriePrima(id);
				in >> *r.materiePrimaNecesara[i];
				
			}
		}
		else
			throw new CustomException("\nInput invalid! ");
		cout << "\nTimpul de preparare: ";
		in >> aux;
		if (aux >= 5)
			r.timpPreparare = aux;
		else
			throw new CustomException("\nInput invalid! ");
		return in;
	}

	Retetar& operator+(MateriePrima* m)
	{
		Retetar copie = *this;
		for (int i = 0; i < this->nrMateriiPrimeNecesare; i++)
		{
			delete this->materiePrimaNecesara[i];
			this->materiePrimaNecesara[i] = nullptr;
		}
		delete[] this->materiePrimaNecesara;
		this->materiePrimaNecesara = nullptr;
		this->materiePrimaNecesara = new MateriePrima * [this->nrMateriiPrimeNecesare + 1];
		for (int i = 0; i < this->nrMateriiPrimeNecesare; i++)
		{
			this->materiePrimaNecesara[i] = new MateriePrima(*copie.materiePrimaNecesara[i]);
		}
		this->materiePrimaNecesara[this->nrMateriiPrimeNecesare] = new MateriePrima(*m);
		this->nrMateriiPrimeNecesare++;
		return *this;
	}

	Retetar& operator-(int id)
	{
		if (this->nrMateriiPrimeNecesare > 0 && this->materiePrimaNecesara != nullptr)
		{
			if (id >= 0)
			{
				bool ok = 0;
				int nr = 0;
				for (int i = 0; i < this->nrMateriiPrimeNecesare; i++)
				{
					if (this->materiePrimaNecesara[i]->idMateriePrima == id)
					{
						ok = 1;
						nr++;
					}
				}
				if (ok)
				{
					Retetar copie = *this;
					int k = 0;
					for (int i = 0; i < this->nrMateriiPrimeNecesare; i++)
					{
						delete this->materiePrimaNecesara[i];
						this->materiePrimaNecesara[i] = nullptr;
					}
					delete[] this->materiePrimaNecesara;
					this->materiePrimaNecesara = nullptr;
					this->materiePrimaNecesara = new MateriePrima * [this->nrMateriiPrimeNecesare - nr];
					for (int i = 0; i < this->nrMateriiPrimeNecesare; i++)
					{
						if (copie.materiePrimaNecesara[i]->idMateriePrima != id)
						{
							this->materiePrimaNecesara[k] = new MateriePrima(*copie.materiePrimaNecesara[i]);
							k++;
						}
					}
					this->nrMateriiPrimeNecesare -= nr;
				}
				else
					throw new CustomException("\nId invalid!");
			}
			else
				throw new CustomException("\nInput invalid!");
		}
		else
			throw new CustomException("\nProdusul nu contine materii prime!");
		return *this;
	}

	//pre-incrementare
	Retetar& operator++()
	{
		this->timpPreparare++;
		return *this;
	}

	//post-incrementare
	Retetar& operator++(int)
	{
		Retetar copie = *this;
		this->timpPreparare++;
		return copie;
	}

	~Retetar() {
		for (int i = 0; i < this->nrMateriiPrimeNecesare; i++)
		{
			delete this->materiePrimaNecesara[i];
			this->materiePrimaNecesara[i] = nullptr;
		}
		delete[] this->materiePrimaNecesara;
		this->materiePrimaNecesara = nullptr;
	}
	friend class Produs;
};


enum CategorieProdus { Aperitiv = 1, FelPrincipal = 2, Desert = 3, Bautura = 4 };
class Produs {
	const int idProdus;
	string denumireProdus;
	Retetar* retetarProdus;
	CategorieProdus categorieProdus;
	float pretProdus;
	int gramajProdus;
	int nrCalorii;
	static int contorIdProdus;
public:
	Produs() :idProdus(contorIdProdus++)
	{
		this->denumireProdus = "N/A";
		this->retetarProdus = nullptr;
		this->categorieProdus = Aperitiv;
		this->pretProdus = 0;
		this->gramajProdus = 0;
		this->nrCalorii = 0;

	}
	Produs(string denumireProdus, Retetar* retetarProdus, CategorieProdus categorieProdus):idProdus(contorIdProdus++)
	{
		if (denumireProdus != "" && denumireProdus.length() >= 3)
			this->denumireProdus = denumireProdus;
		else
			this->denumireProdus = "N/A";
		if (retetarProdus != nullptr)
		{
			this->retetarProdus = new Retetar(*retetarProdus);

		}
		else
		{
			this->retetarProdus = nullptr;
		}
		this->categorieProdus = categorieProdus;
		this->pretProdus = 0;
		this->gramajProdus = 0;
		this->nrCalorii = 0;
	}

	Produs(string denumireProdus,Retetar * retetarProdus, CategorieProdus categorieProdus, float pretProdus, int gramajProdus, int nrCalorii) :idProdus(contorIdProdus++)
	{
		if (denumireProdus != "" && denumireProdus.length() >= 3)
			this->denumireProdus = denumireProdus;
		else
			this->denumireProdus = "N/A";
		if (retetarProdus != nullptr)
		{
			this->retetarProdus = new Retetar(*retetarProdus);

		}
		else
		{
			this->retetarProdus = nullptr;
		}
		this->categorieProdus = categorieProdus;
		if (pretProdus >= 10)
			this->pretProdus = pretProdus;
		else
			this->pretProdus = 0;
		if (gramajProdus >= 50)
			this->gramajProdus = gramajProdus;
		else
			this->gramajProdus = 0;
		if (nrCalorii >= 50)
			this->nrCalorii = nrCalorii;
		else
			this->nrCalorii = 0;
	}

	Produs(const Produs& p) :idProdus(p.idProdus)
	{
		this->denumireProdus = p.denumireProdus;
		if (p.retetarProdus != nullptr)
		{
			this->retetarProdus = new Retetar(*p.retetarProdus);

		}
		else
		{
			this->retetarProdus = nullptr;
		}
		this->categorieProdus = p.categorieProdus;
		this->pretProdus = p.pretProdus;
		this->gramajProdus = p.gramajProdus;
		this->nrCalorii = p.nrCalorii;
	}

	Produs& operator=(const Produs& p)
	{
		if (this != &p)
		{
			delete this->retetarProdus;
			this->retetarProdus = nullptr;
			this->denumireProdus = p.denumireProdus;
			if (p.retetarProdus != nullptr)
			{
				this->retetarProdus = new Retetar(*p.retetarProdus);

			}
			else
			{
				this->retetarProdus = nullptr;
			}
			this->categorieProdus = p.categorieProdus;
			this->pretProdus = p.pretProdus;
			this->gramajProdus = p.gramajProdus;
			this->nrCalorii = p.nrCalorii;
		}
		return *this;
	}

	void setDenumireProdus(string denumireProdus)
	{
		if (denumireProdus != "" && denumireProdus.length() >= 3)
			this->denumireProdus = denumireProdus;
		else
			throw new CustomException("\nInput invalid!");
	}

	int getidProdus()
	{
		return this->idProdus;
	}
	string getDenumireProdus()
	{
		return this->denumireProdus;
	}

	void setRetetar(Retetar* retetarProdus)
	{
		if (retetarProdus != nullptr)
		{
			delete this->retetarProdus;
			this->retetarProdus = nullptr;
			this->retetarProdus = new Retetar(*retetarProdus);

		}
		else
			throw new CustomException("\nInput invalid!");
	}

	const Retetar& getRetetar()
	{
		return *this->retetarProdus;
	}

	void setCategorieProdus(CategorieProdus categorieProdus)
	{
		this->categorieProdus = categorieProdus;
	}
	CategorieProdus getCategorieProdus()
	{
		return this->categorieProdus;
	}

	void setPretProdus(float pretProdus)
	{
		if (pretProdus >= 10)
			this->pretProdus = pretProdus;
		else
			throw new CustomException("\nInput invalid!");
	}

	float getPretProdus()
	{
		return this->pretProdus;
	}

	void setGramajProdus(int gramajProdus)
	{
		if (gramajProdus >= 50)
			this->gramajProdus = gramajProdus;
		else
			throw new CustomException("\nInput invalid!");
	}

	int getGramajProdus()
	{
		return this->gramajProdus;
	}

	void setNrCalorii(int nrCalorii)
	{
		if (nrCalorii >= 50)
			this->nrCalorii = nrCalorii;
		else
			throw new CustomException("\nInput invalid!");
	}

	int getNrCalorii()
	{
		return this->nrCalorii;
	}

	bool operator>=(int calorii)
	{
		if (this->nrCalorii >= calorii)
			return true;
		else
			return false;
	}

	explicit operator float()
	{
		return this->pretProdus;
	}

	friend ostream& operator<<(ostream& out, const Produs p)
	{
		out << "\nId produs: " << p.idProdus;
		out << "\nDenumire produs: " << p.denumireProdus;
		out << "\nRetetar produs: ";
		if (p.retetarProdus != nullptr)
			out << *p.retetarProdus;
		else
			out << " - ";
		out << "\nCategorie produs: ";
		switch (p.categorieProdus)
		{
		case Aperitiv:
			out << "Aperitiv";
			break;
		case FelPrincipal:
			out << "Fel principal";
			break;
		case Desert:
			out << "Desert";
			break;
		case Bautura:
			out << "Bautura";
			break;
		default:
			out << "N/A";
			break;
		}
		out << "\nPret produs: " << p.pretProdus;
		out << "\nGramaj produs: " << p.gramajProdus;
		out << "\nNumar calorii: " << p.nrCalorii;
		return out;
	}

	friend istream& operator>>(istream& in, Produs& p)
	{

		delete p.retetarProdus;
		p.retetarProdus = nullptr;
		cout << "\nDenumire produs: ";
		in >> p.denumireProdus;
		cout << "\nRetetar produs: ";
		p.retetarProdus = new Retetar();
		in >> *p.retetarProdus;
		cout << "\nCategorie produs (1-Aperitiv, 2-Fel principal, 3-Desert, 4-Bautura): ";
		int val;
		in >> val;
		switch (val)
		{
		case 1:
			p.categorieProdus = Aperitiv;
			break;
		case 2:
			p.categorieProdus = FelPrincipal;
			break;
		case 3:
			p.categorieProdus = Desert;
			break;
		case 4:
			p.categorieProdus = Bautura;
			break;
		default:
			p.categorieProdus = Aperitiv;
			break;
		}
		cout << "\nPret produs: ";
		float aux1;
		in >> aux1;
		if (aux1 >= 10)
			p.pretProdus = aux1;
		else
			throw new CustomException("\nInput invalid");
		int aux2;
		cout << "\nGramaj produs: ";
		in >> aux2;
		if (aux2 >= 50)
			p.gramajProdus = aux2;
		else
			throw new CustomException("\nInput invalid");
		cout << "\nNr calorii: ";
		in >> aux2;
		if (aux2 >= 50)
			p.nrCalorii = aux2;
		else
			throw new CustomException("\nInput invalid");
		return in;

	}

	~Produs()
	{
		delete this->retetarProdus;
		this->retetarProdus = nullptr;
	}

	friend class Comanda;
	friend class Meniu;
};
int Produs::contorIdProdus = 1;

class Meniu {
	int nrProduse;
	Produs** listaProduse;
public:
	Meniu(string denumire)
	{
		this->nrProduse = 0;
		this->listaProduse = nullptr;
	}
	Meniu()
	{
		this->nrProduse = 0;
		this->listaProduse = nullptr;
	}

	Meniu(int nrProduse, Produs** listaProduse)
	{
		if (nrProduse > 0 && listaProduse != nullptr)
		{
			this->nrProduse = nrProduse;
			this->listaProduse = new Produs * [this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->listaProduse[i] = new Produs(*listaProduse[i]);
			}
		}
		else
		{
			this->nrProduse = 0;
			this->listaProduse = nullptr;
		}
	}

	Meniu(const Meniu& m)
	{
		if (m.nrProduse > 0 && m.listaProduse != nullptr)
		{
			this->nrProduse = m.nrProduse;
			this->listaProduse = new Produs * [this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->listaProduse[i] = new Produs(*m.listaProduse[i]);
			}
		}
		else
		{
			this->nrProduse = 0;
			this->listaProduse = nullptr;
		}
	}

	Meniu& operator=(const Meniu& m)
	{
		if (this != &m)
		{
			for (int i = 0; i < this->nrProduse; i++)
			{
				delete this->listaProduse[i];
				this->listaProduse[i] = nullptr;
			}
			delete[] this->listaProduse;
			this->listaProduse = nullptr;
			if (m.nrProduse > 0 && m.listaProduse != nullptr)
			{
				this->nrProduse = m.nrProduse;
				this->listaProduse = new Produs * [this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++)
				{
					this->listaProduse[i] = new Produs(*m.listaProduse[i]);
				}
			}
			else
			{
				this->nrProduse = 0;
				this->listaProduse = nullptr;
			}
		}
		return *this;
	}
	int getNrProduse()
	{
		return this->nrProduse;
	}

	Produs& getListaProduse(int i)
	{
		if (i >= 0 && i < this->nrProduse)
			return *this->listaProduse[i];
	}

	friend ostream& operator<<(ostream& out, const Meniu& m)
	{
		out << "\nNumar produse disponibile: " << m.nrProduse;
		out << "\nProduse disponibile: ";
		if (m.nrProduse > 0 && m.listaProduse != nullptr)
		{
			for (int i = 0; i < m.nrProduse; i++)
			{
				out << "\nId produs: " << m.listaProduse[i]->getidProdus();
				out << "\nDenumire produs: " << m.listaProduse[i]->getDenumireProdus();
				out << "\nCategorie produs: ";
				switch (m.listaProduse[i]->getCategorieProdus())
				{
				case Aperitiv:
					out << "Aperitiv";
					break;
				case FelPrincipal:
					out << "Fel principal";
					break;
				case Desert:
					out << "Desert";
					break;
				case Bautura:
					out << "Bautura";
					break;
				default:
					out << "N/A";
					break;
				}
				out << "\nPret produs: " << m.listaProduse[i]->getPretProdus();
				out << "\nGramaj produs: " << m.listaProduse[i]->getGramajProdus();
				out << "\nNr calorii: " << m.listaProduse[i]->getNrCalorii();
				out << endl;
			}
		}
		else
			out << " - ";
		return out;
	}

	friend istream& operator>>(istream& in, Meniu& m)
	{
		for (int i = 0; i < m.nrProduse; i++)
		{
			delete m.listaProduse[i];
			m.listaProduse[i] = nullptr;
		}
		delete[] m.listaProduse;
		m.listaProduse = nullptr;
		cout << "\nNumar produse disponibile: ";
		in >> m.nrProduse;
		if (m.nrProduse > 0)
		{
			m.listaProduse = new Produs*[m.nrProduse];
			for (int i = 0; i < m.nrProduse; i++)
			{
				m.listaProduse[i] = new Produs();
				in >> *m.listaProduse[i];
			}
		}
		else
		{
			m.nrProduse = 0;
			m.listaProduse = nullptr;
		}
		return in;
	}

	Meniu afisarePeCategorie(CategorieProdus categorieProdus)
	{
		if (this->nrProduse > 0 && this->listaProduse != nullptr)
		{
			int nr = 0;
			for (int i = 0; i < this->nrProduse; i++)
			{
				if (this->listaProduse[i]->getCategorieProdus() == categorieProdus)
					nr++;
			}
			Meniu m = *this;
			for (int i = 0; i < this->nrProduse; i++)
			{
				delete m.listaProduse[i];
				m.listaProduse[i] = nullptr;
			}
			delete[] m.listaProduse;
			m.listaProduse = nullptr;
			m.nrProduse = nr;
			int k = 0;
			m.listaProduse = new Produs * [m.nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				if (this->listaProduse[i]->getCategorieProdus() == categorieProdus)
				{
					m.listaProduse[k] = new Produs(*this->listaProduse[i]);
					k++;
				}
			}
			return m;

		}
		else
			throw new CustomException("\nMeniul nu are produse!");
	}
	string afisareDenumireDupaId (int idProdus)
	{
		if (this->nrProduse > 0 && this->listaProduse != nullptr)
		{
			for (int i = 0; i < this->nrProduse; i++)
			{
				if (this->listaProduse[i]->idProdus == idProdus)
				{
					return this->listaProduse[i]->denumireProdus;
				}
			}
		}
		else
			throw new CustomException("\nINPUT INVALID");
	}
	void afisareDupaId(int idProdus)
	{
		if (this->nrProduse > 0 && this->listaProduse != nullptr)
		{
			bool ok = 1;
			for (int i = 0; i < this->nrProduse; i++)
			{
				if (this->listaProduse[i]->idProdus == idProdus)
				{
					cout << "\nId produs: " << this->listaProduse[i]->idProdus;
					cout << "\nDenumire produs: " << this->listaProduse[i]->denumireProdus;
					cout << "\nCategorie produs: ";
					switch (this->listaProduse[i]->categorieProdus)
					{
					case Aperitiv:
						cout << "Aperitiv";
						break;
					case FelPrincipal:
						cout << "Fel principal";
						break;
					case Desert:
						cout << "Desert";
						break;
					case Bautura:
						cout << "Bautura";
						break;
					default:
						cout << "N/A";
						break;
					}
					cout << "\nPret produs: " << this->listaProduse[i]->pretProdus;
					cout << "\nGramaj produs: " << this->listaProduse[i]->gramajProdus;
					cout << "\nNr calorii: " << this->listaProduse[i]->nrCalorii;
					ok = 0;
				}
			}
			if (ok)
				cout << "\nNu exista produs cu acest id!";
		}
	}

	Produs& acestProdus(int id)
	{
		for (int i = 0; i < this->nrProduse; i++)
		{
			if (this->listaProduse[i]->idProdus == id)
				return *this->listaProduse[i];
		}
		throw new CustomException("\nNU EXISTA PRODUS CU ACEST ID!");
	}

	bool operator==(int id)
	{
		if (this->nrProduse > 0 && this->listaProduse != nullptr)
		{
			for (int i = 0; i < this->nrProduse; i++)
			{
				if (this->listaProduse[i]->idProdus == id)
					return true;
			}
			return false;
		}
		else
			throw new CustomException("\nMENIU FARA ELEMENTE");
	}

	Meniu& adaugaProdus(Produs& p)
	{
			Meniu m = *this;
			for (int i = 0; i < this->nrProduse; i++)
			{
				delete this->listaProduse[i];
				this->listaProduse[i] = nullptr;
			}
			delete[] this->listaProduse;
			this->listaProduse = nullptr;
			this->listaProduse = new Produs * [this->nrProduse + 1];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->listaProduse[i] = new Produs(*m.listaProduse[i]);
			}
			this->listaProduse[this->nrProduse] = new Produs(p);
			this->nrProduse++;
			return *this;
	}

	Meniu& eliminaProdus(int id)
	{
		if (*this == id)
		{
			Meniu m = *this;
			for (int i = 0; i < this->nrProduse; i++)
			{
				delete this->listaProduse[i];
				this->listaProduse[i] = nullptr;
			}
			delete[] this->listaProduse;
			this->listaProduse = nullptr;
			int k = 0;
			this->listaProduse = new Produs * [this->nrProduse - 1];
			for (int i = 0; i < this->nrProduse; i++)
			{
				if (m.listaProduse[i]->idProdus != id)
				{
					this->listaProduse[k] = new Produs(*m.listaProduse[i]);
					k++;
				}
			}
			this->nrProduse--;
			return *this;
		}
		else
			throw new CustomException("\nProdus cu acest ID nu exista!");
	}

	~Meniu()
	{
		for (int i = 0; i < this->nrProduse; i++)
		{
			delete this->listaProduse[i];
			this->listaProduse[i] = nullptr;
		}
		delete[] this->listaProduse;
		this->listaProduse = nullptr;
	}
	friend class Comanda;
};

enum MetodaPlata { Cash = 1, Card = 2 };
class Comanda {
	int nrProduseComandateDistincte;
	int* produseComandate;
	int* cantitateProdusComandat;
	MetodaPlata metodaPlata = MetodaPlata::Cash;
	static Stoc stocMP;
	static Meniu meniuPR;
public:
	static void setStocMP(const Stoc& s)
	{
		Comanda::stocMP = s;
	}

     static Stoc getStocMP()
	{
		return Comanda::stocMP;
	}

	static void setMeniuPR(const Meniu& m)
	{
		Comanda::meniuPR = m;
	}
	Comanda()
	{
		this->nrProduseComandateDistincte = 0;
		this->produseComandate = nullptr;
		this->cantitateProdusComandat = nullptr;
		this->metodaPlata = MetodaPlata::Cash;
	}
	Comanda(int nrProduseComandateDistincte, int* produseComandate, int* cantitateProdusComandat)
	{
		if (nrProduseComandateDistincte > 0)
		{
			this->nrProduseComandateDistincte = nrProduseComandateDistincte;
			this->produseComandate = new int[this->nrProduseComandateDistincte];
			this->cantitateProdusComandat = new int[this->nrProduseComandateDistincte];
			for (int i = 0; i < this->nrProduseComandateDistincte; i++)
			{
				this->produseComandate[i] = produseComandate[i];
				this->cantitateProdusComandat[i] = cantitateProdusComandat[i];
			}
		}
		else
		{
			this->nrProduseComandateDistincte = 0;;
			this->produseComandate = nullptr;
			this->cantitateProdusComandat = nullptr;
		}
	}

	Comanda(int nrProduseComandateDistincte, int* produseComandate, int* cantitateProdusComandat, MetodaPlata metodaPlata)
	{
		if (nrProduseComandateDistincte > 0)
		{
			this->nrProduseComandateDistincte = nrProduseComandateDistincte;
			this->produseComandate = new int[this->nrProduseComandateDistincte];
			this->cantitateProdusComandat = new int[this->nrProduseComandateDistincte];
			for (int i = 0; i < this->nrProduseComandateDistincte; i++)
			{
				this->produseComandate[i] = produseComandate[i];
				this->cantitateProdusComandat[i] = cantitateProdusComandat[i];
			}
		}
		else
		{
			this->nrProduseComandateDistincte = 0;;
			this->produseComandate = nullptr;
			this->cantitateProdusComandat = nullptr;
		}
		this->metodaPlata = metodaPlata;
	}

	Comanda(const Comanda& c)
	{
		if (nrProduseComandateDistincte > 0)
		{
			this->nrProduseComandateDistincte = c.nrProduseComandateDistincte;
			this->produseComandate = new int[this->nrProduseComandateDistincte];
			this->cantitateProdusComandat = new int[this->nrProduseComandateDistincte];
			for (int i = 0; i < this->nrProduseComandateDistincte; i++)
			{
				this->produseComandate[i] = c.produseComandate[i];
				this->cantitateProdusComandat[i] = c.cantitateProdusComandat[i];
			}
		}
		else
		{
			this->nrProduseComandateDistincte = 0;;
			this->produseComandate = nullptr;
			this->cantitateProdusComandat = nullptr;
		}
		this->metodaPlata = c.metodaPlata;
	}

	Comanda& operator=(const Comanda& c)
	{
		if (this != &c)
		{
			delete[] this->produseComandate;
			this->produseComandate = nullptr;
			delete[] this->cantitateProdusComandat;
			this->cantitateProdusComandat = nullptr;
			if (nrProduseComandateDistincte > 0)
			{
				this->nrProduseComandateDistincte = c.nrProduseComandateDistincte;
				this->produseComandate = new int[this->nrProduseComandateDistincte];
				this->cantitateProdusComandat = new int[this->nrProduseComandateDistincte];
				for (int i = 0; i < this->nrProduseComandateDistincte; i++)
				{
					this->produseComandate[i] = c.produseComandate[i];
					this->cantitateProdusComandat[i] = c.cantitateProdusComandat[i];
				}
			}
			else
			{
				this->nrProduseComandateDistincte = 0;;
				this->produseComandate = nullptr;
				this->cantitateProdusComandat = nullptr;
			}
			this->metodaPlata = c.metodaPlata;
		}
		return *this;
	}

	bool verificaStocProdus(int idProdus)
	{
		for(int i = 0; i<Comanda::meniuPR.getNrProduse(); i++)
			if (idProdus == Comanda::meniuPR.getListaProduse(i).getidProdus())
			{
				for (int j = 0; j < Comanda::meniuPR.getListaProduse(i).getRetetar().getNrMateriiPrimeNecesare();j++)
				{
					if (Comanda::meniuPR.getListaProduse(i).getRetetar().getCantitateMateriePrimaNecesara(Comanda::meniuPR.getListaProduse(i).getRetetar().getMateriePrimaNecesara(j).getIdMateriePrima()) > Comanda::stocMP.getStocMateriePrima(Comanda::meniuPR.getListaProduse(i).getRetetar().getMateriePrimaNecesara(j).getIdMateriePrima()))
						return false;
					else
						Comanda::stocMP.scadeStocul(Comanda::meniuPR.getListaProduse(i).getRetetar().getMateriePrimaNecesara(j).getIdMateriePrima(), Comanda::meniuPR.getListaProduse(i).getRetetar().getCantitateMateriePrimaNecesara(Comanda::meniuPR.getListaProduse(i).getRetetar().getMateriePrimaNecesara(j).getIdMateriePrima()));
				}
				return true;
			}
	}

	bool verificaComanda()
	{
		if (this->nrProduseComandateDistincte > 0 && this->produseComandate != nullptr && this->cantitateProdusComandat != nullptr)
		{
			cout << endl;
			bool ok = true;
			for (int i = 0; i < this->nrProduseComandateDistincte; i++)
			{
				int aux = this->cantitateProdusComandat[i];
				while (aux)
				{
					if (this->verificaStocProdus(this->produseComandate[i]))
						aux--;
					else break;
				}
				if (aux == this->cantitateProdusComandat[i])
				{
					cout << "\nProdusul '" << Comanda::meniuPR.afisareDenumireDupaId(this->produseComandate[i]) << "' nu este in stoc!";
					ok = false;
				}
				else
					if (aux == 0)
						cout << "\nProdusul '" << Comanda::meniuPR.afisareDenumireDupaId(this->produseComandate[i]) << "' a fost adaugat in comanda!";
					else
					{
						cout << "\nProdusul '" << Comanda::meniuPR.afisareDenumireDupaId(this->produseComandate[i]) << "' poate fi comandat in " << this->cantitateProdusComandat[i] - aux << " bucati!";
						ok = false;
					}
			}
			return ok;
		}
		else
			throw new CustomException("\nCOMANDA INVALIDA!");
	}

	void inlocuireProdus(int idProdus1, int idProdus2, int cantitate) {
		for (int i = 0; i < this->nrProduseComandateDistincte; i++)
			if (this->produseComandate[i] == idProdus1)
			{
				this->produseComandate[i] = idProdus2;
				this->cantitateProdusComandat[i] = cantitate;
			}
	}

	friend ostream& operator<<(ostream& out, const Comanda& c)
	{
		out << "\nNumar produse distincte comandate: " << c.nrProduseComandateDistincte;
		out << "\nProduse comandate: ";
		if (c.nrProduseComandateDistincte > 0 && c.produseComandate != nullptr && c.cantitateProdusComandat != nullptr)
		{
			for (int i = 0; i < c.nrProduseComandateDistincte; i++)
			{
				for (int j = 0; j < meniuPR.getNrProduse(); j++)
					if (c.produseComandate[i] == meniuPR.getListaProduse(j).getidProdus())
					{
						out << "\nCantitate comandata produs: " << c.cantitateProdusComandat[i];
						meniuPR.afisareDupaId(c.produseComandate[i]);
					}
			}
		}
		else
			out << " - ";
		out << "\nMetoda plata: ";
		switch (c.metodaPlata)
		{
		case Cash:
			out << "Cash";
			break;
		case Card:
			out << "Card";
			break;
		default:
			out << "N/A";
			break;
		}
		return out;
	}

	friend istream& operator>>(istream& in, Comanda& c)
	{
		delete[] c.produseComandate;
		c.produseComandate = nullptr;
		delete[] c.cantitateProdusComandat;
		c.cantitateProdusComandat = nullptr;
		cout << "\nIntroduceti numarul de produse distincte dorite: ";
		int aux;
		in >> aux;
		if (aux > 0)
		{
			c.nrProduseComandateDistincte = aux;
			c.produseComandate = new int[c.nrProduseComandateDistincte];
			c.cantitateProdusComandat = new int[c.nrProduseComandateDistincte];
			for (int i = 0; i < c.nrProduseComandateDistincte; i++)
			{
				cout << "\nIntroduceti id-ul produsului: ";
				in >> c.produseComandate[i];
				cout << "\nIntroduceti cantitatea dorita: ";
				in >> c.cantitateProdusComandat[i];
			}
			cout << "\nIntoduceti metoda de plata: \t1 - CASH \t2 - CARD \t";
			int aux2;
			in >> aux2;
			if (aux2 == 1)
				c.metodaPlata = Cash;
			else
				if (aux2 == 2)
					c.metodaPlata = Card;
		}
		else
			throw new CustomException("\nInput invalid!");
	}

	~Comanda()
	{
		delete[] this->produseComandate;
		this->produseComandate = nullptr;
		delete[] this->cantitateProdusComandat;
		this->cantitateProdusComandat = nullptr;
	}

	// metoda elimina 
};

Stoc Comanda::stocMP("stoc");
Meniu Comanda::meniuPR("meniu");


int main() {
	MateriePrima m1(1, "Lapte", 100);
	MateriePrima m2(2, "Ou", 200);
	MateriePrima m3(3, "Faina", 10000);
	MateriePrima m4(4, "Sos de rosii", 2000);
	MateriePrima m5(5, "Unt", 2000);
	MateriePrima m6(6, "Sare", 10000);
	MateriePrima m7(7, "Sunca", 3000);
	MateriePrima m8(8, "Paste", 10000);
	MateriePrima m9(9, "Rosii", 300);
	MateriePrima m10(10, "Ardei", 350);
	MateriePrima m11(11, "Sprite", 10000);
	MateriePrima m12(12, "Menta", 500);
	MateriePrima m13(13, "Gheata", 1000);
	MateriePrima m14(14, "Sirop de capsuni", 500);

	MateriePrima* materii[14] = { &m1, &m2, &m3, &m4, &m5, &m6, &m7, &m8, &m9, &m10, &m11, &m12, &m13, &m14 };
	Stoc s1(14, materii);

	MateriePrima m101(1, "Lapte", 1);
	MateriePrima m102(2, "Ou", 5);
	MateriePrima m103(3, "Faina", 200);
	MateriePrima m104(4, "Sos de rosii", 100);
	MateriePrima m105(5, "Unt", 50);
	MateriePrima m106(6, "Sare", 20);
	MateriePrima m107(7, "Sunca", 150);
	MateriePrima m108(8, "Paste", 200);
	MateriePrima m109(9, "Rosii", 3);
	MateriePrima m110(10, "Ardei", 2);
	MateriePrima m111(11, "Sprite", 100);
	MateriePrima m112(12, "Menta", 20);
	MateriePrima m113(13, "Gheata", 100);
	MateriePrima m114(14, "Sirop de capsuni", 30);

	MateriePrima* mp1[4] = { &m101, &m102, &m103, &m105 };
	MateriePrima* mp2[6] = { &m102, &m104, &m105, &m106,&m107, &m108 };
	MateriePrima* mp3[5] = { &m101, &m102, &m103, &m105, &m107 };
	MateriePrima* mp4[5] = { &m105, &m106, &m108, &m109, &m110 };
	MateriePrima* mp5[4] = { &m102, &m105, &m106, &m107 };
	MateriePrima* mp6[3] = { &m111, &m112, &m113 };
	MateriePrima* mp7[3] = { &m111, &m114, &m113 };

	Retetar r1("Paine", 4, mp1, 50);
	Retetar r2("Paste cu sunca", 6, mp2, 25);
	Retetar r3("Pizza", 5, mp3, 15);
	Retetar r4("Paste cu legume", 5, mp4, 20);
	Retetar r5("Clatite cu sunca", 4, mp5, 25);
	Retetar r6("Limonada cu menta", 3, mp6, 10);
	Retetar r7("Limonada cu capsuni", 3, mp7, 10);

	Produs p1("Covrig caramelizat", &r1, Desert, 12, 150, 100);
	Produs p2("Paste Carbonara", &r2, FelPrincipal, 35, 250, 350);
	Produs p3("Capricioasa", &r3, FelPrincipal, 40, 400, 250);
	Produs p4("Paste Fresh", &r4, FelPrincipal, 39, 300, 150);
	Produs p5("Clatite cu sunca", &r5, Aperitiv, 25, 120, 200);
	Produs p6("Pizza California", &r3, FelPrincipal, 45, 450, 500);
	Produs p7("Mojito", &r6, Bautura, 30, 300, 150);
	Produs p8("Limonada Primavera", &r7, Bautura, 35, 290, 140);

	Produs* listaProduse[8] = { &p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8 };
	Meniu meniu(8, listaProduse);
	Produs pNou;

	bool exista;
	Comanda c;
	c.setStocMP(s1);
	c.setMeniuPR(meniu);
	CategorieProdus cat = Aperitiv;
	string denumire;
	int idUtilizator = 0, idCategorie = 0, idActiune = 0, valoare = 0;
	float valoaref = 0;
	int id = 0, cantitate;
	bool ok = 1;
	cout << "\nIntroduceti ID utilizator: \t1 - ADMINISTRATOR \t2 - CLIENT \n";
	cin >> idUtilizator;
	if (idUtilizator == 1)
	{
		while (ok)
		{
			cout << "\nIntroduceti ID categorie: \t1 - STOC \t2 - MENIU \t3 - EXIT\n";
			cin >> idCategorie;
			switch (idCategorie)
			{
			case 1:
				cout << "\nBINE AI VENIT IN STOC!" << endl;
				while (ok)
				{
					MateriePrima* ma;
					cout << endl << "\n1 - AFISEAZA STOC\n2 - AFISEAZA STOC DISPONIBIL DE MATERIE PRIMA \n3 - SUPLINESTE STOC MATERIE PRIMA \n4 - SCADE CANTITATE MATERIE PRIMA\n5 - ADAUGA MATERIE PRIMA \n6 - AFISEAZA MATERIE PRIMA \n7 - EXIT \n Introduceti ID instructiune: ";
					cin >> idActiune;
					switch (idActiune)
					{
					case 1:
						cout << "\n***** STOC DISPONIBIL *****" << endl;
						cout << s1;
						break;
					case 2:
						cout << "INTRODUCETI ID MATERIE PRIMA CAUTATA: ";
						cin >> id;
						try
						{
							cout << "CANTITATEA DISPONIBILA ESTE " << s1.getStocMateriePrima(id);
						}
						catch (CustomException* ex)
						{
							cout << endl << ex->getMesaj();
							delete ex;
						}
						break;
					case 3:
						cout << "INTRODUCETI ID MATERIE PRIMA: ";
						cin >> id;
						cout << "\nINTRODUCETi CANTITATE DE SUPINIT: ";
						cin >> cantitate;
						try
						{
							s1.suplinesteStoc(id, cantitate);
							cout << "\nSTOC SUPLINIT!";
						}
						catch (CustomException* ex)
						{
							cout << endl << ex->getMesaj();
							delete ex;
						}
						break;
					case 4:
						cout << "INTRODUCETI ID MATERIE PRIMA: ";
						cin >> id;
						cout << "\nINTRODUCETi CANTITATE DE REDUS: ";
						cin >> cantitate;
						try
						{
							s1.scadeStocul(id, cantitate);
							cout << "\nSTOC REDUS!";
						}
						catch (CustomException* ex)
						{
							cout << endl << ex->getMesaj();
							delete ex;
						}
						break;
					case 5:
						cout << "\nADAUGA MATERIE PRIMA" << endl;
						cout << "\nINTRODUCETI ID MATERIE PRIMA NOUA: ";
						cin >> id;
						ma = new MateriePrima(id);
						cin >> *ma;
						s1.adaugaMateriePrima(ma);
						cout << endl << "\nMATERIE PRIMA ADAUGATA CU SUCCES!";
						break;
					case 6:
						cout << "INTRODUCETI ID MATERIE PRIMA: ";
						cin >> id;
						try
						{
							cout << s1[id];
						}
						catch (CustomException* ex)
						{
							cout << endl << ex->getMesaj();
							delete ex;
						}
						break;
					case 7:
						ok = 0;
						break;
					}
				}
				ok = 1;
				break;
			case 2:
				cout << "\nBINE AI VENIT IN MENIU!" << endl;
				while (ok)
				{
					cout << endl << "\n1 - AFISEAZA MENIU \n2 - AFISEAZA PRODUSE DUPA CATEGORIE \n3 - CAUTA PRODUS  \n4 - ELIMINA PRODUS \n5 - ADAUGA PRODUS \n6 - SETEAZA DENUMIRE PRODUS \n7 - SETEAZA PRET PRODUS \n8 - AFISEAZA RETETA PRODUS \n9 - EXIT \nIntroduceti ID instructiune: ";
					cin >> idActiune;
					switch (idActiune)
					{
					case 1:
						cout << "\n***** MENIU *****" << endl;
						cout << meniu;
						break;
					case 2:
						cout << "\nINTRODUCETI CATEGORIE (1-Aperitiv, 2-Fel principal, 3-Desert, 4-Bautura): ";
						cin >> id;
						switch (id)
						{
						case 1:
							cat = Aperitiv;
							break;
						case 2:
							cat = FelPrincipal;
							break;
						case 3:
							cat = Desert;
							break;
						case 4:
							cat = Bautura;
							break;
						default:
							cat = Aperitiv;
							break;
						}
						cout << meniu.afisarePeCategorie(cat);
						break;
					case 3:
						cout << "\nINTRODUCETI ID PRODUS CAUTAT: ";
						cin >> id;
						meniu.afisareDupaId(id);
						break;
					case 4:
						cout << "\nINTRODUCETI ID PRODUS PE CARE DORITI SA IL ELIMINATI: ";
						cin >> id;
						try
						{
							meniu.eliminaProdus(id);
							cout << "\nPRODUS ELIMINAT!";
						}
						catch (CustomException* ex)
						{
							cout << endl << ex->getMesaj();
							delete ex;
						}
						break;
					case 5:
						cout << "\nADAUGA PRODUS";
						cin >> pNou;
						meniu.adaugaProdus(pNou);
						cout << "\nPRODUS ADAUGAT CU SUCCES!";
						break;
					case 6:
						cout << "\nINTRODUCETI ID PRODUS CARUIA DORITI SA II SCHIMBATI DENUMIRE: ";
						cin >> id;
						cout << "\nINTRODUCETI NOUA DENUMIRE: ";
						cin >> denumire;
						meniu.acestProdus(id).setDenumireProdus(denumire);
						cout << "\nDENUMIRE SETATA!";
						break;
					case 7:
						cout << "\nINTRODUCETI ID PRODUS CARUIA DORITI SA II SCHIMBATI PRETUL: ";
						cin >> id;
						cout << "\nINTRODUCETI NOUL PRET: ";
						cin >> valoaref;
						try
						{
							meniu.acestProdus(id).setPretProdus(valoaref);
							cout << "\nPRET SETAT!";
						}
						catch (CustomException* ex)
						{
							cout << endl << ex->getMesaj();
							delete ex;
						}
						break;
					case 8:
						cout << "\nINTRODUCETI ID PRODUS: ";
						cin >> id;
						cout << "\n***** RETETA PRODUSULUI *****" << endl;
						cout << meniu.acestProdus(id).getRetetar();
						break;
					case 9:
						cout << "\n***** EXIT *****";
						ok = 0;
						break;
					}
				}
				ok = 1;
				break;
			case 3:
				cout << "\n***** EXIT *****";
				ok = 0;
				break;
			}
		}
	}
	else
		if (idUtilizator == 2)
		{
			int ok = 1;
			cout << endl <<  "\nBINE ATI VENIT!" << endl;
			while (ok)
			{
				cout <<  "\nTASTATI: \n1 - ACCESARE MENIU \n2 - PLASARE COMANDA \n3 - PARASIRE APLICATIE \n";
				cin >> idActiune;
				switch (idActiune)
				{
				case 1:
					cout << "\n***** MENIU *****" << endl;
					cout << meniu;
					cout << "\n***** RESTAURANT FANTASY *****" << endl;
					ok = 1; 
					break;
				case 2:
					cout << "\nPLASARE COMANDA";
					cin >> c;
					cout << c;
					while (ok)
					{
						exista = c.verificaComanda();
						if (exista)
						{
							cout << endl << "\nComanda efectuata cu succes!";
							s1 = c.getStocMP();
						}
						else
						{
							cout << "\nTASTATI: 1 - PASTRARE COMANDA \n2 - MODIFICARE PRODUSE CU STOC EPUIZAT \n3 - MODIFICARE COMANDA IN INTREGIME \n4 - ANULARE COMANDA\n";
							cin >> idActiune;
							switch (idActiune)
							{
							case 1:
								cout << endl << "\nComanda efectuata cu succes!";
								s1 = c.getStocMP();
								ok = 0;
								break;
							case 2:
								c.setStocMP(s1);
								int nrProduse, idProdus1, idProdus2, cantitateNoua;
								cout << "\nINTRODUCETI NUMARUL DE PRODUSE PE CARE DORITI SA LE INLOCUITI: ";
								cin >> nrProduse;
								while (nrProduse)
								{
									cout << "\nID-UL PRODUSULUI PE CARE DORITI SA IL INLOCUITI: ";
									cin >> idProdus1;
									cout << "\nID-UL NOULUI PRODUS: ";
									cin >> idProdus2;
									cout << "\nNUMAR DE BUCATI: ";
									cin >> cantitateNoua;
									c.inlocuireProdus(idProdus1, idProdus2, cantitateNoua);
									nrProduse--;
								}
								break;
							case 3:
								c.setStocMP(s1);
								cout << "\nPLASARE COMANDA";
								cin >> c;
								cout << c;
								break;
							case 4:
								c.setStocMP(s1);
								ok = 0;
								break;

							}

						}
					}
					ok = 1;
					break;
				case 3:
					cout << endl << "\nMULTUMIM PENTRU VIZITA!";
					ok = 0;
					break;
				}

			}
		}
		else
			cout << "\nID invalid!"; 
}

