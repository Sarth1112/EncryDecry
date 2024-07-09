#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

const int ALPHABET_SIZE = 26;

// Function to encrypt a single character
char encryptChar(char ch, int shift) {
    if (!std::isalpha(ch)) return ch;
    
    char base = std::isupper(ch) ? 'A' : 'a';
    return (ch - base + shift + ALPHABET_SIZE) % ALPHABET_SIZE + base;
}

// Function to decrypt a single character
char decryptChar(char ch, int shift) {
    return encryptChar(ch, -shift);
}

// Function to encrypt or decrypt a file
void processFile(const std::string& inputFile, const std::string& outputFile, int shift, bool encrypt) {
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);
    
    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }
    
    char ch;
    while (inFile.get(ch)) {
        char processedChar = encrypt ? encryptChar(ch, shift) : decryptChar(ch, shift);
        outFile.put(processedChar);
    }
    
    inFile.close();
    outFile.close();
    
    std::cout << (encrypt ? "Encryption" : "Decryption") << " completed." << std::endl;
}

int main() {
    std::string inputFile, outputFile;
    int shift;
    char choice;
    
    std::cout << "Enter input file name: ";
    std::cin >> inputFile;
    
    std::cout << "Enter output file name: ";
    std::cin >> outputFile;
    
    std::cout << "Enter shift value (1-25): ";
    std::cin >> shift;
    shift = std::abs(shift) % ALPHABET_SIZE;  // Ensure shift is in valid range
    
    std::cout << "Encrypt (e) or Decrypt (d)? ";
    std::cin >> choice;
    
    if (choice == 'e' || choice == 'E') {
        processFile(inputFile, outputFile, shift, true);
    } else if (choice == 'd' || choice == 'D') {
        processFile(inputFile, outputFile, shift, false);
    } else {
        std::cout << "Invalid choice. Please enter 'e' for encrypt or 'd' for decrypt." << std::endl;
    }
    
    return 0;
}