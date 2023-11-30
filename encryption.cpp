// encryption.cpp
#include "encryption.h"

// Encryption logic
void encrypt(QString &str) {
    for (int i = 0; i < str.length(); ++i) {
        // Shift each character by 2, then multiply its Unicode value by 3
        str[i] = QChar((str[i].unicode() + 2) * 3);
    }
}

// Decryption logic
void decrypt(QString &str) {
    for (int i = 0; i < str.length(); ++i) {
        // Reverse the operations performed in encryption
        str[i] = QChar(str[i].unicode() / 3 - 2);
    }
}
