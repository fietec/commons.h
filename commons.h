#ifndef _COMMONS_H
#define _COMMONS_H

#include <stdio.h>
#include <stdlib.h>

// logging

#define ansi_rgb(r, g, b) ("\e[38;2;" #r ";" #g ";" #b "m")
#define ansi_end ("\e[0m")

#define printfn(msg, ...) (printf(msg "\n", ##__VA_ARGS__))
#define log(msg, ...) (printf("%s:%d " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__))

#ifndef DEBUGS_COLOR
	#define eprintfn(msg, ...) (fprintf(stderr, "[ERROR] %s:%d " msg "\n", __FILE__,  __LINE__, ##__VA_ARGS__))
	#define iprintfn(msg, ...) (printf("[INFO] %s:%d " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__))
#else
	#define eprintfn(msg, ...) (fprintf(stderr, "%s[ERROR] %s:%d " msg "\n%s", ansi_rgb(196, 0, 0), __FILE__, __LINE__, ##__VA_ARGS__, ansi_end))
	#define iprintfn(msg, ...) (fprintf(stdout, "%s[INFO] %s:%d " msg "\n%s", ansi_rgb(0, 196, 196), __FILE__, __LINE__, ##__VA_ARGS__, ansi_end))
#endif // DEBUGS_COLOR

// arrays

#define arr_len(arr) (sizeof((arr)) / sizeof((arr)[0]))

// assertions

#define cassert(state, msg, ...) do{if (!state) {eprintfn(msg, ##__VA_ARGS__); exit(1);}}while(0)
#endif // _COMMONS_H