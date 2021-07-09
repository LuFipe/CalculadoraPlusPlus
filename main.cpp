#include <iostream>
#include <cmath>

#define nl cout<<endl;

using namespace std;

/*															*/
/*					TIPOS E ESTRUTURAS						*/
/*															*/
enum tipo {OPERANDO, OPERADOR, ABPARENTESE, FEPARENTESE, NADA};
union atom {double num; char oper;};
struct mol {atom val;tipo t;};
	//	typedef mol protein[4] :NÃO FUNCIONA				//
	//	Então faça:											//
	//	"Se não pode passar um elefante por baixo da porta"	//
	//	"Coloque-o em um envelope e passe"					//
struct protein{mol tRNA[50];int posicao_O, posicao_I; int fim;};

/*															*/
/*					 SUB-ROTINAS							*/
/*															*/
void R_RNA(string, protein*, int*); 						//Traduz a Expressão (M_RNA - string) para 'Proteinas' (-atomos)
double Calc(double, char, double); 							//Opera com 2 numeros
void ReducaoProtein(protein*, char, char, int);				//Reduz a proteina calculando os caracteres adicionados
void VarreduraCrescente(protein*, char, char, int, int);	//Segue ordem crescente de varredura
void VarreduraDecrescente(protein*, char, char, int, int);	//Segue ordem decrescente de varredura
double CalcProteinCresc(protein*, int, int); 				//Calcula toda a Proteina de modo Crescente
double CalcProteinDecres(protein*, int, int);				//Calcula toda a Proteina de modo Decrescente
void ShowProtein(protein*); 								//Mostra toda a proteina


int main(){
	string mRNA;
	protein proteina;
	double resultado = 0;

	char operando;
	int pos=0;

	cout<<"Entre com a expressão";nl
	cin>>mRNA;

	R_RNA(mRNA, &proteina, &pos);
	proteina.posicao_O = 0;
	proteina.posicao_I = proteina.fim;

	cout<<"Tamanho da proteina: "<<proteina.fim;nl
	nl
	cout<<"Antes: ";nl
	cout<<"Expressao: "; ShowProtein(&proteina);cout<<" = ";nl
	cout<<"Variavel = "<<resultado;nl
	resultado = CalcProteinCresc(&proteina, proteina.posicao_O, proteina.posicao_I);
	cout<<"Depois: ";nl
	cout<<"Expressao: "; ShowProtein(&proteina);cout<<" = ";nl
	cout<<"Resultado = "<<resultado;nl
/*
*/


	return 0;
}

