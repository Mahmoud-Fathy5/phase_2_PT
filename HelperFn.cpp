#include "HelperFn.h"

bool IsValue(string input)
{

	// checks if the input string is a double value
	// return true if it's double value, false otherwise

	// Double values can be: 12.5, -12.5, -23, -23. , -23.0 …etc.
	// 
	//TODO: complete this function
	for (int i = 0, dot_counter = 0; i < input.length(); i++) {
		if (isdigit(input[i])) {
			continue;
		}
		else if (input[i] == '.' && dot_counter < 1) {
			dot_counter++;
			continue;
		}
		else if (input[i] == '-' && i == 0) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

bool IsVariable(string input)
{
	if (!(isalpha(input[0]) || input[0] == '_')) {
		return false;
	}
	// checks if the input string is a variable name
	// return true if it can be a variable name, false otherwise

	// Variable names must start with an alphabetic letter (small or capital) or an underscore (_). 
	// After the first initial letter, variable names can contain letters, numbers and underscores.  
	// No spaces or special characters, however, are allowed.
	for (int i = 0; i < input.length(); i++) {
		if (!(input[i] == '_' || isalnum(input[i]))) {
			return false;
		}
	}
	//TODO: complete this function

	return true;
}

OpType ValueOrVariable(string input)
{

	// checks if the input string is a double value or a variable name
	// chand returns enum "OpType" (the enum is declared in the .h)

	//TODO: complete this function

	if (IsValue(input)) {
		return VALUE_OP;
	}
	if (IsVariable(input)) {
		return VARIABLE_OP;
	}

	return INVALID_OP;
}