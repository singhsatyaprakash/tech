//write a program for hamming code generation for error detection and correction.
#include <bits/stdc++.h>
using namespace std;

// Function to check if number is power of 2
bool isPowerOfTwo(int x) {
    return (x & (x - 1)) == 0;
}

// Generate Hamming Code
string generateHamming(string data) {
    int m = data.size();
    
    // Calculate number of parity bits
    int r = 0;
    while (pow(2, r) < (m + r + 1)) {
        r++;
    }

    int n = m + r;
    vector<int> hamming(n + 1);

    // Fill data and parity positions
    int j = 0;
    for (int i = 1; i <= n; i++) {
        if (isPowerOfTwo(i)) {
            hamming[i] = 0; // parity placeholder
        } else {
            hamming[i] = data[j++] - '0';
        }
    }

    // Calculate parity bits
    for (int i = 0; i < r; i++) {
        int pos = pow(2, i);    // filling all parity position
        int parity = 0; //count 1 bit...

        for (int j = 1; j <= n; j++) {
            if (j & pos) {
                parity ^= hamming[j];
            }
        }
        hamming[pos] = parity;
    }

    // Convert to string
    string result = "";
    for (int i = 1; i <= n; i++) {
        result += to_string(hamming[i]);
    }

    return result;
}

// Detect and Correct Error
void detectError(string received) {
    int n = received.size();
    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i++) {
        arr[i] = received[i - 1] - '0';
    }

    int errorPos = 0;

    // Check parity bits
    for (int i = 0; pow(2, i) <= n; i++) {
        int pos = pow(2, i);
        int parity = 0;

        for (int j = 1; j <= n; j++) {
            if (j & pos) {
                parity ^= arr[j];
            }
        }

        if (parity != 0) {
            errorPos += pos;
        }
    }

    if (errorPos == 0) {
        cout << "No error detected\n";
    } else {
        cout << "Error at position: " << errorPos << endl;

        // Correct error
        arr[errorPos] ^= 1;

        cout << "Corrected code: ";
        for (int i = 1; i <= n; i++) {
            cout << arr[i];
        }
        cout << endl;
    }
}

int main() {
    string data;
    cout << "Enter binary data: ";
    cin >> data;

    string hamming = generateHamming(data);
    cout << "Hamming Code: " << hamming << endl;

    cout << "\nEnter received code: ";
    string received;
    cin >> received;

    detectError(received);

    return 0;
}