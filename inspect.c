#include <stdio.h>
#include <string.h>

void inspect(char s[]) {
    int index = 0;
    printf("%s, length %ld: ", s, strlen(s));
    while(s[index] != 0) {
        char current = s[index];
        // %d means print as a SIGNED, 2's COMPLEMENT INTERPRETATION
        // char is a signed type
        printf("%c %d %u %hhu | ", current, current, current, current);
        index += 1;
    }
    printf("\n");
}

// Return 1, 2, 3, or 4, depending on the bit pattern at the beginning of c
int size_of_codepoint(char c) {
    // detect the 4 encoding cases in UTF-8
    // Using & with a mix of 1's and 0's is called "MASKING"
    if((c & 0b10000000) == 0b00000000) { return 1; }
    if((c & 0b11100000) == 0b11000000) { return 2; }
    if((c & 0b11110000) == 0b11100000) { return 3; }
    if((c & 0b11111000) == 0b11110000) { return 4; }
    return -1;
}

// Takes a UTF8-encoded string and returns the number of codepoints in it
// Returns -1 if the string has an invalid start byte
int utf8_strlen(char str[]) {
    int index = 0;
    int length = 0;
    while(str[index] != 0) {
        int size = size_of_codepoint(str[index]);
        if(size == -1) { return -1; }
        length += 1;
        index += size;
    }
    return length;
}


int main() {
    char example[] = { 97, 98, 99, 0 };
    inspect("abcd");
    inspect(example);

    char weird[] = { 0b11001000, 97, 98, 99, 0 };
    inspect(weird);

    char notweird[] = { 'J', 'o', 's', 195, 169, 0 };
    inspect(notweird);
    printf("Should be 2: %d\n", size_of_codepoint(notweird[3]));
    printf("Should be 4: %d\n", utf8_strlen(notweird));

    char crab[] = "🦀";
    inspect(crab);
    printf("Should be 4: %d\n", size_of_codepoint(crab[0]));
    printf("Should be 1: %d\n", utf8_strlen(crab));

    // binary of 200 (as bits):

    // 0b11001000

    // %u tries to print a 32-bit unsigned number
    // When char is "extended" to fit into 32 bits, it is "sign extended"

    // C thinks "Ah, we need the 32 bit version of 0b11001000"
    // So it extends bits to the left, copying the sign bit
    // "0b111111111111111111111111 11001000"
    // And then gives that to %u to print... as an unsigned number

    // %hhu means print an unsigned number of the SAME WIDTH/# OF BITS as the value
}
