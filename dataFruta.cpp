#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

using namespace std;

class Lista {
	public:
	virtual void entradaDeDados() =0;
	virtual void mostraMediana() =0;
	virtual void mostraMenor() =0;
	virtual void mostraMaior() =0;
	virtual void listarEmOrdem() =0;
	virtual void listarNelementos(int n)=0;
};

class Data {
	public:
	int dia, mes, ano;
	
	/*
	O método abaixo retornará -1 se d1 é anterior a d2
	Retornará 0 se d1 = d2
	Retornará +1 se d1 é posterior a d2
	*/	
	Data (int _dia, int _mes, int _ano) {
		dia = _dia;
		mes = _mes;
		ano = _ano;
	}
	
	static int compara(Data d1, Data d2) { 
        tm data1 = {};
        data1.tm_year = d1.ano - 1900;  
        data1.tm_mon = d1.mes;            
        data1.tm_mday = d1.dia;           
        mktime(&data1);

        tm data2 = {};
        data2.tm_year = d2.ano - 1900;  
        data2.tm_mon = d2.mes;          
        data2.tm_mday = d2.dia;           
        mktime(&data2);

        if (difftime(mktime(&data1), mktime(&data2)) > 0) {
            return +1;
        } else if (difftime(mktime(&data1), mktime(&data2)) < 0) {
            return -1;
        } else {
            return 0;
        }

	}
	
	string toString() {
		string ret = "";
		ret.append(dia < 10 ? "0" + to_string(dia) : to_string(dia));
		ret.append("/");
		ret.append(mes < 10 ? "0" + to_string(mes) : to_string(mes));
		ret.append("/");
		ret.append(to_string(ano));
		return ret;
	}
};

template <typename T>
class Utils {
    public:
	static bool isEmpty(vector<T> *lista){
		size_t size = lista->size();
		if(size == 0){
			return true;
		}
		return false;
	}
    
};

class ListaNomes : public Lista {
	

	vector<string> lista;
	
	public:
	
	/*
		O método abaixo pergunta ao usuários quantos
		elementos vão existir na lista e depois
		solicita a digitação de cada um deles
	*/	

	void entradaDeDados() override {
        int numElementos;
        cout << "Quantos elementos irao existir na lista de nomes? ";
        cin >> numElementos;
        for(int i = 0; i < numElementos; i++){
           string elemento;
           cout << "Digite o " << i + 1 << "ª elemento: ";
           getline(cin >> ws, elemento);
           lista.push_back(elemento);
        }
        cout << "Todos os elementos foram inseridos." << endl;
		listarEmOrdem();
	}

