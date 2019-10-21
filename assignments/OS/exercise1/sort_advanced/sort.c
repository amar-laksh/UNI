#define _POSIX_C_SOURCE 200809L
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHAR 1
#define CHUNK CHAR * 8
#define OUT_OF_MEMORY -1
#define OVERFLOW -26
#define UNDERFLOW -27
#define INVALID_PTR -28

typedef char* String;

typedef struct {
    int lines;
    int index;
    ssize_t chars;
    size_t mem_used;
    size_t total_mem;
    size_t mem_left;
    String* words;
} Text;

void __error_out(char* msg, int code)
{
    perror(msg);
    exit(code);
}

void ptr_init(Text* input)
{
    input->lines = CHUNK;
    input->total_mem = (size_t)(CHUNK * input->lines);
    input->words = (String*)malloc(input->total_mem);
    if (input->words == NULL)
	exit(OUT_OF_MEMORY);
    for (size_t i = 0; i < (size_t)input->lines; ++i) {
	input->words[i] = (String)malloc(CHUNK);
	if (input->words[i] == NULL)
	    exit(OUT_OF_MEMORY);
    }
}
void ptr_free(Text* input)
{
    // Free lines
    for (int i = 0; i < input->lines; i++) {
	free(input->words[i]);
    }
    // Freeing memory of strings
    free(input->words);
}

void print_input(Text* input)
{
    for (int i = 0; i < input->lines; i++) {
	printf("%s", (input->words)[i]);
    }
}
void __show_memory(Text* input)
{
    size_t mem_used = (size_t)(CHUNK * input->chars);
    size_t mem_left = input->total_mem - mem_used;

    printf("MEMORY:\ttotal: %ld,\tused: %ld,\tleft: %ld\n", input->total_mem, mem_used, mem_left);
}
void __update_text_mem(Text* input)
{
    if (input->mem_used < SIZE_MAX / (input->mem_used * CHUNK)) {
	input->total_mem += (input->mem_used * CHUNK);
	String* p = (String*)realloc(input->words, input->total_mem);
	if (p == NULL)
	    __error_out((char*)"Invalid pointer detected\n", INVALID_PTR);
	input->words = p;
    } else if (input->total_mem < 0)
	__error_out((char*)"Underflow detected!\n", UNDERFLOW);
    else
	__error_out((char*)"Overflow detected!\n", OVERFLOW);
}

Text sort_input(Text* input)
{
    String f_string, s_string;
    for (int i = 0; i < input->lines - 1; i++) {
	for (int j = i + 1; j < input->lines; j++) {
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

/** ssize_t __getline(Text* input) */
/** { */
/** input->chars = 0; */
/** input->lines = 0; */
/** input->mem_used = 0; */
/** char ch = '.'; */
/** while ((ch = getchar()) != (char)0xffffff) { */
/** [> printf("%c, %c, %ld,  %d\n", ch, *(*(input->words + input->lines) + input->chars), input->chars, input->lines); <] */
/** input->mem_used = (size_t)(CHUNK * input->chars + 1); */
/** if (input->mem_used >= input->total_mem) */
/** __update_text_mem(input); */
/** [> __show_memory(input); <] */
/** if (ch != '\n') { */
/** *(*(input->words + input->lines) + input->chars) = (char)ch; */
/** input->chars++; */
/** } else if (ch == '\n') { */
/** if (input->chars == 0) { */
/** *(*(input->words + input->lines) + (input->chars++)) = '\n'; */
/** *(*(input->words + input->lines) + (input->chars++)) = '\0'; */
/** return input->chars; */
/** } */
/** *(*(input->words + input->lines) + (input->chars)) = '\0'; */
/** return input->chars; */
/** } */
/** } */
/** if (*(*(input->words + input->lines) + (input->chars)) == '\0') */
/** return input->chars; */
/** [> printf("CHAR: %x\n", ch); <] */
/** return -1; */
/** } */
/**  */

ssize_t __getline(Text* input)
{
    input->chars = 0;
    input->lines = 0;
    input->mem_used = 0;
    char ch = '.';
    while ((ch = getchar()) != (char)0xffffff) {
	/** printf("%c, %c, %ld,  %d\n", ch, *(*(input->words + input->lines) + input->chars), input->chars, input->lines); */
	input->mem_used = (size_t)(CHUNK * input->chars + 1);
	if (input->mem_used >= input->total_mem)
	    __update_text_mem(input);
	/** __show_memory(input); */
	*(*(input->words + input->lines) + input->chars) = (char)ch;
	input->chars++;
	*(*(input->words + input->lines) + input->chars) = '\0';
    }

    if (*(*(input->words + input->lines) + (input->chars)) == '\0') {
	if (*(*(input->words + input->lines) + (input->chars - 1)) == '\0') {
	    *(*(input->words + input->lines) + (input->chars)) = '\n';
	}
	/** *(*(input->words + input->lines) + (input->chars++)) = '\n'; */
	/** *(*(input->words + input->lines) + (input->chars)) = '\n'; */
	*(*(input->words + input->lines) + (input->chars + 1)) = '\0';
	return input->chars;
    }
    /** printf("CHAR: %x\n", ch); */
    return -1;
}

void get_input(Text* input)
{
    ssize_t index = 0;
    input->chars = 0;
    input->lines = 0;
    input->mem_used = 0;
    input->index = index;
    /**     char ch; */
    /** while ((ch = getchar()) != EOF) { */
    /**  */
    /** input->mem_used = (size_t)(CHUNK * input->chars); */
    /** input->mem_left = input->total_mem - input->mem_used; */
    /** [> __show_memory(input); <] */
    /** if (input->mem_used >= input->total_mem) */
    /** __update_text_mem(input); */
    /** if (ch != '\n') { */
    /** *(*(input->words + input->lines) + index) = (char)ch; */
    /** [> printf("%c, %c, %d,  %d\n", ch, *(*(input->words + input->lines) + index), index, input->lines); <] */
    /** if (input->index < index) */
    /** input->index */
    /** = index; */
    /** input->chars++; */
    /** index++; */
    /** } else { */
    /** *(*(input->words + input->lines) + index) = '\0'; */
    /** index = 0; */
    /** [> printf("%s, LINE=%d\n", input->words[input->lines], input->lines); <] */
    /** input->lines++; */
    /** input->words[input->lines] = (String)malloc(input->mem_used); */
    /** [> free(input->words[input->lines]); <] */
    /** } */
    /** } */
    while (index != -1) {
	while ((index = getline(&input->words[input->lines], &input->mem_used, stdin)) && index != -1) {
	    input->chars += index;
	    /** __show_memory(input); */
	    /** while ((index = __getline(input)) && index != -1) { */
	    input->lines++;
	    /** printf("DEBUG: %ld, %ld\n", input->mem_used, index); */
	    input->words[input->lines] = (String)malloc(CHUNK * input->chars);
	    if (input->words == NULL)
		exit(OUT_OF_MEMORY);
	    if (input->mem_used >= input->total_mem)
		__update_text_mem(input);
	}
	free(input->words[input->lines]);
    }
}
int main(int argc, char** argv)
{
    Text input;
    ptr_init(&input);
    get_input(&input);
    print_input(&input);

    /** Text sorted_input = sort_input(&input); */
    /** print_input(&sorted_input); */
    /** ptr_free(&input); */
    return 0;
}
