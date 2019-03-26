#include "ciphers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

// Nicholas Porrone (250918147)

// This program requires you to compile it with c90 standard on our course server

int main() {

    double array[26]; // used for frequency analysis
    char input[100];
    int cipher; // used for frequency analysis
    char *returns; // the return value

    printf("Input plaintext: ");
    fgets(input,100,stdin);

    printf("Available Ciphers: \n1) Caesar\n2) Vigenere\n\nSelect Cipher: ");
    scanf("%d",&cipher);

    while(getchar() != '\n');

    // make sure selection is correct
    if(cipher > 2 || cipher < 0) {
        printf("Error , incorrect selection.\n");
        return EXIT_FAILURE;
    }

    if(cipher == 1) {

        int key;

        printf("Input key as number: ");
        scanf("%d",&key);

        printf("\nPlaintext: \n%s\n",input);

        returns = caesar_encrypt(input,key);
        printf("Ciphertext: \n%s\n", returns);

        returns = caesar_decrypt(returns,key);
        printf("Decrypted plaintext \n%s\n",returns);

        printf("\nFrequency analysis:\n");
        freq_analysis(returns,array);

        for( int n = 0; n <26 ; n++) {
            printf("%c:" , (char)(n + 65));
            printf("%1.1f\n",*(array +n));
        }

    } else if(cipher == 2) {

        char key[100];

        printf("Input key as string: ");
        fgets(key,100,stdin);

        char *lineFind;
        if((lineFind = strchr(key, '\n')) != NULL) {
            *lineFind = '\0';
        }

        printf("\nPlaintext: \n%s\n",input);

        returns = vigen_encrypt(input,key);
        printf("Ciphertext: \n%s\n", returns);

        returns = vigen_decrypt(returns,key);
        printf("Decrypted plaintext \n%s\n",returns);

        printf("\nFrequency analysis:\n");
        freq_analysis(returns,array);

        for( int n = 0; n <26 ; n++) {
            printf("%c:" , (char)(n + 65));
            printf("%1.1f\n",*(array + n));
        }

    }
    return 0;
}