	void listarEmOrdem() override {
		int isEmpty = Utils<string>::isEmpty(&lista);
		bool isSwapped;
		if(!isEmpty){
			do {
				isSwapped = false;
				for(int i = 0; i < lista.size() - 1; i++){
					if(lista[i] > lista[i + 1]){
						string aux;
						aux = lista[i];
						lista[i] = lista[i + 1];
						lista[i + 1] = aux;
						isSwapped = true;
					}
				}
			}while(isSwapped);
			cout << "Elementos ordenados com sucesso!" << endl;	
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}
	
	void mostraMediana() override {
		int isEmpty = Utils<string>::isEmpty(&lista);

		if(!isEmpty) {
			size_t size = lista.size();
			if(size % 2 != 0) {
				string mediana = lista.at(size/2);
				cout << "A mediana da lista de nomes informada: " << mediana << endl;
			} else {
				string mediana = lista.at(size/2 - 1);
				cout << "A mediana da lista de nomes informada: " << mediana << endl;
			}
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}	
	
	void mostraMenor() override {
		int isEmpty = Utils<string>::isEmpty(&lista);
		if(!isEmpty){
			string menor = lista[0];
			for(int i = 0; i < lista.size(); i++){
				if(lista[i] < menor) {
					menor = lista[i];
				}
			}
			cout << "O menor nome da lista: " << menor << endl;
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;

		}
	}

	void mostraMaior() override {
		int isEmpty = Utils<string>::isEmpty(&lista);
		if(!isEmpty){
			string maior = lista[0];
			for(int i = 0; i < lista.size(); i++){
				if(lista[i] > maior) {
					maior = lista[i];
				}
			}
			cout << "O maior nome da lista: " << maior << endl;
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}

	void listarNelementos(int n) override {
		int isEmpty = Utils<string>::isEmpty(&lista);
		if(!isEmpty){
			size_t size = lista.size();
			if(size >= n){
				cout << "Imprimindo lista de nomes: " << endl;
				for(int i = 0; i < n; i++){
					cout << lista[i] << endl;
				} 
			}else {
				cout << "A lista de nomes possui menos do que " << n << " elementos." << endl;
			}
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}
};

class ListaDatas : public Lista  {
	vector<Data> lista;
	
	public:
		
	/*
	O método abaixo pergunta ao usuários quantos
	elementos vão existir na lista e depois
	solicita a digitação de cada um deles
	*/	
	void entradaDeDados() override { 
		int numElementos;
		cout << "Quantos elementos irao existir na lista de datas? ";
		cin >> numElementos;

		for(int i = 0; i < numElementos; i++){
			int dia, mes, ano;
			cout << "Para a " << i + 1 << "º data, digite o dia do ano: " << endl;
			cin >> dia;
			cout << "Para a " << i + 1 << "º data, digite o mes do ano: " << endl;
			cin >> mes;
			cout << "Para a " << i + 1 << "º data, digite o ano: " << endl;
			cin >> ano;
			
			Data novaData(dia, mes, ano);
			lista.push_back(novaData);
		}
		cout << "Todos os elementos foram inseridos." << endl;
		listarEmOrdem();
	}

	void listarEmOrdem() override {
	int isEmpty = Utils<Data>::isEmpty(&lista);
	if(!isEmpty){
		bool isSwapped;
		do {
			isSwapped = false;
			for (int i = 0; i < lista.size() - 1; i++) {
				int compara = Data::compara(lista[i], lista[i + 1]);

				if (compara == 1) {
					Data aux(3, 3 ,3);
					aux = lista[i];
					lista[i] = lista[i + 1];
					lista[i + 1] = aux;
					isSwapped = true;
				}
			}
		} while (isSwapped);
		cout << "Elementos ordenados com sucesso!" << endl;
		} else {
		cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}

	
	void mostraMediana() override {
		int isEmpty = Utils<Data>::isEmpty(&lista);
		if(!isEmpty){
			listarEmOrdem();
			size_t size = lista.size();

			if(size % 2 != 0) {
				Data mediana = lista.at(size/2);
				cout << "A mediana da lista de datas informada: " << mediana.toString() << endl;
			} else {
				Data mediana = lista.at(size/2 - 1);
				cout << "A mediana da lista de datas informada: " << mediana.toString() << endl;
			}
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}

	}
	
	void mostraMenor() override {
		int isEmpty = Utils<Data>::isEmpty(&lista);
		if(!isEmpty){
			cout << "Menor data: " << lista[0].toString() << endl;
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}
	void mostraMaior() override {
		int isEmpty = Utils<Data>::isEmpty(&lista);
		if(!isEmpty){
			cout << "Maior data: " << lista[lista.size() - 1 ].toString() << endl;
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}

	void listarNelementos(int n) override {
		int isEmpty = Utils<Data>::isEmpty(&lista);
		if(!isEmpty){
			size_t size = lista.size();
			if(size >= n){
				cout << "Imprimindo lista de datas: " << endl;
				for(int i = 0; i < n; i++){
					cout << lista[i].toString() << endl;
				}
			} else {
				cout << "A lista de datas possui menos do que " << n << " elementos." << endl;
			}
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}
};

class ListaSalarios : public Lista {
	vector<float> lista;
	
	public:
	
	/*
	O método abaixo pergunta ao usuários quantos
	elementos vão existir na lista e depois
	solicita a digitação de cada um deles
	*/	
	void entradaDeDados() override {
        int numElementos;
        cout << "Quantos elementos irao existir na lista de salarios? ";
        cin >> numElementos;
        for(int i = 0; i < numElementos; i++){
           float elemento;
           cout << "Digite o " << i + 1 << "ª elemento: ";
           cin >> elemento;
           lista.push_back(elemento);
        }
        cout << "Todos os elementos foram inseridos." << endl;
		listarEmOrdem();
	}

	void listarEmOrdem() override {
		int isEmpty = Utils<float>::isEmpty(&lista);
		if(!isEmpty){
			bool isSwapped;
			do {
				isSwapped = false;
				for(int i = 0; i < lista.size() - 1; i++){
					if(lista[i] > lista[i + 1]){
						float aux;
						aux = lista[i];
						lista[i] = lista[i + 1];
						lista[i + 1] = aux;
						isSwapped = true;
					}
				}
			}while(isSwapped);

			cout << "Elemento ordenados com sucesso!" << endl;
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}
			
	void mostraMediana() override {
		int isEmpty = Utils<float>::isEmpty(&lista);
		if(!isEmpty){
			size_t size = lista.size();

			if(size % 2 != 0) {
				float mediana = lista.at(size/2);
				cout << "A mediana da lista de salarios informada: R$ " << fixed << setprecision(2) << mediana << endl;
			} else {
				float mediana = ((lista.at(size/2 - 1) + lista.at(size/2)) / 2.0);
				cout << "A mediana da lista de salarios informada: R$ " << fixed << setprecision(2) <<  mediana << endl;
			}
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}
	
	void mostraMenor() override {
		int isEmpty = Utils<float>::isEmpty(&lista);
		if(!isEmpty){
			float menor = lista[0];
			for(int i = 0; i < lista.size(); i++){
				if(lista[i] < menor) {
					menor = lista[i];
				}
			}
			cout << "O menor salario da lista: R$ " << fixed << setprecision(2) << menor << endl;
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}
	void mostraMaior() override {
		int isEmpty = Utils<float>::isEmpty(&lista);
		if(!isEmpty){
			float maior = lista[0];
			for(int i = 0; i < lista.size(); i++){
				if(lista[i] > maior) {
					maior = lista[i];
				}
			}
			cout << "O maior salario da lista: R$ " << fixed << setprecision(2) << maior << endl;
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}

	void listarNelementos(int n) override {
		int isEmpty = Utils<float>::isEmpty(&lista);
		if(!isEmpty){
			size_t size = lista.size();
			if(size >= n){
				cout << "Imprimindo lista de salarios: " << endl;
				for(int i = 0; i < n; i++){
					cout << "R$ " << fixed << setprecision(2) << lista[i] << endl;
				}
			} else {
				cout << "A lista de salarios possui menos do que " << n << " elementos."<< endl;
			}
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}
};

class ListaIdades : public Lista  {
	vector<int> lista;
	
	public:
		
		/*
	O método abaixo pergunta ao usuários quantos
	elementos vão existir na lista e depois
	solicita a digitação de cada um deles
	*/	
	void entradaDeDados() override {
        int numElementos;
        cout << "Quantos elementos irao existir na lista de idades? ";
        cin >> numElementos;
        for(int i = 0; i < numElementos; i++){
           int elemento;
           cout << "Digite o " << i + 1 << "ª elemento: ";
           cin >> elemento;
           lista.push_back(elemento);
        }
        cout << "Todos os elementos foram inseridos." << endl;
		listarEmOrdem();
	}

	void listarEmOrdem() override {
		int isEmpty = Utils<int>::isEmpty(&lista);
		if(!isEmpty){
			bool isSwapped;
			do {
				isSwapped = false;
				for(int i = 0; i < lista.size() - 1; i++){
					if(lista[i] > lista[i + 1]){
						int aux;
						aux = lista[i];
						lista[i] = lista[i + 1];
						lista[i + 1] = aux;
						isSwapped = true;
					}
				}
			}while(isSwapped);
			cout << "Elementos ordenados com sucesso!" << endl;
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}
	
	void mostraMediana() override {
		int isEmpty = Utils<int>::isEmpty(&lista);
		if(!isEmpty){
			size_t size = lista.size();

			if(size % 2 != 0) {
				int mediana = lista.at(size/2);
				cout << "A mediana da lista de idades informada: " << mediana << endl;
			} else {
				int mediana = ((lista.at(size/2 - 1) + lista.at(size/2)) / 2);
				cout << "A mediana da lista de idades informada: " << mediana << endl;
			}
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}
	
	void mostraMenor() override {
		int isEmpty = Utils<int>::isEmpty(&lista);
		if(!isEmpty){
			int menor = lista[0];
			for(int i = 0; i < lista.size(); i++){
				if(lista[i] < menor) {
					menor = lista[i];
				}
			}
			cout << "A menor idade da lista: " << menor << endl;
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}
	void mostraMaior() override {
		int isEmpty = Utils<int>::isEmpty(&lista);
		if(!isEmpty){
			int maior = lista[0];
			for(int i = 0; i < lista.size(); i++){
				if(lista[i] > maior) {
					maior = lista[i];
				}
			}
			cout << "A maior idade da lista: " << maior << endl;
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}

	void listarNelementos(int n) override {
		int isEmpty = Utils<int>::isEmpty(&lista);
		if(!isEmpty){
			size_t size = lista.size();
			if(size >= n){
				cout << "Imprimindo lista de idades: " << endl;
				for(int i = 0; i < n; i++){
					cout << lista[i] << endl;
				}
			} else {
				cout << "A lista de idades possui menos do que " << n << " elementos." << endl;
			}
		} else {
			cout << "A lista esta vazia. Adicione pelo menos um elemento." << endl;
		}
	}
};

int main () {
	vector<Lista*> listaDeListas;
	
	ListaNomes listaNomes;
	listaNomes.entradaDeDados();
	listaDeListas.push_back(&listaNomes);
	
	ListaDatas listaDatas;
	listaDatas.entradaDeDados();
	listaDeListas.push_back(&listaDatas);

 	ListaSalarios listaSalarios;
	listaSalarios.entradaDeDados();
	listaDeListas.push_back(&listaSalarios);

	ListaIdades listaIdades;
	listaIdades.entradaDeDados();
	listaDeListas.push_back(&listaIdades);
	cout << endl;

	for (Lista* l : listaDeListas) {
		l->mostraMediana();
		l->mostraMenor();
		l->mostraMaior();
	}
}
    
