#include <bits/stdc++.h>
using namespace std;
int main() {
	freopen("hack.in", "r", stdin);
	freopen("hack.out", "w", stdout);
	int TestID; cin >> TestID;
	switch (TestID) {
		case 0 : cout << "NOIP RP ++" << endl; break;
		case 1 : cout << "Are you going to Scarborough Fair?" << endl; break; 
		case 2 : cout << "Parsley, sage, rosemary, and thyme." << endl; break; 
		case 3 : cout << "Remember me to one who lives there," << endl; break; 
		case 4 : cout << "" << endl; break; 
		case 5 : cout << "Tell her to make me a cambric shirt." << endl; break; 
		case 6 : cout << "" << endl; break; 
		case 7 : cout << "" << endl; break; 
		case 8 : cout << "Then she'll be a true love of mine." << endl; break; 
		default : cout  << "What do you do at" << endl
				<< "the end of the world?" << endl
				<< "Are you busy?" << endl
				<< "Will you save us?" << endl;
	}
}
