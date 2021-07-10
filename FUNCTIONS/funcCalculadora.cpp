#include "../CLASSES/classeCalculadora.h"

			/*					PPROTOTIPO DAS					*/
			/*					SUB-ROTINAS						*/
			/*													*/
double Calc(double, char, double);
void ReducaoProtein(Protein*, char, char, int );
void Varredura(Protein*, int, int);
double CalcProtein(Protein*, int, int);
void R_RNA(string, Protein*);

			/*													*/
			/*					SUB-ROTINAS						*/
			/*													*/

//Opera com 2 numeros
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

//Reduz a proteina calculando os caracteres adicionados
void ReducaoProtein(Protein* prot, char posit, char negati, int i){
	int pre, pos;
	double operador_1, operador_2;
	if(prot->get_Type(i) == OPERADOR){
		if((prot->get_Oper(i) == posit)||(prot->get_Oper(i) == negati)){
			pre=i-1;
				do
				{
					if(prot->get_Type(pre) == OPERANDO){
						operador_1 = prot->get_Num(pre);
						prot->set_Type(NADA, pre);
						break;
					};
					if(prot->get_Type(pre) == FEPARENTESE){
						prot->set_posicao_I(pre);
						int count=0;
						for(int j = (prot->get_posicao_I()-1); j >= 0; j--){
							if(prot->get_Type(j) == FEPARENTESE) count++;

							if((prot->get_Type(j) == ABPARENTESE)&&(count != 0)) count--;

							if((prot->get_Type(j) == ABPARENTESE)&&(count == 0)) {
								prot->set_posicao_O(j);
								prot->set_Type(NADA, j);
								break;
							}
						}
						prot->setCresc(false);
						operador_1 = CalcProtein(prot, prot->get_posicao_O(), prot->get_posicao_I());
						prot->set_Type(NADA, pre);
						break;
					}
				} while (prot->get_Type(pre--) != OPERANDO);

			pos=i+1;
				do
				{
					if(prot->get_Type(pos) == OPERANDO){
						operador_2 = prot->get_Num(pos);
						prot->set_Type(NADA, pos);
						break;
					};
					if(prot->get_Type(pos) == ABPARENTESE){
						prot->set_posicao_O(pos);
						int count=0;
						for(int j = (prot->get_posicao_O()+1); j < prot->getFim(); j++){
							if(prot->get_Type(j) == ABPARENTESE) count++;

							if((prot->get_Type(j) == FEPARENTESE)&&(count != 0)) count--;

							if((prot->get_Type(j) == FEPARENTESE)&&(count == 0)) {
								prot->set_posicao_I(j);
								prot->set_Type(NADA, j);
								break;
							}
						}
						prot->setCresc(true);
						operador_2 = CalcProtein(prot, prot->get_posicao_O(), prot->get_posicao_I());
						prot->set_Type(NADA, pos);
						break;
					}					
				} while (prot->get_Type(pos++) != OPERANDO);

			prot->set_Type(OPERANDO, i);
/*
			//											//
			//											//
			//				DEBUG NA RAÇA				//
			//		descomente para fazer o debug		//
			//											//
			nl
			cout<<"________________________________________________________";nl
			cout<<"----#-----#-----#-----#-----#-----#-----#-----#-----#---";nl
			cout<<"________________________________________________________";nl
			nl
			nl
			cout<<"POSIÇÂO:"<<i<<"\nOperadores procurados: \""<<posit<<"\" \""<<negati<<"\"\nOperando 1 = "<< operador_1 <<"\nOperando_2 = "<<operador_2<<"\n\tOPERADOR: \""<<prot->get_Oper(i)<<"\" "<<"\n\tValor numerico: "<<prot->get_Num(i);nl
			prot->ShowTab();nl
*/
			prot->set_Num(Calc(operador_1,prot->get_Oper(i),operador_2), i);
/*
			cout<<"POSIÇÂO:"<<i<<"\nOperando 1 = "<< operador_1 <<"\nOperando_2 = "<<operador_2<<"\n\tOPERADOR: \""<<prot->get_Oper(i)<<"\" "<<"\n\tValor numerico: "<<prot->get_Num(i);nl
			prot->ShowTab();nl
			nl
			cout<<"________________________________________________________";nl
			cout<<"----#-----#-----#-----#-----#-----#-----#-----#-----#---";nl
			cout<<"________________________________________________________";nl
			nl
			nl
*/
		}
	}

}

//Varre toda a proteina de forma crescente e decrescente
void Varredura(Protein* prot, int inicio, int final){
	char oper[3][2] = {{'^','l'},{'*','/'},{'+','-'}};

	if(prot->getCresc() == true){
		for(int loop = 0; loop < 3; loop++){
			for(int i = (inicio); i<final; i++){
				ReducaoProtein(prot, oper[loop][0], oper[loop][1], i);
			}
		}
	}else if(prot->getCresc() == false){
		for(int loop = 0 ; loop<3; loop++){
			for(int i = (final -1); i>=inicio; i--){
				ReducaoProtein(prot, oper[loop][0], oper[loop][1], i);
			}
		}
	}
}

//Calcula toda a Proteina de modo Crescente
double CalcProtein(Protein* proteina, int inicio, int final){
	double res;
	Varredura(proteina, inicio, final);

	for(int i=inicio; i<final; i++){
		if(proteina->get_Type(i) == OPERANDO){
			res = proteina->get_Num(i);
			proteina->set_Type(NADA, i);
		}
	}
	return res;
}

