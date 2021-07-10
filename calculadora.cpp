#include "./CLASSES/classeCalculadora.h"

int main(){
	string mRNA;
	cout<<"Entre com a expressão:";nl
	nl
	cin>>mRNA;
	Protein proteina(mRNA);
	cout<<proteina.get_Resultado();nl
	nl	
	return 0;
}