#include "Computing.h"

void Print(FILE* output_file, char* buffer, int buffer_size)
{
	fprintf(output_file, "%s", buffer);

	int primary_checking = Primary_Check(buffer, buffer_size);
	switch (primary_checking)
	{
	case 0:
		fprintf(output_file, " == ");
		break;
	case 1:
		fprintf(output_file, "\n");
		return;
	case 2:
		fprintf(output_file, " == ERROR: incorrect input\n");
		return;
	default:
		break;
	}

	int lexeme_checking = Lexeme_Check(buffer, buffer_size);
	if (lexeme_checking == 1)
	{
		fprintf(output_file, "ERROR: lexems\n");
		return;
	}

	int size = DelSpace(buffer, buffer_size);
	int secondary_checking = Secondary_Check(buffer, size);
	switch (secondary_checking)
	{
	case 1:
		fprintf(output_file, "ERROR: brackets\n");
		return;
	case 2:
		fprintf(output_file, "ERROR: incorrect points\n");
		return;
	case 3:
		fprintf(output_file, "ERROR: incorrect signs\n");
		return;
	default:
		break;
	}

	double result;
	int fail = Pre_Compute(buffer, size, &result);
	switch (fail)
	{
	case 0:
		fprintf(output_file, "%g\n", result);
		break;
	case 1:
		fprintf(output_file, "ERROR: division by zero\n");
		break;
	case 2:
		fprintf(output_file, "ERROR: error in signs\n");
		break;
	case 3:
		fprintf(output_file, "ERROR: not a number\n");
		break;
	case 4:
		fprintf(output_file, "ERROR: incorrect function\n");
		break;
	case 5:
		fprintf(output_file, "ERROR: incorrect function expression\n");
		break;
	case 6:
		fprintf(output_file, "ERROR: no numbers\n");
		break;
	case 7:
		fprintf(output_file, "ERROR: incorrect expression with \"pi\" or \"e\"\n");
		break;
	case 8:
		fprintf(output_file, "ERROR: incorrect scientific notation\n");
		break;
	case 9:
		fprintf(output_file, "ERROR: an expression under the ARCSIN modulo more than one\n");
		break;
	case 10:
		fprintf(output_file, "ERROR: an expression under the ARCCOS modulo more than one\n");
		break;
	case 11:
		fprintf(output_file, "ERROR: expression under SQRT is less than zero\n");
		break;
	case 12:
		fprintf(output_file, "ERROR: expression under LN is less than zero\n");
		break;
	case 13:
		fprintf(output_file, "ERROR: infinity\n");
		break;
	case 14:
		fprintf(output_file, "ERROR: nothing in brackets\n");
		break;
	case 15:
		fprintf(output_file, "ERROR: why 2(2+2) or (2+2)2 is error??\n");
		break;
	case 16:
		fprintf(output_file, "ERROR: not enough memory\n");
		break;
	default:
		fprintf(output_file, "ERROR: ...\n");
		break;
	}
}


int main(int argc, char* argv[])
{
	FILE* input_file = stdin;
	FILE* output_file = stdout;
	if (argc > 3)
	{
		printf("ERROR: not correct parameters");
		return 1;
	}
	if (argc > 1)
		fopen_s(&input_file, argv[1], "r");
	if (argc > 2)
		fopen_s(&output_file, argv[2], "w");

	int size_of_array = 100, index = 0, current_char;
	char* array_of_stdin = (char*)malloc(size_of_array);
	char* temp;
	bool not_enough_memory = false;

	if (array_of_stdin == NULL)
	{
		fprintf(output_file, "ERROR: not enough memory\n");
		return 0;
	}

	while ((current_char = getc(input_file)) != EOF)
	{
		array_of_stdin[index++] = (char)current_char;
		if (index == size_of_array)
		{
			temp = (char*)realloc(array_of_stdin, size_of_array += 100);
			if (temp == NULL)
			{
				while ((current_char = getc(input_file)) != EOF && current_char != '\n');
				fprintf(output_file, "ERROR: not enough memory\n");
				not_enough_memory = true;
				index = 0;
				size_of_array -= 100;
				if (current_char == EOF)
					break;
			}
			else
				array_of_stdin = temp;
		}

		if ((current_char == '\n') && (not_enough_memory == false))
		{
			array_of_stdin[--index] = '\0';
			Print(output_file, array_of_stdin, index);
			index = 0;
		}
		not_enough_memory = false;
	}
	if (index != 0)
	{
		array_of_stdin[index] = '\0';
		Print(output_file, array_of_stdin, index);
	}

	fclose(input_file);
	fclose(output_file);
	free(array_of_stdin);
	return 0;
}