#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 20

typedef char* String;

typedef struct {
    String words[LIMIT];
} Text;

void print_input(Text* input)
{
    for (int i = 0; i < LIMIT; i++) {
	if (*input->words[i] != '\0') {
	    printf("%s\n", (input->words)[i]);
	}
    }
}
Text sort_input(Text* input)
{
    String f_string, s_string;
    for (int i = 0; i < 19; i++) {
	for (int j = i + 1; j < LIMIT; j++) {
	    f_string = input->words[i];
	    s_string = input->words[j];
	    if (*f_string != '\0' && *s_string != '\0') {
		if (strcmp(f_string, s_string) > 0) {
		    input->words[i] = s_string;
		    input->words[j] = f_string;
		}
	    }
	}
    }
    return *input;
}

void get_input(Text* input)
{
    int index = 0, line = 0;
    char c;
    while ((c = getchar()) != EOF) {
	if (c != '\n') {
	    *(*(input->words + line) + index) = c;
	    index = index + 1;
	} else {
	    *(*(input->words + line) + index) = '\0';
	    index = 0;
	    line++;
	}
    }
}
int main(int argc, char** argv)
{
    Text input;

    // Allocating memory for strings
    for (int i = 0; i < LIMIT; ++i) {
	*(input.words + i) = (String)malloc(sizeof(char) * LIMIT);
    }

    get_input(&input);

    Text sorted_input = sort_input(&input);
    print_input(&sorted_input);

    // Freeing memory for strings
    for (int i = 0; i < LIMIT; ++i) {
	free(*(input.words + i));
    }
    return 0;
}
