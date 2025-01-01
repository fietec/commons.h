#ifndef _COMMONS_H
#define _COMMONS_H

#include <stdio.h>
#include <stdlib.h>

// logging

// the ansi string representation of an rgb value
#define ansi_rgb(r, g, b) ("\e[38;2;" #r ";" #g ";" #b "m") 
// the ansi reset value
#define ansi_end ("\e[0m") 

// printf with new-line forced
#define printfn(msg, ...) (printf(msg "\n", ##__VA_ARGS__)) 
// wrapper for printf with file and line display
#define log(msg, ...) (printf("%s:%d " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__)) 

#ifndef COMMONS_COLOR // define this to enable color printing
	// wrapper for printf for printing errors
	#define eprintfn(msg, ...) (fprintf(stderr, "[ERROR] %s:%d " msg "\n", __FILE__,  __LINE__, ##__VA_ARGS__)) 
	// wrapper for printf for printf for debugging
	#define iprintfn(msg, ...) (printf("[INFO] %s:%d " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__)) 
#else
	// define color printing versions of the above macros
	#define eprintfn(msg, ...) (fprintf(stderr, "%s[ERROR] %s:%d " msg "\n%s", ansi_rgb(196, 0, 0), __FILE__, __LINE__, ##__VA_ARGS__, ansi_end))
	#define iprintfn(msg, ...) (fprintf(stdout, "%s[INFO] %s:%d " msg "\n%s", ansi_rgb(0, 196, 196), __FILE__, __LINE__, ##__VA_ARGS__, ansi_end))
#endif // COMMONS_COLOR

// arrays

// calculates the length of an array
#define arr_len(arr) (sizeof((arr)) / sizeof((arr)[0])) 

// assertions

// for classic assertion, uses eprintfn for printing the message
#define cassert(state, msg, ...) do{if (!state) {eprintfn(msg, ##__VA_ARGS__); exit(1);}}while(0) 

#endif // _COMMONS_H