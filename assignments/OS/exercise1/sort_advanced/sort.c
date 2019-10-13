#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHUNK 20

typedef char* String;

typedef struct {
    int lines;
    int index;
    String* words;
} Text;

int __pow(int x, int n)
{
    int i, number = 1;
    for (i = 0; i < n; ++i)
	number *= x;
    return (number);
}

void print_input(Text input)
{
    for (int i = 0; i < input.lines; i++) {
	if (*input.words[i] != '\0') {
	    printf("%s\n", (input.words)[i]);
	}
    }
}
Text sort_input(Text input)
{
    String f_string, s_string;
    for (int i = 0; i < input.lines - 1; i++) {
	for (int j = i + 1; j < input.lines; j++) {
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
	    *(*(input.words + line) + index) = (char)c;
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
    input.index = CHUNK;
    input.lines = CHUNK;

    size_t mem = (size_t)(sizeof(char) * input.lines * input.index + input.lines);

    printf("Trying to allocate %ld bytes of memory...\n", mem);
    input.words = (String*)malloc(mem);
    for (int i = 0; i < input.lines; ++i) {
	input.words[i] = (String)malloc(sizeof(char) * input.index);
    }
    printf("Memory Allocated!\n");
    get_input(input);

    Text sorted_input = sort_input(input);
    print_input(sorted_input);

    // Freeing memory of strings
    free(input.words);
    return 0;
}
