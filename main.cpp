#include <iostream>
#include <cmath>

#define nl cout<<endl;

using namespace std;

/*															*/
/*					TIPOS E ESTRUTURAS						*/
/*															*/
enum tipo {OPERANDO, OPERADOR, PARENTESE, NADA};
union atom {double num; char oper;};
struct mol {atom val;tipo t;};
	//	typedef mol protein[4] :NÃO FUNCIONA				//
	//	Então faça:											//
	//	"Se não pode passar um elefante por baixo da porta"	//
	//	"Coloque-o em um envelope e passe"					//
struct protein{mol tRNA[50]; int fim;};

/*															*/
/*					 SUB-ROTINAS							*/
/*															*/
void R_RNA(string, protein*, int*);
double Calc(double, char, double);
double CalcExpress(protein*);
void ReducExpres(protein*, char, char);
double CalcExpress(protein*);
void ShowProtein(protein*);


int main(){
	string mRNA;
	protein proteina;
	double resultado = 0;

	char operando;
	int pos=0;

	cout<<"Entre com a expressão";nl
	cin>>mRNA;

	R_RNA(mRNA, &proteina, &pos);
	cout<<"Tamanho da proteina: "<<proteina.fim;nl
	nl
	cout<<"Antes: ";nl
	cout<<"Expressao: "; ShowProtein(&proteina);cout<<" = ";nl
	cout<<"Variavel = "<<resultado;nl
	resultado = CalcExpress(&proteina);
	cout<<"Depois: ";nl
	cout<<"Expressao: "; ShowProtein(&proteina);cout<<" = ";nl
	cout<<"Resultado = "<<resultado;nl


	return 0;
}

void R_RNA(string m_RNA, protein* prot, int* p){
	double numb=0;
	int expInt=1, expDec=0, fatExpDec=0;

	//Atribui a toda a espressão mRNA
	for(int j=0; j<50;j++){
		//Percorre toda M_RNA atribuindo a protein
		if((*p)<m_RNA.length()){
			while(m_RNA[*p] == ' '){
				(*p)++;
			}
			if((m_RNA[*p]=='+')||(m_RNA[*p]=='-')||(m_RNA[*p]=='*')||(m_RNA[*p]=='/')||(m_RNA[*p]=='^')||(m_RNA[*p]=='l')){
				prot->tRNA[j].t = OPERADOR;
				prot->tRNA[j].val.oper = m_RNA[(*p)++];
			}
			else if(m_RNA[*p]== '='){
				prot->fim = j;
				prot->tRNA[j].t = NADA;
				prot->tRNA[j].val.oper = m_RNA[*p];
			}
			else if( (('9'>=m_RNA[*p]) && (m_RNA[*p]>='0')) || (m_RNA[*p] == ',') || (m_RNA[*p] == '.')){
				expInt=1, expDec=0, fatExpDec=0;

				for(int k=(*p);k<m_RNA.length(); k++){
					if(( '9' >= m_RNA[k]) && (m_RNA[k] >= '0')){
						numb = numb*pow(10,expInt) + (m_RNA[k]-48)*pow(10,expDec*fatExpDec);
						expDec--;
					}
					else if ((m_RNA[k] == ',') || (m_RNA[k] == '.')){
						expInt=0;
						fatExpDec=1;
						expDec=-1;
					} else {
						(*p) = k;
						numb = 0;
						break;
					};
					prot->tRNA[j].t = OPERANDO;
					prot->tRNA[j].val.num = numb;
				};
			} else cout<<"Expressão invalida\n";
		};
		if(prot->tRNA[j].val.oper == '=') break;
	};
}

double Calc(double term1, char oper, double term2){
	switch (oper)
	{
	case '+':
		return (term1+term2);
	case '-':
		return (term1-term2);
	case '*':
		return (term1*term2);
	case '/':
		return (term1/term2);
	case '^':
		return (pow(term1,term2));
	case 'l':
		return (log(term1)/log(term2));
	default:
		cout<<"Nao é um operando\n";
		return 0;
	}
}

void ReducExpres(protein* exp, char positivo, char negativo){
	int pre, pos;
	double operador_1, operador_2;
	for(int i=0; i<exp->fim; i++){
		if(exp->tRNA[i].t == OPERADOR){
			if((exp->tRNA[i].val.oper == positivo)||(exp->tRNA[i].val.oper == negativo)){
				pre=i-1;
					do
					{
						if(exp->tRNA[pre].t == OPERANDO){
							operador_1 = exp->tRNA[pre].val.num;
							exp->tRNA[pre].t = NADA;
							break;
						};
					} while (exp->tRNA[pre--].t != OPERANDO);

				pos=i+1;
					do
					{
						if(exp->tRNA[pos].t == OPERANDO){
							operador_2 = exp->tRNA[pos].val.num;
							exp->tRNA[pos].t = NADA;
							break;
						};
					} while (exp->tRNA[pos++].t != OPERANDO);

				exp->tRNA[i].t = OPERANDO;
				exp->tRNA[i].val.num = Calc(operador_1,exp->tRNA[i].val.oper,operador_2);
			}
		}
	}

}

double CalcExpress(protein* expressao){
	double res;
	ReducExpres(expressao, '^','l');
	ReducExpres(expressao, '*', '/');
	ReducExpres(expressao, '+','-');
	for(int i=0; i<expressao->fim; i++){
		if(expressao->tRNA[i].t == OPERANDO){
			res = expressao->tRNA[i].val.num;
		}
	}
	return res;
}

void ShowProtein(protein* prot){
	double a;
	char b;
	for(int i=0; i<prot->fim; i++){
		if(prot->tRNA[i].t == OPERADOR) {
			b = prot->tRNA[i].val.oper;
			cout<<b;
		}
		else if(prot->tRNA[i].t == OPERANDO) {
			a = prot->tRNA[i].val.num;
			cout<<a;
		}
		else continue;
	}
}