#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* String;

typedef struct {
    String words[20];
} Text;

void print_input(Text input)
{
    for (int i = 0; i < 20; i++) {
	if (*input.words[i] != '\0') {
	    printf("%s\n", (input.words)[i]);
	}
    }
}
Text sort_input(Text input)
{
    String f_string, s_string;
    for (int i = 0; i < 19; i++) {
	for (int j = i + 1; j < 20; j++) {
	    f_string = input.words[i];
	    s_string = input.words[j];
	    if (*f_string != '\0' && *s_string != '\0') {
		if (strcmp(f_string, s_string) > 0) {
		    input.words[i] = s_string;
		    input.words[j] = f_string;
		}
	    }
	}
    }
    return input;
}

void get_input(Text input)
{
    int index = 0, line = 0;
    char c;
    while ((c = getchar()) != EOF) {
	if (c != '\n') {
	    *(*(input.words + line) + index) = c;
	    /** printf("%c, %c, %d,  %d\n", c, *(*(input.words + line) + index), index, line); */
	    index = index + 1;
	} else {
	    *(*(input.words + line) + index) = '\0';
	    index = 0;
	    line++;
	}
    }
}
int main(int argc, char** argv)
{
    Text input;

    // Allocating memory for strings
    for (int i = 0; i < 20; ++i) {
	*(input.words + i) = (String)malloc(sizeof(char) * 20);
    }

    get_input(input);

    Text sorted_input = sort_input(input);
    print_input(sorted_input);

    // Freeing memory of strings
    for (int i = 0; i < 20; ++i) {
	free(*(input.words + i));
    }
    return 0;
}
