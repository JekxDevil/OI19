#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#define UNIT 60
#define DAY 24

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	//sleep and awake
	int Sh, Sm, Ah, Am, Rh = 0, Rm = 0;
	scanf("%d %d", &Sh, &Sm);
	scanf("%d %d", &Ah, &Am);

	if (Am - Sm < 0) {
          Am += UNIT;
          Ah--;
	}

    	if (Sh > Ah) {
           int tmp = DAY - Sh;
           Sh = 0;
           Ah += tmp;
    	} 

	Rm = Am - Sm;
	Rh = Ah - Sh;
    
	printf("%d %d", Rh, Rm);
	return 0;
}