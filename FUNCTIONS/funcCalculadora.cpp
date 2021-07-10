#include "../CLASSES/classeCalculadora.h"

			/*					SUB-ROTINAS						*/

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

			/*													*/
			/*					SUB-ROTINAS						*/
			/*					DE CLASSE						*/
			/*													*/

void Protein::ReducaoProtein(char posit, char negati, int i){
	int pre, pos;
	double operador_1, operador_2;
	if(this->get_Type(i) == OPERADOR){
		if((this->get_Oper(i) == posit)||(this->get_Oper(i) == negati)){
			pre=i-1;
				do
				{
					if(this->get_Type(pre) == OPERANDO){
						operador_1 = this->get_Num(pre);
						this->set_Type(NADA, pre);
						break;
					};
					if(this->get_Type(pre) == FEPARENTESE){
						this->set_posicao_I(pre);
						this->set_Type(NADA, pre);
						int count=0;
						for(int j = (this->get_posicao_I()-1); j >= 0; j--){
							if(this->get_Type(j) == FEPARENTESE) count++;

							else if((this->get_Type(j) == ABPARENTESE)){
								if(count != 0){
									count--;
								}
								else if(count == 0){
									this->set_posicao_O(j);
									this->set_Type(NADA, j);
									break;
								}
							} 
						}
						this->setCresc(false);
						operador_1 = CalcProtein(this->get_posicao_O(), this->get_posicao_I());
						break;
					}
				} while (this->get_Type(pre--) != OPERANDO);

			pos=i+1;
				do
				{
					if(this->get_Type(pos) == OPERANDO){
						operador_2 = this->get_Num(pos);
						this->set_Type(NADA, pos);
						break;
					};
					if(this->get_Type(pos) == ABPARENTESE){
						this->set_posicao_O(pos);
						this->set_Type(NADA, pos);
						int count=0;
						for(int j = (this->get_posicao_O()+1); j < this->getFim(); j++){
							if(this->get_Type(j) == ABPARENTESE) count++;

							else if((this->get_Type(j) == FEPARENTESE)){
								if(count != 0){
									count--;									
								}
								else if(count == 0){
									this->set_posicao_I(j);
									this->set_Type(NADA, j);
									break;
								}
							} 
						}
						this->setCresc(true);
						operador_2 = CalcProtein(this->get_posicao_O(), this->get_posicao_I());
						break;
					}					
				} while (this->get_Type(pos++) != OPERANDO);

			this->set_Type(OPERANDO, i);
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
			cout<<"POSIÇÂO:"<<i<<"\nOperadores procurados: \""<<posit<<"\" \""<<negati<<"\"\nOperando 1 = "<< operador_1 <<"\nOperando_2 = "<<operador_2<<"\n\tOPERADOR: \""<<this->get_Oper(i)<<"\" "<<"\n\tValor numerico: "<<this->get_Num(i);nl
			this->ShowTab();nl
*/

			this->set_Num(Calc(operador_1,this->get_Oper(i),operador_2), i);

/*
			cout<<"POSIÇÂO:"<<i<<"\nOperando 1 = "<< operador_1 <<"\nOperando_2 = "<<operador_2<<"\n\tOPERADOR: \""<<this->get_Oper(i)<<"\" "<<"\n\tValor numerico: "<<this->get_Num(i);nl
			this->ShowTab();nl
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

void Protein::Varredura(int inicio, int final){
	char oper[3][2] = {{'^','l'},{'*','/'},{'+','-'}};

	if(this->getCresc() == true){
		for(int loop = 0; loop < 3; loop++){
			for(int i = (inicio); i<final; i++){
				ReducaoProtein(oper[loop][0], oper[loop][1], i);
			}
		}
	}else if(this->getCresc() == false){
		for(int loop = 0 ; loop<3; loop++){
			for(int i = (final -1); i>=inicio; i--){
				ReducaoProtein(oper[loop][0], oper[loop][1], i);
			}
		}
	}
}

double Protein::CalcProtein(int inicio, int final){
	double res;
	Varredura(inicio, final);

	for(int i=inicio; i<final; i++){
		if(this->get_Type(i) == OPERANDO){
			res = this->get_Num(i);
			this->set_Type(NADA, i);
		}
	}
	return res;
}

void Protein::R_RNA(string m_RNA){
	double numb=0;
	int expInt=1, expDec=0, fatExpDec=0, posi = this->get_posicao();

	//Varre toda a espressão mRNA
	for(int j=0; j<50;j++){
		if((posi)<m_RNA.length()){ 							//Condição de parada por tamanho
			while(m_RNA[posi] == ' '){						//Retira todos os espaços em branco do M_RNA
				posi++;
			}
											// Verifica e traduz Menos Unario	//
			if(m_RNA[posi] == '~'){
				this->set_Type(MENOS_UNARIO, j);
				this->set_Oper(m_RNA[posi++], j);
			}
											//	Verifica e traduz Parenteses	//
			else if((m_RNA[posi] == '(') || (m_RNA[posi] == ')')){
				this->set_Type(((m_RNA[posi] == '(') ? ABPARENTESE:FEPARENTESE), j);
				this->set_Oper(m_RNA[posi++], j);
			}

											//	Verifica e traduz Operadores	//
			else if((m_RNA[posi]=='+')||(m_RNA[posi]=='-')||(m_RNA[posi]=='*')||(m_RNA[posi]=='/')||(m_RNA[posi]=='^')||(m_RNA[posi]=='l')){
				this->set_Type(OPERADOR, j);
				this->set_Oper(m_RNA[posi++],j);
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
					this->set_Type(OPERANDO, j);
					this->set_Num(numb, j);
				};
			}
											//	Verifica e traduz o sinal '='	//
			else if(m_RNA[posi]== '='){
				this->setFim(j);
				this->set_Type(NADA, j);
				this->set_Oper(m_RNA[posi],j);
			} else cout<<"Expressão invalida\n";
		};
		//Para de traduzir a expressao ao encontrar o '='
		if(this->get_Oper(j) == '=') break;			//Condição de parada por '='
	};
	this->set_posicao(posi);
}

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

void Protein::set_Type(tipo classificacao, int posicao){
	this->tRNA[posicao].classificacao = classificacao;
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
/*
	nl
	cout<<"________________________________________________________";nl
	cout<<"----#-----#-----#-----#-----#-----#-----#-----#-----#---";nl
	cout<<"________________________________________________________";nl
	nl
*/
	cout<<"\t|Numero\t\t|OPERADOR\t|Tipo";nl
	for(int i = 0; i<= this->getFim(); i++){
		float alguma_coisa;
		
		cout<<"________________________________________________________";nl
		cout<<i<<"\t|"<<(((this->get_Num(i)<0.001)&&(this->get_Num(i)>(-0.001)))? 0.00000 : this->get_Num(i))<<"\t\t|"<<this->get_Oper(i)<<"\t\t|";switch (this->get_Type(i))
		{
		case MENOS_UNARIO:
			cout<<"MENOS UNARIO";nl
			break;
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
	nl
	cout<<"________________________________________________________";nl
	cout<<"----#-----#-----#-----#-----#-----#-----#-----#-----#---";nl
	cout<<"________________________________________________________";nl
	nl
	nl
}

void Protein::ShowProtein(){
	double a;
	char b;
	for(int i=0; i<this->fim; i++){
		if((this->get_Type(i) == OPERADOR)||(this->get_Type(i) == ABPARENTESE)||(this->get_Type(i) == FEPARENTESE)) {
			b = this->tRNA[i].val.oper;
			cout<<b;
		}
		else if(this->get_Type(i) == OPERANDO) {
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
	this->resultado = CalcProtein(this->get_posicao_O(), this->get_posicao_I());
}

Protein::Protein(string mRNA){
	set_M_RNA(mRNA);
	set_DIM(this->get_M_RNA().length());
	set_posicao(0);

	R_RNA(this->get_M_RNA());
	
	set_posicao_O(0);
	set_posicao_I(getFim());
	setCresc(true);

	ShowTab();

	set_Resultado();
}