void R_RNA(string m_RNA, protein* prot, int* p){
	double numb=0;
	int expInt=1, expDec=0, fatExpDec=0;

	//Varre toda a espressão mRNA
	for(int j=0; j<50;j++){
		
		if((*p)<m_RNA.length()){ 							//Condição de parada por tamanho
			while(m_RNA[*p] == ' '){						//Retira todos os espaços em branco do M_RNA
				(*p)++;
			}

											//	Verifica e traduz Parenteses	//
			if((m_RNA[*p] == '(') || (m_RNA[*p] == ')')){
				prot->tRNA[j].t = (m_RNA[*p] == '(') ? ABPARENTESE:FEPARENTESE;
				prot->tRNA[j].val.oper = m_RNA[(*p)++];
			}

											//	Verifica e traduz Operadores	//
			else if((m_RNA[*p]=='+')||(m_RNA[*p]=='-')||(m_RNA[*p]=='*')||(m_RNA[*p]=='/')||(m_RNA[*p]=='^')||(m_RNA[*p]=='l')){
				prot->tRNA[j].t = OPERADOR;
				prot->tRNA[j].val.oper = m_RNA[(*p)++];
			}

											//	Verifica e traduz Reais			//
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
			}

											//	Verifica e traduz o sinal '='	//
			else if(m_RNA[*p]== '='){
				prot->fim = j;
				prot->tRNA[j].t = NADA;
				prot->tRNA[j].val.oper = m_RNA[*p];
			} else cout<<"Expressão invalida\n";
		};
		//Para de traduzir a expressao ao encontrar o '='
		if(prot->tRNA[j].val.oper == '=') break;			//Condição de parada por '='
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

void ReducaoProtein(protein* prot, char posit, char negati, int i){
	int pre, pos;
	double operador_1, operador_2;
	if(prot->tRNA[i].t == OPERADOR){
		if((prot->tRNA[i].val.oper == posit)||(prot->tRNA[i].val.oper == negati)){
			pre=i-1;
				do
				{
					if(prot->tRNA[pre].t == OPERANDO){
						operador_1 = prot->tRNA[pre].val.num;
						prot->tRNA[pre].t = NADA;
						break;
					};

					//CORRIGIR - TOMAR COMO REFERENCIA O CRESCENTE
					if(prot->tRNA[pre].t == FEPARENTESE){
						prot->posicao_I = pre;
						int count=0;
						for(int j = (prot->posicao_I-1); j >= 0; j--){
							if(prot->tRNA[j].t == FEPARENTESE) count++;

							if((prot->tRNA[j].t == ABPARENTESE)&&(count != 0)) count--;

							if((prot->tRNA[j].t == ABPARENTESE)&&(count == 0)) {
								prot->posicao_O = j;
								prot->tRNA[j].t = NADA;
								break;
							}
						}
						operador_1 = CalcProteinDecres(prot, prot->posicao_O, prot->posicao_I);
						prot->tRNA[pre].t = NADA;
						break;
					}
				} while (prot->tRNA[pre--].t != OPERANDO);

			pos=i+1;
				do
				{
					if(prot->tRNA[pos].t == OPERANDO){
						operador_2 = prot->tRNA[pos].val.num;
						prot->tRNA[pos].t = NADA;
						break;
					};
					if(prot->tRNA[pos].t == ABPARENTESE){
						prot->posicao_O = pos;
						int count=0;
						for(int j = (prot->posicao_O+1); j < prot->fim; j++){
							if(prot->tRNA[j].t == ABPARENTESE) count++;

							if((prot->tRNA[j].t == FEPARENTESE)&&(count != 0)) count--;

							if((prot->tRNA[j].t == FEPARENTESE)&&(count == 0)) {
								prot->posicao_I = j;
								prot->tRNA[j].t = NADA;
								break;
							}
						}
						operador_2 = CalcProteinCresc(prot, prot->posicao_O, prot->posicao_I);
						prot->tRNA[pos].t = NADA;
						break;
					}					
				} while (prot->tRNA[pos++].t != OPERANDO);

			prot->tRNA[i].t = OPERANDO;
			prot->tRNA[i].val.num = Calc(operador_1,prot->tRNA[i].val.oper,operador_2);
		}
	}

}

void VarreduraCrescente(protein* prot, char positivo, char negativo, int inicio, int final){
	for(int i = (inicio); i<final; i++){
		ReducaoProtein(prot, positivo, negativo, i);
	}
}

void VarreduraDecrescente(protein* prot, char positivo, char negativo, int inicio, int final){
	for(int i = (final -1) ; i>=inicio; i--){
		ReducaoProtein(prot, positivo, negativo, i);
	}
}

double CalcProteinCresc(protein* proteina, int inicio, int final){
	double res;
	VarreduraCrescente(proteina, '^','l', inicio, final);
	VarreduraCrescente(proteina, '*', '/', inicio, final);
	VarreduraCrescente(proteina, '+','-', inicio, final);

	for(int i=inicio; i<final; i++){
		if(proteina->tRNA[i].t == OPERANDO){
			res = proteina->tRNA[i].val.num;
			proteina->tRNA[i].t = NADA;
		}
	}
	return res;
}

double CalcProteinDecres(protein* proteina, int inicio, int final){
	double res;
	VarreduraDecrescente(proteina, '^','l', inicio, final);
	VarreduraDecrescente(proteina, '*', '/', inicio, final);
	VarreduraDecrescente(proteina, '+','-', inicio, final);

	for(int i=inicio; i<final; i++){
		if(proteina->tRNA[i].t == OPERANDO){
			res = proteina->tRNA[i].val.num;
			proteina->tRNA[i].t = NADA;
		}
	}
	return res;
}

void ShowProtein(protein* prot){
	double a;
	char b;
	for(int i=0; i<prot->fim; i++){
		if((prot->tRNA[i].t == OPERADOR)||(prot->tRNA[i].t == ABPARENTESE)||(prot->tRNA[i].t == FEPARENTESE)) {
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