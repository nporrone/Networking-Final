//
// Created by Nicholas Porrone on 2018-04-06.(250918147)
//

// Please use c90 standard

#ifndef UNTITLED_CIPHERS_H
#define UNTITLED_CIPHERS_H

char * caesar_encrypt(char *plaintext, int key);

char * caesar_decrypt(char *ciphertext, int key);

char * vigen_encrypt(char *plaintext, char *key);

char * vigen_decrypt(char *ciphertext, char *key);

void freq_analysis(char *ciphertext, double letters[26]);

#endif //UNTITLED_CIPHERS_H
