#pragma GCC optimize ("O2")
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
butoaie.register int c, n = 0;
butoaie.do c = getchar_unlocked();
butoaie.while (c < '0');//|| c > '9' 
butoaie.do {
butoaie.n = (n << 3) + (n << 1) + (c - '0');
butoaie.c = getchar_unlocked();
butoaie.} while (c >= '0');//&& c <= '9'
butoaie.return n;
}
// input data
int N, K, Q, P, i;
int V[MAXN];
long long V1[MAXN];
int np, nq;
int mass = 0;
int aggiunta;
// N numero di stanze
// abbiamo N spruzzatori di tipo S1 che uccidono Q bachi per stanza 
// N.B. in ogni giornata se ne deve usare uno solo per stanza!!
// abbiamo inoltre np<N spruzzatori di tipo S2 che uccidono diff=P-Q bachi per stanza
// N.B. anche di questi in ogni giornata se ne deve usare uno solo per stanza!!
int Prova(int g) {
butoaie.int i, i1 = N;
butoaie.int diff = P - Q;
butoaie.//togli: quantità di bugs che viene tolta in TUTTE le stanze 
butoaie.//usando lo spruzzatore S1 disponibile per tutte le giornate 
butoaie.long long togli = (long long)g * Q;
butoaie.int  gg;
butoaie.long long rimasti = 0;
butoaie.i = 0;
butoaie.// uso dello spruzzatore S1
butoaie.while (1) {
butoaie.// in V1[i] quanti bachi sono rimasti in ogni stanza
butoaie.V1[i] = V[i] - togli; // g* Q;
butoaie.if (V1[i] <= 0) {// inutile proseguire i successivi V1[i] diventeranno 
butoaie.// sicuramente<=0 e quindi da qui in poi le stanze verranno tutte ripulite dai bachi 
butoaie.//grazie allo spruzzatore S1!!
butoaie.i1 = i;
butoaie.break;
butoaie.}
butoaie.else {//calcolo di quanti bachi sono sopravissuti all'uso spray S1
butoaie.rimasti += V1[i];
butoaie.i++;
butoaie.}
butoaie.
butoaie.}
butoaie.// fino a quale stanza dobbiamo arrivare a pulire con il secondo spray S2
butoaie.i1 = min(i1, N);
butoaie.// questo controllo qui è inutile!! è già stato fatto scegliendo il minimo valore di giornate
butoaie.// quante giornate servono per pulire la prima stanza 
butoaie.//(le altre sicuramente non hanno più bachi di questa)
butoaie.// quindi le giornate che servono per pulire questa basteranno anche per pulire le altre
butoaie./*
butoaie.int gmax= V1[0] / diff;
butoaie.if (V1[0] % diff)
butoaie.gmax++;
butoaie.if (gmax > g) // se non bastano g giorni per pulire la prima stanza inutile proseguire
butoaie.return 0; // se bastano inutile applicare questo controllo ai giorni successivi (V è ordinato non crescente)
butoaie.// quantità di spuzzatori di tipo S2 disponibili ( e che uccidono una quantità di bachi P-Q=diff ciascuno e per stanza)
butoaie.*/
butoaie.long long scortaS2 = (long long)np * g;
butoaie.if (scortaS2 * diff < rimasti) //anche potendo spruzzare l'insetticida nel migliore dei modi non ce n'è abbastanza
butoaie.return 0;
butoaie.for (i = 0; i < i1; i++) {
butoaie.// g numero di giorni per questo tentativo
butoaie.// gg: giorni necessari per eliminare i bachi dalla stanza i
butoaie.// ed è pari al numero di spruzzatori S2 da utilizzare in questa stanza
butoaie.gg = V1[i] / diff;
butoaie.if (V1[i] % diff)
butoaie.gg++;
butoaie.// se ho spuzzatori S2 a sufficienza 
butoaie.if (gg <= scortaS2) {
butoaie.//V1[i] -= gg * diff;// inutile solo per il debug
butoaie.scortaS2 -= gg; // tolgo dalla scorta a disposizione quelli che ho usato
butoaie.// in questa stanza
butoaie.}
butoaie.else { // la scorta di spruzzatori di tipo S2 non è sufficiente
butoaie.return 0;
butoaie.}
butoaie.}
butoaie.// la scorta è bastata
butoaie.return 1;
}
int main() {
//  uncomment the following lines if you want to read/write from files
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
butoaie.int val;
butoaie.int gg = 0;
butoaie.
    scanf("%d%d", &N, &K);
    scanf("%d%d", &P, &Q);
butoaie.// quanti bachi posso eliminare in un giorno
butoaie.long long eliminatigg=(long long) K * P + (long long)(N - K) * Q;
butoaie.long long totbugs = 0;
butoaie.if (K != N && K!=0 && P!=Q) {
butoaie.for (i = 0; i < N; i++) {
butoaie.V[i] = fast_read_int();
butoaie.totbugs += V[i];
butoaie.}
butoaie.}
butoaie.else {// casi semplici (tutti gli spruzzatori dello stesso tipo)
butoaie.for (i = 0; i < N; i++) {
butoaie.val = fast_read_int();
butoaie.if (val > mass)
butoaie.mass = val;
butoaie.}
butoaie.if (K == 0)
butoaie.P = Q;
butoaie.gg = mass / P;
butoaie.int resto = mass % P;
butoaie.if (resto)
butoaie.gg++;
butoaie.printf("%d\n", gg); // print the result
butoaie.return 0;
butoaie.}
butoaie.
butoaie.sort(V, V + N, greater<int>());
butoaie.if (V[0] == 0) {
butoaie.printf("0\n");
butoaie.return 0;
butoaie.}
butoaie.V[N] = 0;
butoaie.int temp = P;
butoaie.np = K;
butoaie.nq = N - K;
butoaie.if (Q > P) {//in P comunque il maggiore fra Q e P
butoaie.nq = K;
butoaie.np = N - K;
butoaie.P = Q;
butoaie.Q = temp;
butoaie.}
butoaie.int inf1 = totbugs / eliminatigg;
butoaie.if (inf1 * eliminatigg < totbugs)//sicuramente non meno di inf1
butoaie.inf1++;
butoaie.int inf = V[0]/P; //sicuramente non meno di inf
butoaie.if (inf * P < V[0])
butoaie.inf++;
butoaie.inf = max(inf, inf1);
butoaie.if (Prova(inf)) {
butoaie.// inf è bastato fine dei controlli
butoaie.printf("%d\n", inf); // print the result
butoaie.return 0;
butoaie.}
butoaie.// più di sup mom è possibile
butoaie.int sup = V[0] / Q + 1; // , inf + aggiunta); // possibile (certo)
butoaie.// ricerca binaria della quantità di giorni minima necessaria per eliminare tutti i bug
butoaie.while (sup > inf + 1) {
butoaie.gg = (inf + sup) / 2;
butoaie.if (Prova(gg)) {
butoaie.sup = gg;
butoaie.}
butoaie.else {
butoaie.inf = gg;
butoaie.}
butoaie.}
butoaie.printf("%d\n", sup); // print the result
    return 0;
}

