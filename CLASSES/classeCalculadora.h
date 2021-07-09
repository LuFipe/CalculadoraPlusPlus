#ifndef CALC_CLASS
#define CALC_CLASS

#include <iostream>
#include <cmath>

#define nl cout<<endl;

using namespace std;

			/*													*/
			/*					TIPOS E ESTRUTURAS				*/
			/*													*/

enum tipo {OPERANDO, OPERADOR, TRIGONOMETRICO, ABPARENTESE, FEPARENTESE, NADA};
union atom {double num; char oper;};
struct mol {atom val;tipo t;};

					

class Protein{
	private:
	string mRNA;
	mol* tRNA;
	int dim;
	int posicao_O, posicao_I, posicao;
	int fim;
	bool crescente;

	double resultado;

	public:
		void set_M_RNA(string);
		string get_M_RNA(){return mRNA;};

		void set_DIM(int);
		int get_DIM(){return dim;};

		void set_Oper(char, int);
		char get_Oper(int i){return tRNA[i].val.oper;};

		void set_Num(double, int);
		double get_Num(int i){return tRNA[i].val.num;};

		void set_Type(tipo, int);
		tipo get_Type(int i){return tRNA[i].t;};

		void set_posicao_O(int);
		int get_posicao_O(){return posicao_O;};

		void set_posicao_I(int);
		int get_posicao_I(){return posicao_I;};

		void set_posicao(int);
		int get_posicao(){return posicao;};

		void setFim(int);
		int getFim(){return fim;};

		void setCresc(bool);
		bool getCresc(){return crescente;};

		void set_Resultado();
		double get_Resultado(){return resultado;};

		void ShowTab();

		void ShowProtein();
		Protein(string);
		~Protein(){ delete [] tRNA; };
	};

#endif