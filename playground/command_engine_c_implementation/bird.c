#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <string.h>


int main(void) {
    char input[] = "A bird came down the walk"; // use a modifiable array
    printf("Parsing the input string '%s'\n", input);
    char* token = strtok(input, " ");

    while(token) {
        puts(token);
        token = strtok(NULL, " ");
    }

    printf("Contents of the input string now: ' ");
    for(size_t n=0; n < sizeof input; ++n) {
        input[n] ? putchar(input[n]) : fputs("\\0", stdout);

    }

    puts("' ");

#ifdef __STDC_WANT_LIB_EXT1__
    char str[] = "A bird came down the walk";
    size_t strmax = sizeof str;
    const char* delim = " ";
    char* next_token;
    printf("Parsing the input string '%s'\n", input);

    token = strtok_s(str, &strmax, delim, &next_token);
    while(token) {
        puts(token);
        token = strtok_s(NULL, &strmax, delim, &next_token);
    }

    printf("Contents of the input string now: '");
    for (size_t n =0 ; n <sizeof str; n++) {
        str[n] ? putchar(str[n]) : fputs("\\0", stdout);
    }

#endif


}