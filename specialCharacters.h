#include<unordered_map>
class SpecialCharacters {
	public:
		std::unordered_map<char, char> specialCharacters;

		SpecialCharacters() {

			specialCharacters['1'] = '!';
			specialCharacters['2'] = '@';
			specialCharacters['3'] = '#';
			specialCharacters['5'] = '%';
			specialCharacters['6'] = '^';
			specialCharacters['7'] = '&';
			specialCharacters['4'] = '$';
			specialCharacters['8'] = '*';
			specialCharacters['9'] = '(';
			specialCharacters['0'] = ')';
			specialCharacters['-'] = '_';
			specialCharacters['='] = '+';
			specialCharacters['['] = '{';
			specialCharacters[']'] = '}';
			specialCharacters[';'] = ':';
			specialCharacters['\''] = '\"';
			specialCharacters[','] = '<';
			specialCharacters['.'] = '>';
			specialCharacters['/'] = '?';
			specialCharacters['\\'] = '|';
			specialCharacters['`'] = '~';
		}
};