//Traduz a Expressão (M_RNA - string) para 'Proteinas' (-atomos)
void R_RNA(string m_RNA, Protein* prot){
	double numb=0;
	int expInt=1, expDec=0, fatExpDec=0, posi = prot->get_posicao();

	//Varre toda a espressão mRNA
	for(int j=0; j<50;j++){
		if((posi)<m_RNA.length()){ 							//Condição de parada por tamanho
			while(m_RNA[posi] == ' '){						//Retira todos os espaços em branco do M_RNA
				posi++;
			}

											//	Verifica e traduz Parenteses	//
			if((m_RNA[posi] == '(') || (m_RNA[posi] == ')')){
				prot->set_Type(((m_RNA[posi] == '(') ? ABPARENTESE:FEPARENTESE), j);
				prot->set_Oper(m_RNA[posi++], j);
			}

											//	Verifica e traduz Operadores	//
			else if((m_RNA[posi]=='+')||(m_RNA[posi]=='-')||(m_RNA[posi]=='*')||(m_RNA[posi]=='/')||(m_RNA[posi]=='^')||(m_RNA[posi]=='l')){
				prot->set_Type(OPERADOR, j);
				prot->set_Oper(m_RNA[posi++],j);
			}

											//	Verifica e traduz Reais			//
			else if( (('9'>=m_RNA[posi]) && (m_RNA[posi]>='0')) || (m_RNA[posi] == ',') || (m_RNA[posi] == '.')){
				expInt=1, expDec=0, fatExpDec=0;

				for(int k=(posi);k<m_RNA.length(); k++){
					if(( '9' >= m_RNA[k]) && (m_RNA[k] >= '0')){
						numb = numb*pow(10,expInt) + (m_RNA[k]-48)*pow(10,expDec*fatExpDec);
						expDec--;
					}
					else if ((m_RNA[k] == ',') || (m_RNA[k] == '.')){
						expInt=0;
						fatExpDec=1;
						expDec=-1;
					} else {
						posi = k;
						numb = 0;
						break;
					};
					prot->set_Type(OPERANDO, j);
					prot->set_Num(numb, j);
				};
			}
											//	Verifica e traduz o sinal '='	//
			else if(m_RNA[posi]== '='){
				prot->setFim(j);
				prot->set_Type(NADA, j);
				prot->set_Oper(m_RNA[posi],j);
			} else cout<<"Expressão invalida\n";
		};
		//Para de traduzir a expressao ao encontrar o '='
		if(prot->get_Oper(j) == '=') break;			//Condição de parada por '='
	};
	prot->set_posicao(posi);
}


			/*													*/
			/*					SUB-ROTINAS						*/
			/*					DE CLASSE						*/
			/*													*/

void Protein::set_M_RNA(string mRNA){
	this->mRNA = mRNA;
}

void Protein::set_DIM(int n){
	this->dim = n;
	this->tRNA = new mol[n];
}

void Protein::set_Oper(char oper, int posicao){
	this->tRNA[posicao].val.oper = oper;
};

void Protein::set_Num(double num, int posicao){
	this->tRNA[posicao].val.num = num;
};

void Protein::set_Type(tipo t, int posicao){
	this->tRNA[posicao].t = t;
};

void Protein::set_posicao_O(int posicao_O){
	this->posicao_O = posicao_O;
}

void Protein::set_posicao_I(int posicao_I){
	this->posicao_I = posicao_I;
}

void Protein::set_posicao(int posicao){
	this->posicao = posicao;
}

void Protein::setFim(int fim){
	this->fim = fim;
}

void Protein::ShowTab(){
	cout<<"\t|Numero\t\t|OPERADOR\t|Tipo";nl
	for(int i = 0; i<= this->getFim(); i++){
		cout<<"________________________________________________________";nl
		cout<<i<<"\t|"<<(this->get_Num(i)>0.001?this->get_Num(i) : 0.00000)<<"\t\t|"<<this->get_Oper(i)<<"\t\t|";switch (this->get_Type(i))
		{
		case OPERADOR:
			cout<<"OPERADOR";nl
			break;
		case OPERANDO:
			cout<<"OPERANDO";nl
			break;
		case ABPARENTESE:
			cout<<"ABPARENTESE";nl
			break;
		case FEPARENTESE:
			cout<<"FEPARENTESE";nl
			break;
		case TRIGONOMETRICO:
			cout<<"TRIGONOMETRICO";nl
			break;
		case NADA:
			cout<<"NADA";nl
			break;
		default:
			cout<<"Não ha tipo reconhecido";nl
			break;
		}
	}
}

void Protein::ShowProtein(){
	double a;
	char b;
	for(int i=0; i<this->fim; i++){
		if((this->tRNA[i].t == OPERADOR)||(this->tRNA[i].t == ABPARENTESE)||(this->tRNA[i].t == FEPARENTESE)) {
			b = this->tRNA[i].val.oper;
			cout<<b;
		}
		else if(this->tRNA[i].t == OPERANDO) {
			a = this->tRNA[i].val.num;
			cout<<a;
		}
		else continue;
	}
}

void Protein::setCresc(bool crescente){
	this->crescente = crescente;
};

void Protein::set_Resultado(){
	this->resultado = CalcProtein(this, this->get_posicao_O(), this->get_posicao_I());
}

Protein::Protein(string mRNA){
	set_M_RNA(mRNA);
	set_DIM(this->get_M_RNA().length());
	set_posicao(0);

	R_RNA(this->get_M_RNA(), this);
	
	set_posicao_O(0);
	set_posicao_I(getFim());
	setCresc(true);

	set_Resultado();
}