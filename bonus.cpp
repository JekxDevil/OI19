#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>

#define MAXN 100000

long long N;
long long S[MAXN], P[MAXN];
long long result;
long double max_score;
long double max_point;

//"A" maggiore uguale -> A · D >= C · B
//concentrarsi su media

bool NeedChange(long long& a, long long& b,long long& c,long long& d) {
	return ((max_score - a) * (max_point - d) < (max_score - c) * (max_point - b)) ? true : false;
}

long long GetExercise() {
	int bad_index = 0;

	//other cases
	for (int i = 1; i < N; i++) {
		if (NeedChange(S[bad_index], P[bad_index], S[i], P[i]))
			bad_index = i;
	}

	return bad_index;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

    assert(1 == scanf("%lld", &N));

    for(int i=0; i<N; i++) {
        assert(1 == scanf("%lld", &S[i]));
        assert(1 == scanf("%lld", &P[i]));
    }

	for (int i = 0; i < N; i++) {
		max_score += S[i];
		max_point += P[i];
	}

	result = GetExercise();

    printf("%lld\n", result);
    return 0;
}
