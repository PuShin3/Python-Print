#ifndef PYTHON_PRINT_INCLUDED
#define PYTHON_PRINT_INCLUDED

#include<iostream>

// Using macros from stackoverflow:
// https://stackoverflow.com/questions/1826464/c-style-strings-as-template-arguments
// from the user Jordi Espada

#define _MAX_W_COUNT 100
#define _W_MIN(a,b) (a)<(b)?(a):(b)
#define _W(s)\
&_Word<getChr(s, 0), \
	getChr(s, 1), \
	getChr(s, 2), \
	getChr(s, 3), \
	getChr(s, 4), \
	getChr(s, 5), \
	getChr(s, 6), \
	getChr(s, 7), \
	getChr(s, 8), \
	getChr(s, 9), \
	getChr(s, 10), \
	getChr(s, 11), \
	getChr(s, 12), \
	getChr(s, 13), \
	getChr(s, 14), \
	getChr(s, 15), \
	getChr(s, 16), \
	getChr(s, 17), \
	getChr(s, 18), \
	getChr(s, 19), \
	getChr(s, 20), \
	getChr(s, 21), \
	getChr(s, 22), \
	getChr(s, 23), \
	getChr(s, 24), \
	getChr(s, 25), \
	getChr(s, 26), \
	getChr(s, 27), \
	getChr(s, 28), \
	getChr(s, 29), \
	getChr(s, 30), \
	getChr(s, 31), \
	getChr(s, 32), \
	getChr(s, 33), \
	getChr(s, 34), \
	getChr(s, 35), \
	getChr(s, 36), \
	getChr(s, 37), \
	getChr(s, 38), \
	getChr(s, 39), \
	getChr(s, 40), \
	getChr(s, 41), \
	getChr(s, 42), \
	getChr(s, 43), \
	getChr(s, 44), \
	getChr(s, 45), \
	getChr(s, 46), \
	getChr(s, 47), \
	getChr(s, 48), \
	getChr(s, 49), \
	getChr(s, 50), \
	getChr(s, 51), \
	getChr(s, 52), \
	getChr(s, 53), \
	getChr(s, 54), \
	getChr(s, 55), \
	getChr(s, 56), \
	getChr(s, 57), \
	getChr(s, 58), \
	getChr(s, 59), \
	getChr(s, 60), \
	getChr(s, 61), \
	getChr(s, 62), \
	getChr(s, 63), \
	getChr(s, 64), \
	getChr(s, 65), \
	getChr(s, 66), \
	getChr(s, 67), \
	getChr(s, 68), \
	getChr(s, 69), \
	getChr(s, 70), \
	getChr(s, 71), \
	getChr(s, 72), \
	getChr(s, 73), \
	getChr(s, 74), \
	getChr(s, 75), \
	getChr(s, 76), \
	getChr(s, 77), \
	getChr(s, 78), \
	getChr(s, 79), \
	getChr(s, 80), \
	getChr(s, 81), \
	getChr(s, 82), \
	getChr(s, 83), \
	getChr(s, 84), \
	getChr(s, 85), \
	getChr(s, 86), \
	getChr(s, 87), \
	getChr(s, 88), \
	getChr(s, 89), \
	getChr(s, 90), \
	getChr(s, 91), \
	getChr(s, 92), \
	getChr(s, 93), \
	getChr(s, 94), \
	getChr(s, 95), \
	getChr(s, 96), \
	getChr(s, 97), \
	getChr(s, 98), \
	getChr(s, 99), \
	getChr(s, 100) \
>

#define getChr(name, i) ((_W_MIN(i, _MAX_W_COUNT)) < sizeof(name)/sizeof(*name) ? name[i]: '\0')

// Usage: _W("your text")
// This will result in a 'pointer' to the _Word class

template<char ... _Chars>
std::ostream& _Word(std::ostream& out) {
	return ((out << _Chars), ...);
}
// Actual print implementation
// Can specify the text of the seperator, end and start
template<
	std::ostream& (*_Seperator)(std::ostream&) = _W(" "),
	std::ostream& (*_End)(std::ostream&) = _W("\n"),
	std::ostream& (*_Start)(std::ostream&) = _W("")
>
struct print {

	// Base case
	print() {
		std::cout << *_End;
	}

	// Can pass in multiple args with different types
	// like in python
	template<typename T, typename... Tail>
	print(const T& t, Tail&&... tail) {
		std::cout << *_Start << t; // first print _Start, if any
		if (sizeof...(Tail)) { 
			// If there is still argument waiting to be printed,
			// cout the _Seperator
			std::cout << *_Seperator;
		}
		// Recursion, setting the _Start to empty string
		auto _ = print<_Seperator, _End, _W("")>(tail...);
	}
};

// Example: 

//	print("Hi");
//	output: 
//	Hi
//	
//	print<_W(", ")>("Eddie", "Adam", "Someone else", "blablabla");
//	output: Eddie, Adam, Someone else, blablabla
//	
//	print<_W(", "), _W("    End of the line!\n"), _W("Start of the line!    ")>(1, 2, 3, 4);
//	output: 
//	Start of the line!    1, 2, 3, 4    End of the line!
//	
//	_Word is like std::endl, std::fixed, etc,
//	which is a function that takes std::ostream& as a arg and returns std::ostream.
//	So you can absolutely pass in std::endl as the _End
// 
//	print<std::endl>("Hello", "World")
//	output: 
//	Hello		
//	World

#endif