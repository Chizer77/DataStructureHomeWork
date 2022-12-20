// Copyright (c) 2022.
// Editor By Chizer

//汉诺塔

#include<iostream>
using namespace std;

int count = 0;
void move(int n, char x, char z) {
    cout << ++count << ". Move disk " << n << " from " << x << " to " << z << '\n';
}

void hanoi(int n, char x, char y, char z) {
    if(n == 1) move(1, x ,z);
    else {
        hanoi(n - 1, x,z,y);
        move(n, x ,z);
        hanoi(n - 1, y, x, z);
    }
}

int main() {
    int n;
    char x, y, z;
    cin >> n >> x >> y >> z;
    hanoi(n, x, y, z);
}