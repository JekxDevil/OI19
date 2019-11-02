#include <iostream>

using namespace std;

int conta(int N, int K, int* V);

//2,0,1,1,2,0
//0,1,1,2,1,1,0

//RICERCA NUMERO DI RAPPRESENTAZIONI MINIME
int main(int argc, char** argv) {
	
	int V[] = {2,0,1,1,2,0};
	cout << conta(6, 3, V) << endl;
	return 0;
}

//N => lunghezza array, K => lunghezza alfabeto, V[] => array
int conta(int N, int K, int* V){
	
	//const
	const int MODULO = 46337;
	
	//dati
	int arrayNumTrov[K];		//array statico tenente numero occorrenza caratteri
	int _iSwitchIndice;		//variabile indicante switch iniziale arrayAn
	int _iRappresentazioniTotali = 0, _iRisultato;		//variabili per il risultato finale
	bool _bTrovato = false;
	
	//se array non vuoto
	if(N > 0) {
		
		//ciclo incrementa lunghezza del subarray da analizzare
		for(int _iLunAn=K; _iLunAn < N && _iRappresentazioniTotali <= 0;_iLunAn++){
			
			/*	il numero di iterazioni di un subarray all'interno dell'array
			e' dato dall'incremento tra la lunghezza dell'array sottratta
			alla lunghezza dell'subarray => (N-Lsub)+1	*/
			int _iTotaleIteraSub = (N-_iLunAn)+1;
			_iSwitchIndice = 0;
			
			for(int _iNumIterazione=0; _iNumIterazione<_iTotaleIteraSub; _iNumIterazione++){
				
				//inizializzazione sub-array da analizzare e booleano risultato
				int arrayAn[_iLunAn], _iRappresentazioniLocali = 1;
				_bTrovato = true;
				
				//inizializzazione array tieni traccia dei caratteri della substring
				for (int i=0; i<K; i++)
					arrayNumTrov[i] = 0;
				
				//riempimento subarray da analizzare
				for (int i=_iSwitchIndice, j=0; j<_iLunAn; i++, j++)
					arrayAn[j] = V[i];
				
				//registrazione occorrenze dei simboli
				for(int i=0; i<_iLunAn; i++)
					arrayNumTrov[arrayAn[i]]++;
				
				//conteggio occorrenze (null=0, etero=1, pangrMin>1) CONTROLLO
				for(int i=0; i<K; i++)
				
					if(arrayNumTrov[i] == 0){
						_bTrovato = false;
						_iRappresentazioniLocali = 0;
					}
					else if(arrayNumTrov[i] > 1 && _bTrovato)
						_iRappresentazioniLocali *= arrayNumTrov[i];
					
				//somma rappresentazioni trovate
				_iRappresentazioniTotali += _iRappresentazioniLocali;
					
				//terminata analisi subarray, aumento spaziamento indice
				_iSwitchIndice++;
			}
		}
	}
	
	_iRisultato = _iRappresentazioniTotali % MODULO;
	return _iRisultato;
}