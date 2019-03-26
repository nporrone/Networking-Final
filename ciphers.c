//
// Created by Nicholas Porrone on 2018-04-06.(250918147)
//

// please use c90 standard

#include "ciphers.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <memory.h>

// This function takes a null terminated string, plaintext, and integer key as arguments. The result
//is a new dynamically allocated null terminated string containing the ciphertext

char * caesar_encrypt(char *plaintext, int key) {

    char *encrypt = (char *) malloc((strlen(plaintext) +1) * sizeof(char)); // encrpyted message

    char *p , *q ;

    char alph[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};  // alphabet string

    int result; // needed for negative keys

    if (encrypt == NULL) {
        printf("Error locating memory");
        exit(EXIT_FAILURE);
    }

    // iterate through the given string and alphabet

    for(p = plaintext , q = encrypt; *p != '\0'; p++ , q++) {

        // if it is punctuation just skip over it

        if(!isalpha(*p)){

            *q = *p;

        } else {

            *p = toupper((unsigned char) *p);

            for(int i = 0; alph[i] != 0; i++) {

                if (*p == alph[i]) {

                    result = (i + key) % 26;
                    if (result < 0) {

                        result = 26 + result;
                        *q = alph[result];

                    }
                    *q = alph [(i + key) % 26];
                }

            }

        }

    }

    *(encrypt + strlen(plaintext)) = '\0';
    return encrypt;

}

// This function takes a null terminated string, ciphertext, and integer key as arguments. The
//result is a new dynamically allocated null terminated string containing the plaintext

char * caesar_decrypt(char *ciphertext, int key){

    char *decrypt = (char *) malloc((strlen(ciphertext) +1) * sizeof(char)); // encrpyted message

    char *p , *q ;

    char alph[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};  // alphabet string

    int result; // used for negative keys

    if (decrypt == NULL) {
        printf("Error locating memory");
        exit(EXIT_FAILURE);
    }

    // iterate through the given string and alphabet

    for(p = ciphertext , q = decrypt; *p != '\0'; p++ , q++) {

        // if it is punctuation just skip over it

        if(!isalpha(*p)){

            *q = *p;

        } else {

            *p = toupper((unsigned char) *p);

            for(int i = 0; alph[i] != 0; i++) {

                if (*p == alph[i]) {

                    result = (i - key) % 26;
                    if (result < 0) {

                        result = 26 + result;
                        *q = alph[result];

                    }
                    *q = alph [(i - key) % 26];
                }

            }

        }

    }

    *(decrypt + strlen(ciphertext)) = '\0';
    return decrypt;

}

// This function takes a null terminated string, plaintext and a second null terminated string key
//as arguments. The result is a new, dynamically allocated null terminated string containing the
//ciphertext

char * vigen_encrypt(char *plaintext, char *key) {

    char *padded = (char *) malloc((strlen(plaintext) + 1) * sizeof(char)); // encrpyted message

    char *p , *q;

    char alph[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};  // alphabet string

    int iresult , jresult;

    for(p = key , q = padded; strlen(padded) < strlen(plaintext) - 1 ; p++ , q++) {

        if (*p == '\0') {
            p = p - strlen(key);

        }

        *q = *p;

    }

    for(p = plaintext , q = padded; *p != '\0'; p++ , q++) {

        // if it is punctuation just skip over it

        if(!isalpha(*p)){

            *q = *p;

        } else {

            *p = toupper((unsigned char) *p); // ciphertext requires all uppercase

            // find the postion of p in alph

            for(int i = 0; alph[i] != 0 ; i++) {

                if (*p == alph[i]) {

                    iresult = i;
                    break;

                }

            }

            // find the postion of q in alph

            for(int j = 0 ; alph[j] != 0; j++) {

                if (*q == alph[j]) {

                    jresult = j;
                    break;

                }

            }

            // calculate the sum of the postions

            *p = alph[(iresult + jresult) % 26];

        }

    }

    return plaintext;

}

// This function takes a null terminated string, ciphertext and a second null terminated string key
//as arguments. The result is a new dynamically allocated null terminated string containing the
//plaintext

char * vigen_decrypt(char *ciphertext, char *key) {

    char *padded = (char *) malloc((strlen(ciphertext) + 1) * sizeof(char)); // encrpyted message

    char *p , *q;

    char alph[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};  // alphabet string

    int iresult , jresult;

    int result; // used for negative keys

    for(p = key , q = padded; strlen(padded) < strlen(ciphertext) - 1 ; p++ , q++) {

        if (*p == '\0') {
            p = p - strlen(key);

        }

        *q = *p;

    }

    for(p = ciphertext , q = padded; *p != '\0'; p++ , q++) {

        // if it is punctuation just skip over it

        if(!isalpha(*p)){

            *q = *p;

        } else {

            *p = toupper((unsigned char) *p);

            // find the postion of p in alph

            for(int i = 0; alph[i] != 0 ; i++) {

                if (*p == alph[i]) {

                    iresult = i;
                    break;

                }

            }

            // find the postion q in alph

            for(int j = 0 ; alph[j] != 0; j++) {

                if (*q == alph[j]) {

                    jresult = j;
                    break;

                }

            }

            // calculate the sum of the postions

            result = (iresult - jresult) % 26;

            if(result < 0){

                result = 26 + result;
                *p = alph[result];

            }

            *p = alph[result % 26];

        }

    }

    return ciphertext;

}

// This function takes a null terminated string, ciphertext and an array of doubles of size 26

void freq_analysis(char *ciphertext, double letters[26]) {

    char *cipher = (char *)malloc((strlen(ciphertext) + 1) * sizeof(char));

    char *current;

    double total = 0; // counter for all letters

    int i = 0;

    if(cipher == NULL) {
        printf("Error, allocating memory");
        exit(EXIT_FAILURE);
    }

    // copy plaintext to cipher text
    strcpy(cipher,ciphertext);

    // set everything to 0
    for(i = 0; i < 26; i++) {

        *(letters + i) = 0.0;

    }

    for(current = cipher; *current != '\0'; current++) {

        if((int)*current >= 65 && (int)*current <= 90) {

            *(letters + ((int)*current - 65)) += 1;
            total++;

        } else {
            continue;
        }

    }

    current = current - strlen(cipher);

    for(i = 0; i < 26; i++) {

        *(letters + i) = (*(letters + i) / total)*100;

    }


}



