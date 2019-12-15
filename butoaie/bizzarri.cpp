// sottopos N 472782 85 mx
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include <functional>
#include <algorithm>
 // constraints
#define MAXN 200001
using namespace std;
//   /*
#define _WINDOWS
#ifdef _WINDOWS
// no getchar_unlocked on Windows so just call getchar
inline int getchar_unlocked() { return getchar(); }
#endif
//   */
inline int fast_read_int() {
	register int c, n = 0;
	do c = getchar_unlocked();
	while (c < '0');//|| c > '9' 
	do {
		n = (n << 3) + (n << 1) + (c - '0');
		c = getchar_unlocked();
	} while (c >= '0');//&& c <= '9'
	return n;
}

// input data
int N, K, Q, P, i;
int V[MAXN];
long long working_array[MAXN];
int number_insect_killing_p, number_insect_killing_q;
int room_max_bugs = 0;

// N numero di stanze
// abbiamo N spruzzatori di tipo S1 che uccidono Q bachi per stanza 
// N.B. in ogni giornata se ne deve usare uno solo per stanza!!
// abbiamo inoltre number_insect_killing_p<N spruzzatori di tipo S2 che uccidono diff=P-Q bachi per stanza
// N.B. anche di questi in ogni giornata se ne deve usare uno solo per stanza!!

int Prova(int _days) {
	int i,  index_power_insecticide = N;
	int diff = P - Q;
	//remove_lower_insecticide: quantità di bugs che viene tolta in TUTTE le stanze
	//usando lo spruzzatore S1 disponibile per tutte le giornate
	long long remove_lower_insecticide = (long long)_days * Q;
	int days;
	long long left = 0;
	i = 0;
	
    // uso dello spruzzatore S1
	while (1) {
		// in working_array[i] quanti bachi sono left in ogni stanza
		working_array[i] = V[i] - remove_lower_insecticide; // _days* Q;
		
        // inutile proseguire i successivi working_array[i] diventeranno 
		// sicuramente<=0 e quindi da qui in poi le stanze verranno tutte ripulite dai bachi 
		// grazie allo spruzzatore S1!!
        if (working_array[i] <= 0) {
		    index_power_insecticide = i;
			break;
		} else {    //calcolo di quanti bachi sono sopravissuti all'uso spray S1
			left += working_array[i];
			i++;
		}
	}

	// fino a quale stanza dobbiamo arrivare a pulire con il secondo spray S2
    index_power_insecticide = min(index_power_insecticide, N);
	// questo controllo qui è inutile!! è già stato fatto scegliendo il minimo valore di giornate
	// quante giornate servono per pulire la prima stanza 
	//(le altre sicuramente non hanno più bachi di questa)
	// quindi le giornate che servono per pulire questa basteranno anche per pulire le altre
	long long scortaS2 = (long long)number_insect_killing_p * _days;
    
	if (scortaS2 * diff < left) //anche potendo spruzzare l'insetticida nel migliore dei modi non ce n'è abbastanza
		return 0;

	for (i = 0; i < index_power_insecticide; i++) {
		// _days numero di giorni per questo tentativo
		// days: giorni necessari per eliminare i bachi dalla stanza i
		// ed è pari al numero di spruzzatori S2 da utilizzare in questa stanza
		days = working_array[i] / diff;
		if (working_array[i] % diff) 
            days++;

		// se ho spuzzatori S2 a sufficienza 
		if (days <= scortaS2) {
			//working_array[i] -= days * diff;// inutile solo per il debug
			scortaS2 -= days; // tolgo dalla scorta a disposizione quelli che ho usato in questa stanza
		} else { // la scorta di spruzzatori di tipo S2 non è sufficiente
			return 0;
		}
	}

	// la scorta è bastata
	return 1;
}

int main() {
    //  uncomment the following lines if you want to read/write from files
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
	int val;
	int days = 0;
	
    scanf("%d%d", &N, &K);
    scanf("%d%d", &P, &Q);
	
    // quanti bachi posso eliminare in un giorno
	long long max_deleted_per_day = (long long) K * P + (long long)(N - K) * Q;
	long long total_insects = 0;
	
    /*
    Se non ci sono insetticidi tutti dello stesso tipo e
    se gli insetticidi non ammazzano quantita' uguali di insetti per giorno (equivalenti).
    Riempo array con insetti in stanze e variabile con numero totali insetti
    */
    if (K != N && K!=0 && P!=Q) {
		
        for (i = 0; i < N; i++) {
			V[i] = fast_read_int();
			total_insects += V[i];
		}
	} else {    // casi semplici (tutti gli spruzzatori dello stesso tipo)
        
        //cerco il massimo
        for (i = 0; i < N; i++) {
			val = fast_read_int();
            
			if (val > room_max_bugs)
				room_max_bugs = val;
		}

		if (K == 0) 
            P = Q;
		
        days = room_max_bugs / P;
		int resto = room_max_bugs % P;
		
        if (resto) 
            days++;

		printf("%d\n", days); // print the result
		return 0;
	}
	
    //ordino array in modo decrescente (v[0] stanza con > insetti)
	sort(V, V + N, greater<int>());

    //se tutte le stanze sono vuote programma termina con risultato 0
	if (V[0] == 0) {
		printf("0\n");
		return 0;
	}
	
    V[N] = 0;   //ultimo indice fuori limite = 0
	int temp = P;
	number_insect_killing_p = K;
	number_insect_killing_q = N - K;
	
    //se Q maggiore, switch valori per avere P sempre maggiore
    if (Q > P) {
		number_insect_killing_q = K;
		number_insect_killing_p = N - K;
		P = Q;
		Q = temp;
	}
	
    //limite minimo di giorni relativo
    int relative_min_limit = total_insects / max_deleted_per_day;

    //se presente resto, manca un giorno al conteggio del limite minimo
	if (relative_min_limit * max_deleted_per_day < total_insects) 
        relative_min_limit++;
	
    //limite minimo di giorni con insetticida potente
    int min_days = V[0] / P;
    
    //se presente resto, manca un giorno al conteggio del limite minimo
	if (min_days * P < V[0]) 
        min_days++;
	
    min_days = max(min_days, relative_min_limit);
	
    // min_days è bastato fine del programma
    if (Prova(min_days)) {
		printf("%d\n", min_days); // print the result
		return 0;
	}

	// limite massimo numero giorni diviso insetticida debole, incrementato per gestire resto
	int max_days = V[0] / Q + 1; // possibile (certo)

	/*
    ricerca binaria della quantità di giorni minima necessaria per eliminare tutti i bug
	quando min e max_days coincidono, numero giorni trovato
    */
    while (max_days > min_days + 1) {
		days = (min_days + max_days) / 2;

		if (Prova(days)) {
			max_days = days;
		} else {
			min_days = days;
		}
	}

	printf("%d\n", max_days); // print the result
    return 0;
}