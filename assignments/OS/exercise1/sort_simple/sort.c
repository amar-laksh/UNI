#include <stdio.h>

const int LINES = 20;
const int ROWS = 20;

typedef struct {
    char array[20][20];
} Text;

void print_input(Text input)
{
    printf("output:\n");
    for (int i = 0; i < 20; i++) {
	for (int j = 0; j < 20; j++) {
	    if (input.array[i][j] != '\0') {
		printf("%c", input.array[i][j]);
	    }
	}
    }
}

Text get_input(Text input)
{
    /** char input[20][20] = { '\0' }; */
    int index = 0, line = 0;
    char c;
    while (line < 20) {
	while ((c = getchar()) != '\n' && index <= 20) {
	    input.array[line][index] = c;
	    index = index + 1;
	}
	if (c == '\n') {
	    input.array[line][index] = '\n';
	    index = 0;
	}
	line++;
    }

    return input;
}
int main(int argc, char** argv)
{
    Text input = { '\0' };
    print_input(get_input(input));
    return 0;
}
