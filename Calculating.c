#include "Computing.h"

int DelMinus(char* string, int size)
{
	int minuses = 0, index;
	for (int i = 0; i < size - 1; i++)
	{
		if ((string[i] == '-' || string[i] == '+') && (string[i + 1] == '-' || string[i + 1] == '+'))
		{
			index = i;
			while (string[i] == '+' || string[i] == '-')
			{
				if (string[i++] == '-')
					minuses++;
				if (i == size)
					break;
			}
			if (minuses % 2 == 0)
			{
				if (index == 0 || minuses != 0 && (string[index - 1] == '(' || string[index - 1] == '*' || string[index - 1] == '/' || string[index - 1] == '^'))
					string[index] = ' ';
				else
					string[index] = '+';
			}
			else
				string[index] = '-';
			for (int j = index + 1; j < i; j++)
				string[j] = ' ';
			size = DelSpace(string, size);
			i = index;
			minuses = 0;
		}
	}
	return size;
}

int Search_Priority(char* string, int start_index, int end_index)
{
	int index_of_preority_operation = -1, max_priority = 0, priority;
	for (int i = start_index; i < end_index; i++)
	{
		switch (string[i])
		{
		case '+':
			priority = 1;
			break;
		case '-':
			priority = 1;
			break;
		case '*':
			priority = 2;
			break;
		case '/':
			priority = 2;
			break;
		case '^':
			priority = 3;
			break;
		default:
			priority = 0;
			break;
		}

		if (priority == 3 || priority > max_priority)
		{
			index_of_preority_operation = i;
			max_priority = priority;
		}
	}
	return index_of_preority_operation;
}

int Search_Function(char* string, double* numbers, int start_index, int end_index)
{
	int max_word_size = 20, j = 0, index_elem_in_func = 0;
	char* func = (char*)malloc(max_word_size);
	if (func == NULL)
		return 16;

	bool function_correct = false;

	for (int i = start_index; i < end_index; i++)
	{
		if (isalpha(string[i]))
		{
			if (j == max_word_size)
			{
				free(func);
				return 4;
			}

			func[j++] = string[i];
		}
		else if (j != 0)
		{
			if (string[i] != '0' && string[i] != '-' && string[i + 1] != '0')
			{
				free(func);
				return 5;
			}

			for (int k = 0; k < i; k++)
				if (string[k] == '0')
					index_elem_in_func++;
			func[j] = '\0';
			if (string[i] == '-')
			{
				numbers[index_elem_in_func] = -numbers[index_elem_in_func];
				string[i] = ' ';
			}
			if (strcmp(func, "sin") == 0)
			{
				numbers[index_elem_in_func] = sin(numbers[index_elem_in_func]);
				function_correct = true;
			}
			else if (strcmp(func, "cos") == 0)
			{
				numbers[index_elem_in_func] = cos(numbers[index_elem_in_func]);
				function_correct = true;
			}
			else if (strcmp(func, "tg") == 0)
			{
				numbers[index_elem_in_func] = tan(numbers[index_elem_in_func]);
				function_correct = true;
			}
			else if (strcmp(func, "ctg") == 0)
			{
				numbers[index_elem_in_func] = 1 / tan(numbers[index_elem_in_func]);
				function_correct = true;
			}
			else if (strcmp(func, "arcsin") == 0)
			{
				if (fabs(numbers[index_elem_in_func]) > 1)
				{
					free(func);
					return 9;
				}
				numbers[index_elem_in_func] = asin(numbers[index_elem_in_func]);
				function_correct = true;
			}
			else if (strcmp(func, "arccos") == 0)
			{
				if (fabs(numbers[index_elem_in_func]) > 1)
				{
					free(func);
					return 10;
				}
				numbers[index_elem_in_func] = acos(numbers[index_elem_in_func]);
				function_correct = true;
			}
			else if (strcmp(func, "arctg") == 0)
			{
				numbers[index_elem_in_func] = atan(numbers[index_elem_in_func]);
				function_correct = true;
			}
			else if (strcmp(func, "sqrt") == 0)
			{
				if (numbers[index_elem_in_func] < 0)
				{
					free(func);
					return 11;
				}
				numbers[index_elem_in_func] = sqrt(numbers[index_elem_in_func]);
				function_correct = true;
			}
			else if (strcmp(func, "ln") == 0)
			{
				if (numbers[index_elem_in_func] < 0)
				{
					free(func);
					return 12;
				}
				numbers[index_elem_in_func] = log(numbers[index_elem_in_func]);
				function_correct = true;
			}
			else if (strcmp(func, "floor") == 0)
			{
				numbers[index_elem_in_func] = floor(numbers[index_elem_in_func]);
				function_correct = true;
			}
			else if (strcmp(func, "ceil") == 0)
			{
				numbers[index_elem_in_func] = ceil(numbers[index_elem_in_func]);
				function_correct = true;
			}

			if (function_correct == true)
			{
				for (int k = i - strlen(func); k < i; k++)
					string[k] = ' ';

				if (i - strlen(func) != 0 && string[i - strlen(func) - 1] == '0')
					string[i - strlen(func)] = '*';
			}
			else
			{
				free(func);
				return 4;
			}

			if (fabs(numbers[index_elem_in_func]) == INFINITY)
			{
				free(func);
				return 13;
			}
			if (isnan(numbers[index_elem_in_func]))
			{
				free(func);
				return 3;
			}

			j = 0;
			index_elem_in_func = 0;
			function_correct = false;
		}
	}
	if (j != 0)
	{
		free(func);
		return 4;
	}

	free(func);
	return 0;
}

