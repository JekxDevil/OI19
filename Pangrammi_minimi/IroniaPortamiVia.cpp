#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int conta(int N, int K, vector<int>& V) {
    int somma=0;
    for(int i = K; i<N ; i++){
        for (int j = 0; j+i <= N; ++j) {
            int *nums = new int[K];
            for(int l = 0; l<K; l++)
            	nums[l]=0;

            for (int y = j; y < j+i; ++y) {
                nums[V[y]]=nums[V[y]]+1;
            }

            int s=0;
            int res=1;
            for (int y = 0; y < K; ++y) {
                if (nums[y]==0){
                    s++;
                }
                if (s==0){
                    res*=nums[y];
                }
            }
            if (s!=0){
                j+=s-1;
            } else {
                somma+=res;
            }
        }
        if (somma!=0){
            break;
        }
    }
    return somma;
}

int main() {
    // Input da file:
    // freopen("input.txt", "r", stdin);

    // Output su file:
    // freopen("output.txt", "w", stdout);

    size_t n, k;
    cin >> n >> k;
    vector<int> v(n);
    for(size_t i = 0; i < n; i++) {
        cin >> v[i];
    }
    cout << conta(n, k, v) << endl;
    return EXIT_SUCCESS;
}
