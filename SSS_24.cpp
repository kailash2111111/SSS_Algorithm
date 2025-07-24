#include<iostream>
#include <vector>
#include <random>

using namespace std;

int threadshold;
int split;
vector<pair<int, int>> shares; /// stored the all shares 

vector<pair<int, int>> selectedShares; //selected share



bool containsX(const vector<pair<int, int>>& shares, int idx) {
	for (const auto& share : shares) {
		if (share.first == idx) {
			return true;
		}
	}
	return false;
}


int reconstructSecret(vector < pair<int, int>>& shares) {
	int secret = 0;
	int n = shares.size();

	
	
	for (int i = 0; i < n; ++i) {
		int xi = shares[i].first;
		int yi = shares[i].second;

		double numerator = 1.0;
		double denominator = 1.0;

		for (int j = 0; j < n; ++j) {
			if (i != j) {
				int xj = shares[j].first;
				numerator *= (0.0 - xj);
				denominator *= (xi - xj);
			}
		}

		secret += yi * (numerator / denominator);
	}

	return secret;

	

}

int evalPolynomial(vector<int>& coeffs, int x) {

	int result = coeffs[0] + (coeffs[1] * x )+ (coeffs[2] * (x * x));
	return result;
}

void generateMode(int secret, int split) {

	vector<int> coff(threadshold);
	coff[0] = secret;

	for (int i = 1; i < threadshold; i++) {
		coff[i] = rand()%256;
	}
	

	for (int i = 1; i <= split; i++) {
		int y = evalPolynomial(coff, i);
		shares.emplace_back(i, y);
	}
	for (auto& n : shares) {
		cout << n.first << " : " << n.second << endl;
	}

	
	

	
}

int main() {

	srand(time(0));

	while (true) {
		cout << "\n==== Shamir's Secret Sharing ====\n";
		cout << "1. Generate Shares\n";
		cout << "2. Reconstruct Secret\n";
		cout << "3. Exit\n";
		cout << "Enter your choice: ";

		int choice;
		cin >> choice;

		if (choice == 1) {

			int secret;
			cout << "Enter the Secret number \n";
			cin >> secret;

			cout << "Enter the count of owner : \n";
			cin >> split;

			threadshold = split / 2;



			generateMode(secret, split);
		}
		else if (choice == 2) {

			int cnt;
			cout << "\nEnter number of shares to reconstruct the secret: ";
			cin >> cnt;

			if ((threadshold < cnt) && (cnt <= split)) {


				cout << "Enter the x values (e.g. 1 2 3): ";
				for (int i = 0; i < cnt; i++) {
					int xval;
					cin >> xval;

					// Check if this x exists in shares
					bool found = false;
					for (int j = 0; j < shares.size(); j++) {
						if (shares[j].first == xval) {
							selectedShares.push_back(shares[j]);
							found = true;
							break;
						}
					}
					if (!found) {
						cout << "x = " << xval << " not found in shares.\n";
					}
				}
				int n2 = reconstructSecret(selectedShares);

				cout << "secret number is : " << n2 << endl;
			}
			else {
				cout << "threadshold count is min  " << threadshold << "  less than " << split << endl;;

			}
			reconstructSecret(selectedShares);
		}
		else if (choice == 3) {
			cout << "Exiting program. Goodbye!\n";
			break;
		}
		else {
			cout << "Invalid choice. Please try again.\n";
		}
	}

	return 0;
}