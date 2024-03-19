#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int A[4], B[4];
	long long result = 0;

	scanf("%d.%d.%d.%d", &A[0], &A[1], &A[2], &A[3]);
	scanf("%d.%d.%d.%d", &B[0], &B[1], &B[2], &B[3]);

	result = B[3] - A[3];
	result += (B[2] << 8) - (A[2] << 8);
	result += (B[1] << 16) - (A[1] << 16);
	result += ((long long)B[0] << 24) - ((long long)A[0] << 24);
	result++;

	printf("%lld", (long long)result);
	return 0;
}