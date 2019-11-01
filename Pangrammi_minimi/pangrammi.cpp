#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	
	return 0;
}

//N => lunghezza array, K => lunghezza alfabeto, V[] => array
int conta(int N, int K, int* V){
	
	//const
	const int MODULO = 46337;
	
	//dati
	int arrayNumTrov[K];		//array statico tenente numero occorrenza caratteri
	int _iSwitchIndex = 0;		//variabile indicante switch iniziale arrayAn
	int _iOut = 0, _iRisultato;		//variabili per il risultato finale
	
	//se array non vuoto
	if(N > 0) {
		
		//ciclo incrementa lunghezza del subarray da analizzare
		for(int _iLunAn=K; _iLunAn<N && _iOut<=0; _iLunAn++){
			
			/*	il numero di iterazioni di un subarray all'interno dell'array
			e' dato dall'incremento tra la lunghezza dell'array sottratta
			alla lunghezza dell'subarray => (N-Lsub)+1	*/
			int _iTotaleIteraSub = (N-_iLunAn)+1;
			
			for(int _iNumIterazione=0; _iNumIterazione<_iTotaleIteraSub; _iNumIterazione++){
				
				//inizializzazione sub-array da analizzare
				int arrayAn[_iLunAn];
				
				//riempimento subarray da analizzare
				for (int i=_iSwitchIndex, j=0; j<_iLunAn; i++, j++)
					arrayAn[j] = V[i];
					
				//analisi subarray
				for (int i=0; i<_iLunAn; i++){
					
					//se eterolettare, senno' pangramma minimo
					if(_iLunAn == K){
						
					} else {
						
					}
					
					//pulizia vettore tieni traccia dei caratteri della substring
					for (int i=0; i<K; i++)
						arrayNumTrov[i] = 0;
						
					//terminata analisi subarray, aumento spaziamento indice
					_iSwitchIndex++;	
				}
			}
		}
	}
	
	_iRisultato = _iOut % MODULO;
	return _iRisultato;
}