int Compute(char* string, double* numbers, int start_index, int end_index, int amount_of_numbers, int* size)
{
	int function_error = Search_Function(string, numbers, start_index, end_index);
	if (function_error != 0)
		return function_error;
	int old_size = *size;
	*size = DelSpace(string, *size);
	end_index -= old_size - *size;


	int index_first_elem = 0;
	for (int i = 0; i < start_index; i++)
		if (string[i] == '0')
			index_first_elem++;

	int count_of_numbers_in_brackets = 0;
	for (int i = end_index; i >= start_index; i--)
		if (string[i] == '0')
			count_of_numbers_in_brackets++;
	int index_last_elem = index_first_elem + count_of_numbers_in_brackets - 1;

	if (count_of_numbers_in_brackets == 0)
		return 14;

	double result = 0;
	int index_of_priority_operation, index_elem_after_operation;
	while ((index_of_priority_operation = Search_Priority(string, start_index, end_index)) != -1)
	{
		index_elem_after_operation = index_first_elem;
		for (int i = start_index; i < index_of_priority_operation; i++)
			if (string[i] == '0')
				index_elem_after_operation++;

		if (string[index_of_priority_operation + 1] == '*' || string[index_of_priority_operation + 1] == '/' || string[index_of_priority_operation + 1] == '^')
			return 2;

		switch (string[index_of_priority_operation])
		{
		case '+':
		{
			if (index_elem_after_operation == index_first_elem)
				return 2;
			if (index_elem_after_operation > index_last_elem)
				return 2;

			result = numbers[index_elem_after_operation - 1] + numbers[index_elem_after_operation];
			break;
		}
		case '-':
		{
			if (index_elem_after_operation == index_first_elem)
			{
				numbers[index_first_elem] = -numbers[index_first_elem];
				string[index_of_priority_operation] = '0';
				string[index_of_priority_operation + 1] = ' ';
				break;
			}
			if (index_elem_after_operation > index_last_elem)
				return 2;

			result = numbers[index_elem_after_operation - 1] - numbers[index_elem_after_operation];
			break;
		}
		case '*':
		{
			if (index_elem_after_operation == index_first_elem)
				return 2;
			if (index_elem_after_operation > index_last_elem)
				return 2;
			if (string[index_of_priority_operation + 1] == '+')
				return 2;

			if (string[index_of_priority_operation + 1] == '-')
			{
				numbers[index_elem_after_operation] = -numbers[index_elem_after_operation];
				string[index_of_priority_operation + 2] = ' ';
			}
			result = numbers[index_elem_after_operation - 1] * numbers[index_elem_after_operation];
			break;
		}
		case '/':
		{
			if (numbers[index_elem_after_operation] == 0)
				return 1;
			if (index_elem_after_operation == index_first_elem)
				return 2;
			if (index_elem_after_operation > index_last_elem)
				return 2;
			if (string[index_of_priority_operation + 1] == '+')
				return 2;

			if (string[index_of_priority_operation + 1] == '-')
			{
				numbers[index_elem_after_operation] = -numbers[index_elem_after_operation];
				string[index_of_priority_operation + 2] = ' ';
			}
			result = numbers[index_elem_after_operation - 1] / numbers[index_elem_after_operation];
			break;
		}
		case '^':
		{
			if (index_elem_after_operation == index_first_elem)
				return 2;
			if (index_elem_after_operation > index_last_elem)
				return 2;
			if (string[index_of_priority_operation + 1] == '+')
				return 2;

			if (string[index_of_priority_operation + 1] == '-')
			{
				numbers[index_elem_after_operation] = -numbers[index_elem_after_operation];
				string[index_of_priority_operation + 2] = ' ';
			}
			result = pow(numbers[index_elem_after_operation - 1], numbers[index_elem_after_operation]);
			break;
		}
		default:
			break;
		}

		if (isnan(result))
			return 3;
		if (result == INFINITY)
			return 13;

		if (index_elem_after_operation != index_first_elem && index_elem_after_operation <= index_last_elem)
		{
			numbers[index_elem_after_operation - 1] = result;
			for (int i = index_elem_after_operation; i < amount_of_numbers - 1; i++)
				numbers[i] = numbers[i + 1];
			amount_of_numbers--;
			index_last_elem--;

			string[index_of_priority_operation] = ' ';
			string[index_of_priority_operation + 1] = ' ';
		}
	}

	if (string[start_index] == '(' && string[end_index] == ')')
	{
		if (start_index != 0 && string[start_index - 1] == '0')
				return 15;
		if (end_index + 1 < *size && string[end_index + 1] == '0')
				return 15;

		string[start_index] = ' ';
		string[end_index] = ' ';
	}
	*size = DelSpace(string, *size);
	return 0;
}

