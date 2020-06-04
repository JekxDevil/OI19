/*
 * This template is valid both in C and in C++,
 * so you can expand it with code from both languages.
 * NOTE: it is recommended to use this even if you don't
 * understand the following code.
 * 
 * (1,1) (3,2) = sqrt(|1-2| * ~ + |1-3| * ~) = sqrt(1*1 + 2*2) = sqrt(5)
 */

#include <stdio.h>
#include <assert.h>
#include <math.h>

// input data
int T, i;
int Xa, Ya, Xb, Yb, Xc, Yc, R;

struct Point
{
    int x;
    int y;
};

int GetCartesianDistance(int a, int b)
{
    return abs(a - b);
}

double GetPythagoreanDistance(Point A, Point B)
{
    return sqrt(pow(GetCartesianDistance(A.x, B.x), 2) + pow(GetCartesianDistance(A.y, B.y), 2));
}

int main() 
{
    assert(1 == scanf("%d", &T));

    for(i=0; i<T; i++) {
        assert(7 == scanf("%d %d %d %d %d %d %d",
                    &Xa, &Ya, &Xb, &Yb, &Xc, &Yc, &R));

        // insert your code here
        Point A {Xa, Ya}, B {Xb, Yb}, C {Xc, Yc};
        double AB, AC, BC, through_circle, result;

        //perhaps speed up
        if(A.x == B.x){
            AB = GetCartesianDistance(A.y, B.y);
        } else if(A.y == B.y) {
            AB = GetCartesianDistance(A.x, B.x);
        } else {
            AB = GetPythagoreanDistance(A, B);
        }

        //circle stuff
        AC = GetPythagoreanDistance(A, C);
        BC = GetPythagoreanDistance(B, C);

        AC = AC > R ? AC - R : 0;
        BC = BC > R ? BC - R : 0;
        through_circle = AC + BC;       //effective noise through circle path

        result = through_circle < AB ? through_circle : AB;

        // print result (round down and print six decimals)
        // DO NOT EDIT!
        result = floor(result * 1000000) / 1000000;
        printf("%.6f\n", result);
    }
    return 0;
}
