#include "Computing.h"

int Primary_Check(char* str, int size)
{
	int index = 0;
	if (str[index] < 0)
		return 2;
	for (; index < size && str[index] >= 0 && isspace(str[index]); index++);
	if (index == size || (str[index] == '/' && str[index + 1] == '/'))     //пустая строка или комментарий
		return 1;
	for (int i = index; i < size; i++)
		if (str[i] < 0 || !(isspace(str[i]) || isalnum(str[i]) || str[i] == '(' || str[i] == ')' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == '.'))
			return 2;
	return 0;
}

int Secondary_Check(char* string, int size)
{
	int number_of_open_brackets = 0, number_of_closed_brackets = 0, count = 0;

	if (string[0] == '.')
		return 2;

	for (int i = 0; i < size; i++)
	{
		if (string[i] == '(')
			number_of_open_brackets++;
		if (string[i] == ')')
			number_of_closed_brackets++;
		if (number_of_open_brackets < number_of_closed_brackets)
			return 1;

		if ((string[i] == '.') && (isdigit(string[i + 1]) == 0))
			return 2;
		if (((string[i] == '+') || (string[i] == '-') || (string[i] == '*') || (string[i] == '/') || (string[i] == '^')) && ((string[i + 1] == '*') || (string[i + 1] == '/') || (string[i + 1] == '^')))
			return 3;

		if (isdigit(string[i]) || string[i] == '.')
		{
			if (string[i] == '.')
				count++;
			if (count > 1)
				return 2;
		}
		else
			count = 0;
	}
	if (number_of_open_brackets != number_of_closed_brackets)
		return 1;

	return 0;
}

int Lexeme_Check(char* string, int size)
{
	struct
	{
		enum
		{
			symbol,
			digit,
			point,
			plus,
			scientific,
			nosign
		}sign;
		int index_in_string;
	}new_sign, old_sign;

	new_sign.index_in_string = 0;
	old_sign.index_in_string = 0;
	new_sign.sign = nosign;
	old_sign.index_in_string = nosign;

	for (int i = 0; i < size; i++)
	{
		old_sign.index_in_string = new_sign.index_in_string;
		old_sign.sign = new_sign.sign;

		if (old_sign.sign != symbol && ((string[i] == 'e') || (string[i] == 'E')))
		{
			new_sign.sign = scientific;
			new_sign.index_in_string = i;
		}
		else if (isalpha(string[i]))
		{
			new_sign.sign = symbol;
			new_sign.index_in_string = i;
		}
		else if (isdigit(string[i]))
		{
			new_sign.sign = digit;
			new_sign.index_in_string = i;
		}
		else if (string[i] == '.')
		{
			new_sign.sign = point;
			new_sign.index_in_string = i;
		}
		else if (string[i] == '+')
		{
			new_sign.sign = plus;
			new_sign.index_in_string = i;
		}
		else if (isspace(string[i]) == 0)
		{
			new_sign.sign = nosign;
			new_sign.index_in_string = 0;
			old_sign.sign = nosign;
			old_sign.index_in_string = 0;
		}

		if (new_sign.sign != nosign && old_sign.sign != nosign)
			if (new_sign.index_in_string - old_sign.index_in_string > 1 && (new_sign.sign == old_sign.sign || (old_sign.sign == digit && new_sign.sign == scientific) || (old_sign.sign == scientific && new_sign.sign == digit)))
				return 1;
	}
	return 0;
}

int DelSpace(char* string, int size)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (isspace(string[i]))
			count++;
		else
			string[i - count] = string[i];
	}
	string[size - count] = '\0';
	return size - count;
}