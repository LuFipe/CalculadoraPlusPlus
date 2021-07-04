#include <iostream>
#include <cmath>

#define nl cout<<endl;

using namespace std;

double ConvCord(string, int*);
char ConvOper(string, int*);
double Calc(double, char, double);

int main(){
	string expres, test;
	double num_1, num_2, res;
	char operando;
	int pos=0;

	cout<<"Entre com a expressão";nl
	cin>>expres;

	num_1 = ConvCord(expres, &pos);
	operando = ConvOper(expres, &pos);
	num_2 = ConvCord(expres, &pos);

	res = Calc(num_1, operando, num_2);

	cout<<"Operação: "<<num_1<<operando<<num_2<<" = "<<res;nl

	return 0;
}

double ConvCord(string expres, int* p){
	double numb=0;
	int virg, i;
	int a=1, b=0, c=0;

	for( i=(*p); i<expres.length();i++){
		if(( '9' >= expres[i]) && (expres[i] >= '0')){
		numb = numb*pow(10,a) + (expres[i]-48)*pow(10,b*c);
		b--;
		} else if ((expres[i] == ',') || (expres[i] == '.')){
			a=0;
			c=1;
			b=-1;
		} else if(expres[i] == ' '){
			*p = i;
			++(*p);
			return numb;
		}else{
			cout<<"String invalida";nl
			*p = i;
			cout<<"Posição :"<<*p;nl
			return numb;
		};
	};
	*p = i;
	return numb;
}

char ConvOper(string expres, int* p){
	return expres[(*p)++];
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