#include <bits/stdc++.h>
using namespace std;

// Function to compute One's Complement
string getOnesComplement(string data) {
    for (char &bit : data) {
        bit = (bit == '0') ? '1' : '0';
    }
    return data;
}

// Function to perform binary addition of two blocks
string addBinary(string a, string b) {
    int n = a.size();
    string result = "";
    int carry = 0;

    for (int i = n - 1; i >= 0; i--) {
        int sum = (a[i] - '0') + (b[i] - '0') + carry;
        result = char((sum % 2) + '0') + result;
        carry = sum / 2;
    }

    // Handle end-around carry
    if (carry) {
        for (int i = n - 1; i >= 0; i--) {
            int sum = (result[i] - '0') + carry;
            result[i] = char((sum % 2) + '0');
            carry = sum / 2;
        }
    }

    return result;
}

// Function to calculate checksum
string computeChecksum(string data, int blockSize) {
    int n = data.length();

    // Padding with leading zeros if needed
    if (n % blockSize != 0) {
        int padSize = blockSize - (n % blockSize);
        data = string(padSize, '0') + data;
    }

    // Initial block
    string result = data.substr(0, blockSize);

    // Process remaining blocks
    for (int i = blockSize; i < data.size(); i += blockSize) {
        string block = data.substr(i, blockSize);
        result = addBinary(result, block);
    }

    // Return one's complement of result
    return getOnesComplement(result);
}

// Function to verify message integrity
bool isValidMessage(string sent, string received, int blockSize) {
    string senderChecksum = computeChecksum(sent, blockSize);
    string receiverChecksum = computeChecksum(received + senderChecksum, blockSize);

    // Check if all bits are zero
    return count(receiverChecksum.begin(), receiverChecksum.end(), '0') == blockSize;
}

int main() {
    string sentMessage, receivedMessage;
    int blockSize;

    cout << "Enter sender message (binary): ";
    cin >> sentMessage;

    cout << "Enter received message (binary): ";
    cin >> receivedMessage;

    cout << "Enter block size: ";
    cin >> blockSize;

    if (isValidMessage(sentMessage, receivedMessage, blockSize)) {
        cout << "No Error\n";
    } else {
        cout << "Error\n";
    }

    return 0;
}