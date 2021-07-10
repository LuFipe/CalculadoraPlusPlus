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
		/*					GETTERS					*/
		/*					   &					*/
		/*					SETTERS					*/
	//mRNA
		void set_M_RNA(string);
		string get_M_RNA(){return mRNA;};
	//dim
		void set_DIM(int);
		int get_DIM(){return dim;};
	//tRNA[i].val.oper
		void set_Oper(char, int);
		char get_Oper(int i){return tRNA[i].val.oper;};
	//tRNA[i].val.num
		void set_Num(double, int);
		double get_Num(int i){return tRNA[i].val.num;};
	//tRNA[i].t
		void set_Type(tipo, int);
		tipo get_Type(int i){return tRNA[i].t;};
	//posicao_O
		void set_posicao_O(int);
		int get_posicao_O(){return posicao_O;};
	//posicao_I
		void set_posicao_I(int);
		int get_posicao_I(){return posicao_I;};
	//posicao
		void set_posicao(int);
		int get_posicao(){return posicao;};
	//fim
		void setFim(int);
		int getFim(){return fim;};
	//Crescente
		void setCresc(bool);
		bool getCresc(){return crescente;};
	//Resultado
		void set_Resultado();
		double get_Resultado(){return resultado;};


		/*					SUB-ROTINAS					*/
		/*					ESPECIFICAS					*/
		/*					DA CLASSE					*/
		void ShowProtein();								//Mostra a proteina em forma de Expressao
		void ShowTab();									//Mostra a Proteina em forma de Tabela
		void ReducaoProtein(char, char, int );			//Reduz a proteina calculando os caracteres adicionados
		void Varredura(int, int);						//Varre toda a proteina de forma crescente e decrescente
		double CalcProtein(int, int);					//Calcula toda a Proteina de modo Crescente
		void R_RNA(string);								//Traduz a Expressão (M_RNA - string) para 'Proteinas' (-atomos)

		/*					CONSTRUTOR					*/
		/*						&						*/
		/*					DESTRUTOR					*/
		Protein(string);
		~Protein(){ delete [] tRNA; };
	};

/*					PPROTOTIPO DAS					*/
/*					SUB-ROTINAS						*/
/*													*/
double Calc(double, char, double);					//Opera com dois Numeros e um Operador

#endif