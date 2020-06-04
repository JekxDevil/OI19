int quadri(int N, long long M, int V[]){
    long long sum = 0;
    long long range = 0;

    for (range = 0; range < N; range++) {
        sum += V[range];
        if (sum > M) {
            range--;
            break;
        }
    }

    if (range == N) {
        return range;
    }

    long long s = 0;    //somma totale del range massimo
    for (long long j = 0; j < range+1; j++) {
        s += V[j];
    }

    //z da fine j in poi. Parte array esclusa for precedente
    for (long long z = range+1; z < N; z++) {
        s = s - V[z-(range+1)] + V[z];

        while (s > M && range >= 0) {       //fintanto che la somma e' maggiore di massimale e range positivo
            s -= V[z-range];
            range -= 1;
        }

        if (range == 0) break;  //qualore range raggiunge 0, ritornalo
    }

    return range+1;
}
