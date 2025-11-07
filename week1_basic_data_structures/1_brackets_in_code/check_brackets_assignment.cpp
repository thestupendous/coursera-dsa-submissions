#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Bracket {
	Bracket(char type, int position):
		type(type),
		position(position)
	{}

	bool Matchc(char c) {
		if (type == '[' && c == ']')
			return true;
		if (type == '{' && c == '}')
			return true;
		if (type == '(' && c == ')')
			return true;
		return false;
	}

	char type;
	int position;
};

int main() {
	std::string text;
	getline(std::cin, text);

	std::stack <Bracket> opening_brackets_stack;
	bool success{false},fail{false};
	for (int position = 0; position < text.length(); ++position) {
		// cout << "at pos: " << position << '\n';
		char next = text[position];

		if (next == '(' || next == '[' || next == '{') {
			// Process opening bracket, write your code here
			opening_brackets_stack.push({next,position});
		}

		if (next == ')' || next == ']' || next == '}') {
			// Process closing bracket, write your code here
			if (opening_brackets_stack.empty()){
				cout << position+1;
				fail=true;
				return 0;
				break;
			}
			Bracket top = opening_brackets_stack.top();
			if ( top.Matchc(next) == true) {
				// found matching opening bracket already in stack,
				// need to pop it
				opening_brackets_stack.pop();
			} else {
				// found first mismatch
				cout << position+1;
				fail=true;
				return 0;
				break;
			}
		}
	}
	if (!opening_brackets_stack.empty()) {
		// opening bracket case
		int firstPos{-1};
		while ( !opening_brackets_stack.empty() ) {
			firstPos = opening_brackets_stack.top().position;
			opening_brackets_stack.pop();
		}
		firstPos++;
		cout << firstPos;
		return 0;
	} else if (!fail) {
		cout << "Success";
	}
#if 0
	if ( !opening_brackets_stack.empty() ) {
		// found errors
		// now error resolution
		cout << "error aye\n";
		cout<< 
		// priority 1, first closing bracket
		// right se stack lagana hai, already stack me bachi values pe

		// next, first opening bracket
		// first opening bracket left side se jo mile
		
	// Printing answer, write your code here
	} else {
		cout << "Success\n";
	}

#endif

	return 0;
}