int Pre_Compute(char* string, int size, double* result)
{
	int size_of_numbers_array = 50;
	double* array_of_all_numbers = (double*)malloc(sizeof(double) * size_of_numbers_array);
	double* temp;
	if (array_of_all_numbers == NULL)
		return 16;

	int amount_of_numbers = 0;
	bool scientific_form = false;
	for (int i = 0; i < size;)
	{
		if (i < size - 1 && string[i] == 'p' && string[i + 1] == 'i')
		{
			array_of_all_numbers[amount_of_numbers++] = PI;
			if (i > 0 && string[i - 1] == '0')
				string[i++] = '*';
			else
				string[i++] = ' ';
			string[i++] = '0';

			if (isdigit(string[i]))
			{
				free(array_of_all_numbers);
				return 7;
			}
		}

		if (string[i] == 'e' && (!isalpha(string[i + 1])))
		{
			if ((i < size - 1) && isdigit(string[i + 1]))
			{
				free(array_of_all_numbers);
				return 7;
			}
			array_of_all_numbers[amount_of_numbers++] = exp(1);
			string[i++] = '0';
		}

		if (isdigit(string[i]))
		{
			scientific_form = false;

			array_of_all_numbers[amount_of_numbers++] = atof(string + i);

			string[i++] = '0';
			while (isdigit(string[i]) || string[i] == '.')
				string[i++] = ' ';

			if (string[i] == 'E')
				string[i] = 'e';

			if (string[i] == 'e' && (isdigit(string[i + 1]) || (i < size - 2 && (string[i + 1] == '+' || string[i + 1] == '-') && isdigit(string[i + 2]))))
			{
				scientific_form = true;
				string[i++] = ' ';
				if (string[i] == '+' || string[i] == '-')
					string[i++] = ' ';
			}
			else if (string[i] == 'e')
			{
				free(array_of_all_numbers);
				return 8;
			}

			if (scientific_form == true)
				while (isdigit(string[i]))
					string[i++] = ' ';

			if (string[i] == '.' || string[i] == 'e' || string[i] == 'E')
			{
				free(array_of_all_numbers);
				return 8;
			}
		}
		else
			i++;
		if (amount_of_numbers == size_of_numbers_array)
		{
			temp = (double*)realloc(array_of_all_numbers, (size_of_numbers_array += 50) * sizeof(double));
			if (temp == NULL)
			{
				free(array_of_all_numbers);
				return 16;
			}
			array_of_all_numbers = temp;
		}
	}

	int new_size = DelSpace(string, size);
	new_size = DelMinus(string, new_size);

	if (new_size == 1 && amount_of_numbers == 0)
	{
		free(array_of_all_numbers);
		return 6;
	}

	int error_in_compute = 0;
	int index_of_open_brackets, index_of_closed_brackets;
	while (new_size > 1)
	{
		index_of_open_brackets = -1, index_of_closed_brackets = -1;
		for (int i = 0; i < new_size; i++)
		{
			if (string[i] == '(')
				index_of_open_brackets = i;
			if (string[i] == ')')
			{
				index_of_closed_brackets = i;
				break;
			}
		}
		if (index_of_open_brackets == -1)
		{
			index_of_open_brackets = 0;
			index_of_closed_brackets = new_size;
		}

		if (index_of_closed_brackets - index_of_open_brackets == 1)
		{
			free(array_of_all_numbers);
			return 14;
		}

		error_in_compute = Compute(string, array_of_all_numbers, index_of_open_brackets, index_of_closed_brackets, amount_of_numbers, &new_size);
		if (error_in_compute != 0)
		{
			free(array_of_all_numbers);
			return error_in_compute;
		}
	}

	*result = array_of_all_numbers[0];
	free(array_of_all_numbers);
	return error_in_compute;
}