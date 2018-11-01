#include <bits/stdc++.h>
#ifdef _WIN32
#	include <windows.h>
#	define slp(x) Sleep(x)
#elif __linux__
#	include <unistd.h> 
# 	define slp(x) usleep((x) * 1000.0)
#endif
using namespace std;

const int maxn = 600;

ofstream fout("extract.in");

char A[maxn];
int f[maxn][maxn], g[maxn][maxn][maxn], c[maxn][maxn][maxn], lcp[maxn][maxn];

void print(int x, int y) {
	for (int m = x; m < y; m++)
		if (f[x][y] == f[x][m] + f[m + 1][y]) {
			print(x, m), print(m + 1, y);
			return;
		}
	for (int l = 1; l * 2 <= y - x + 1; l++) 
		if (f[x][y] == f[x][x + l - 1] + 3 + g[x][y][l]) {
			cout << '[';
			fout << '[';
			print(x, x + l - 1);
			cout << ']';
			fout << ']';
			cout << c[x][y][l];
			fout << c[x][y][l];
			for (int i = x + l, j = x + l; i + l - 1 <= y; i++) {
				if (i > j) {
					if (g[j - l][y][l] == g[i][y][l] + f[j][i - 1] + 3) {
						cout << '{';
						fout << '{';
						print(j, i - 1);
						cout << '}';
						fout << '}';
						cout << c[x][y][l] - c[i][y][l];
						fout << c[x][y][l] - c[i][y][l];
						j = i + l;
						i = j - 1;
					}	
				} else {
					if (g[j - l][y][l] == g[i][y][l]) {
						j = i + l;
						i = j - 1;	
					}
				}
			}
			return;
		}
	for (int i = x; i <= y; i++) { cout << A[i]; fout << A[i]; fflush(stdout); slp(10); }
}

string B;

int main() {
	ifstream fin;
	fin.open("extract.ans");
	if (!fin) { 
		cerr << "compress: cannot access 'extract.ans': No such file or directory" << endl; return -1; 
	} 
	
	fin >> B;
	if (fin.fail() || B.length() > 600) {
		cerr << "the length of string should be between 1 to 600, \nplease check the file and try again later" << endl; return -1;
	}
	
	for (int i = 0; i < B.length(); i++) {
		A[i] = B[i];
		if (A[i] == '[' || A[i] == '{' || A[i] == '}' || A[i] == ']' || 
			isdigit(A[i]) || !isgraph(A[i])) { 
			cerr << "format error, the string should not have contained invisible characters, digits and brackets" << endl;
			return -1;
		}
	}
	
	cout << "Before:" << endl;
	
	slp(100);
	
	cout << endl;
	for (int i = 0; A[i]; i++) {
		cout << A[i];
		fflush(stdout);
		slp(10);
	}
	cout << endl << endl;
	
	slp(100);
	
	printf("Magic:\n\n"); int now = 0;
	
	int n = strlen(A);
	memset(f, 0x3f, sizeof f);
	memset(g, 0x3f, sizeof g);
	
	for (int x = 0; x < n; x++) 
		for (int y = x + 1; y < n; y++) 
			while (A[x + lcp[x][y]] == A[y + lcp[x][y]]) lcp[x][y]++;
	
	for (int x = 0; x < n; x++) f[x][x] = 1;
	for (int x = 0; x < n; x++) for (int y = x; y < n; y++) g[x][y][y - x + 1] = 0, c[x][y][y - x + 1] = 1;
	
	for (int s = 2; s <= n; s++) {
		
		int k = (s - 1) * 100 / (n - 1);
		slp(20);
		
		for (int i = 0; i < 50 + 2 + 5 + 2; i++) printf("\b");
		
		switch (now) {
			case 0 : cout << '-'; break;
			case 1 : cout << '/'; break;
			case 2 : cout << '|'; break;
			case 3 : cout << '\\'; break;
		}
		if (s % 4 == 0) now = (now + 1) % 4;
		cout << ' ';
		
		cout << '[';
		
		for (int i = 0; i < 50; i++) {
			if (i * 2 < k) cout << '#';
			else cout << ' ';
		}
		
		cout << ']';
		
		printf(" %3d%%", k);
		
		fflush(stdout);
		
		for (int x = 0, y = x + s - 1; y < n; x++, y++) {
			for (int m = x; m < y; m++) 
				f[x][y] = min(f[x][y], f[x][m] + f[m + 1][y]);
			for (int l = 1; l * 2 <= s; l++) {
				if (lcp[x][y - l + 1] < l) continue;
				g[x][y][l] = f[x + l][y - l] + 3;
				c[x][y][l] = 2;
				for (int i = x + l; i + l - 1 <= y; i++) {
					if (lcp[x][i] < l) continue;
					if (i > x + l) {
						if (g[x][y][l] > g[i][y][l] + f[x + l][i - 1] + 3) {
							g[x][y][l] = g[i][y][l] + f[x + l][i - 1] + 3;
							c[x][y][l] = c[i][y][l] + 1;
						}
					}
					
					else {
						if (g[x][y][l] > g[i][y][l]) {
							g[x][y][l] = g[i][y][l];		
							c[x][y][l] = c[i][y][l] + 1;
						}
					}
					
				}
			}			
			for (int l = 1; l * 2 <= s; l++) {
				if (lcp[x][y - l + 1] < l) continue;				
				f[x][y] = min(f[x][y], f[x][x + l - 1] + 3 + g[x][y][l]);
			}
		}
	}
	//cout << f[0][n - 1] << endl;
	slp(100);
	
	cout << endl << endl << "After:" << endl << endl;
	
	slp(100);
	print(0, n - 1);
	cout << endl;
	//cout << endl << "press any key to continue...";
	fflush(stdout);
	fout.close();
	getchar();
	return 0;
}


/*
aaaabaaaaaaaabaaaaaaaabaaaa
*/
