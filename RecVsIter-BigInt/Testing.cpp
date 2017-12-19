#include <iostream>
#include <string>

using namespace std;

long fiboRecurs(int);
int fiboIter(int);

int main() {
	cout << fiboRecurs(7) << endl;
	cout << fiboIter(7);
	return 0;
}

long fiboRecurs(int n) {
	return (n < 2) ? n : (fiboRecurs(n - 1) + fiboRecurs(n - 2));
}

int fiboIter(int n) {
	int num[3] = { 0, 1, 0 };
	if (n == 0) {
		return 0;
	}
	else if (n == 1) {
		return 1;
	}
	else {
		for (int i = 1; i < n ; i++) {
			num[2] = num[1];
			num[1] = num[0] + num[1];
			if (i < n) {
				num[0] = num[2];
			}
		}
	}
	return num[1];
}
