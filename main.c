#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORDS 10
#define MAX_ATTEMPTS 7
#define WORD_LENGTH 20

const char *wordList[MAX_WORDS] = {
    "programlama", "bilgisayar", "muhendislik", "teknoloji", "yazilim",
    "kodlama", "sifreleme", "algoritma", "veritabani", "agbilisim"
};

void getRandomWord(char *chosenWord) {
    srand(time(NULL));
    int randomIndex = rand() % MAX_WORDS;
    strcpy(chosenWord, wordList[randomIndex]);
}

void displayGameState(const char *guessedWord, int remainingAttempts, const char *guessedLetters, const char *guessedWords) {
    printf("\nKelime: %s\n", guessedWord);
    printf("Kalan Hak: %d\n", remainingAttempts);
    printf("Tahmin Edilen Harfler: %s\n", guessedLetters[0] ? guessedLetters : "Henüz yok");
    printf("Tahmin Edilen Kelimeler: %s\n", guessedWords[0] ? guessedWords : "Henüz yok");
}

int isLetterGuessed(char letter, const char *guessedLetters) {
    for (int i = 0; guessedLetters[i] != '\0'; i++) {
        if (guessedLetters[i] == letter) {
            return 1;
        }
    }
    return 0;
}

void updateGuessedWord(const char *word, char *guessedWord, char letter) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == letter) {
            guessedWord[i] = letter;
        }
    }
}

int isWordGuessed(const char *guess, const char *guessedWords) {
    const char *wordPtr = guessedWords;
    while (*wordPtr) {
        if (strstr(wordPtr, guess) == wordPtr) {
            return 1;
        }
        wordPtr += strlen(wordPtr) + 1;
    }
    return 0;
}

int main() {
    char chosenWord[WORD_LENGTH];
    char guessedWord[WORD_LENGTH];
    char guessedLetters[WORD_LENGTH] = "";
    char guessedWords[WORD_LENGTH * MAX_ATTEMPTS] = "";
    int remainingAttempts = MAX_ATTEMPTS;
    char guess[WORD_LENGTH];

    getRandomWord(chosenWord);
    int wordLength = strlen(chosenWord);
    for (int i = 0; i < wordLength; i++) {
        guessedWord[i] = '_';
    }
    guessedWord[wordLength] = '\0';

    printf("Adam Asmaca Oyununa Hoş Geldiniz!\n");

    while (remainingAttempts > 0) {
        displayGameState(guessedWord, remainingAttempts, guessedLetters, guessedWords);

        printf("\nBir harf veya kelime tahmin edin: ");
        scanf("%s", guess);

        if (strlen(guess) == 1) {
            char letter = guess[0];

            if (!isalpha(letter)) {
                printf("Geçersiz giriş! Lütfen bir harf giriniz.\n");
                continue;
            }
            if (isLetterGuessed(letter, guessedLetters)) {
                printf("Bu harfi zaten tahmin ettiniz! Başka bir harf deneyin.\n");
                continue;
            }

            strncat(guessedLetters, &letter, 1);
            if (strchr(chosenWord, letter)) {
                printf("Doğru tahmin!\n");
                updateGuessedWord(chosenWord, guessedWord, letter);
            } else {
                printf("Yanlış tahmin!\n");
                remainingAttempts--;
            }
        } else {
            if (isWordGuessed(guess, guessedWords)) {
                printf("Bu kelimeyi zaten tahmin ettiniz! Başka bir kelime deneyin.\n");
                continue;
            }

            strcat(guessedWords, guess);
            strcat(guessedWords, " ");

            if (strcmp(chosenWord, guess) == 0) {
                printf("\nTebrikler, kazandınız! Doğru kelime: %s\n", chosenWord);
                return 0;
            } else {
                printf("Yanlış kelime tahmini!\n");
                remainingAttempts--;
            }
        }

        if (strcmp(chosenWord, guessedWord) == 0) {
            printf("\nTebrikler, kazandınız! Doğru kelime: %s\n", chosenWord);
            return 0;
        }
    }

    printf("\nÜzgünüz, kaybettiniz. Doğru kelime: %s\n", chosenWord);
    return 0;
}
