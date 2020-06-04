#include <iostream>
#include <string>
#define SIZE 4		//cambio in base a dimensione del cruciverba (salve spegni :D)
using namespace std;

//funzione bool - input matrice immutabile di input e stringa da cercare
bool is_orizontal(const char (&_matrix)[SIZE][SIZE], const string _find_me){
	string analyzing;
	int index;
	
	for(int i = 0; i < SIZE; i++){
		index = 0;
		analyzing = "";
		
		for(int j = 0; j < SIZE; j++) {			
			//se coincide la prima lettera
			if(_matrix[i][j] == _find_me[index]){
				analyzing += _find_me[index++];
				
				if(analyzing == _find_me)
					return true;	
			}else{
				index = 0;
				analyzing = "";
				
				//e' importante ricordarsi di riverificare coincidenza
				if(_matrix[i][j] == _find_me[index]){
					analyzing += _find_me[index++];
				
					if(analyzing == _find_me)
						return true;
				}
			}
		}
	}
	
	return false;
}

//funzione bool - input matrice immutabile di input e stringa da cercare
bool is_vertical(const char (&_matrix)[SIZE][SIZE], const string _find_me){
	string analyzing;
	int index;
	
	for(int i = 0; i < SIZE; i++){
		index = 0;
		analyzing = "";
		
		for(int j = 0; j < SIZE; j++) {
			//se coincide la prima lettera
			if(_matrix[j][i] == _find_me[index]){
				analyzing += _find_me[index++];
				
				if(analyzing == _find_me)
					return true;	
			} else{
				index = 0;
				analyzing = "";
				
				//e' importante ricordarsi di riverificare coincidenza
				if(_matrix[j][i] == _find_me[index]){
					analyzing += _find_me[index++];
				
					if(analyzing == _find_me)
						return true;
				}
			}
		}
	}
	
	return false;
}

//funzione bool - input matrice immutabile di input e stringa da cercare
bool is_diagonal(const char (&_matrix)[SIZE][SIZE], const string _find_me){
	int limit = SIZE * SIZE;	//ciclo di giri pari al quadrato della dimensione della matrice
	string analyzing = "";
	int index;
	
	int i, row, column, j;
	
	//diagonale da sx a dx
	i = row = SIZE - 1;		//occhio all'overflow della matriceeeee (.)(.)
	j = column = 0;			//										 \__/
	for(int cycles = 0; cycles < limit; cycles++){
		//se coincide la prima lettera
		if(_matrix[i][j] == _find_me[index]){
			analyzing += _find_me[index++];
			
			if(analyzing == _find_me)
				return true;
		}else{
			index = 0;
			analyzing = "";
			
			//e' importante ricordarsi di riverificare coincidenza
			if(_matrix[i][j] == _find_me[index]){
				analyzing += _find_me[index++];
			
				if(analyzing == _find_me)
					return true;
			}
		}
		
		//spostamento casella obiettivo
		j++;
		i++;
		if(i >= SIZE || j >= SIZE){
			index = 0;
			analyzing = "";
			
			if(row == 0){
				j = ++column;
				i = row;
			}
			else{
				i = --row;
				j = column;
			}
		}	
	}
	
	//RIPRISTINARE VALORI PER EVITARE CONTAMINAZIONE RISULTATI
	//diagonale da dx a sx
	i = row = SIZE - 1;
	j = column = SIZE - 1;
	analyzing = "";
	for(int cycles = 0; cycles < limit; cycles++){
		//se coincide la prima lettera
		if(_matrix[i][j] == _find_me[index]){
			analyzing += _find_me[index++];
			
			if(analyzing == _find_me)
				return true;
		}else{
			index = 0;
			analyzing = "";
			
			//e' importante ricordarsi di riverificare coincidenza
			if(_matrix[i][j] == _find_me[index]){
				analyzing += _find_me[index++];
			
				if(analyzing == _find_me)
					return true;
			}
		}
		
		//spostamento casella obiettivo
		j--;
		i++;
		if(i >= SIZE || j < 0){
			index = 0;
			analyzing = "";
		
			if(row == 0){
				j = --column;
				i = row;
			}
			else{
				i = --row;
				j = column;
			}
		}	
	}
	
	return false;
}

int main(){
	//programma provato con cruciverba "aabbccddeeffgghh" (scrivere disponendolo in matrice 4x4)
	char matrix[SIZE][SIZE];
	string find_me;
	
	//input matrice
	cout << "Digita cruciverba" << endl;
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			cin >> matrix[i][j];
			
	//input parola da cercare
	cout << "Digita parola da cercare" << endl;
	cin >> find_me;
	
	//stampo matrice per debug
	for(int i = 0; i < SIZE; i++){
		cout << endl;
		for(int j = 0; j < SIZE; j++){
			cout << matrix[i][j] << " ";
		}
	}
	cout << endl;
	
	//algoritmi di ricerca sul cruciverba scritti da me :D
	if(is_orizontal(matrix, find_me) || is_vertical(matrix, find_me) || is_diagonal(matrix, find_me))
		cout << "Parola trovata!";
	else
		cout << "Parola assente.";
	
	return 0;
}
