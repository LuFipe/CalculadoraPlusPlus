#include "./CLASSES/classeCalculadora.h"

int main(){
	string mRNA;
	cout<<"Entre com a expressão";nl
	cin>>mRNA;
	Protein proteina(mRNA);

	int a;
	char b;
	
	cout<<"Tamanho da proteina = "<<proteina.get_DIM();nl
	proteina.ShowTab();

	proteina.ShowProtein();
	proteina.set_Resultado();
	cout<<" = "<<proteina.get_Resultado();nl
	nl
	
	proteina.ShowTab();
/*

	cout<<"Antes: ";nl
	cout<<"Expressao: ";nl
	cout<<"Tamanho da proteina: "<<proteina.get_M_RNA().length();nl
	nl
*/	
	return 0;
}