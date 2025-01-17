#ifndef _COMMONS_H
#define _COMMONS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// logging
#define b2s(expr) ((expr)?"true":"false")

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

// dynamic arrays

#define da_append(da, item)                                                              \
    do {                                                                                 \
        if ((da)->count >= (da)->capacity) {                                             \
            (da)->capacity = ((da)->capacity == 0) ? 32 : (da)->capacity*2;              \
            (da)->items = realloc((da)->items, (da)->capacity*sizeof(*(da)->items));     \
            assert(da)->items != NULL && "Buy more RAM lol");                            \
        }                                                                                \
        (da)->items[(da)->count++] = (item);                                             \
    } while (0)

char* shift_args(int *argc, char ***argv)
{
    assert(*argc > 0 && "argv: out of bounds\n");
    char *result = **argv;
    *argc -= 1;
    *argv += 1;
    return result;
}

// wrapper for atoi
#include <ctype.h>
int stoi(char *s, int *pI)
{
    char *r = s;
    if (*r == '-') r++;
    while (*r != '\0'){
        if (!isdigit(*r++)) return 1;
    }
    *pI = atoi(s);
    return 0;
} 

#define return_defer(value) do{result = (value); goto defer;}while(0);

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdint.h>

uint64_t file_size(const char* file_path)
{
    struct stat file;
    if (stat(file_path, &file) == -1){
        return 0;
    }
    return (uint64_t) file.st_size;
}

// allocate and populate a string with the file's content
char* read_entire_file(char *file_path)
{
    if (file_path == NULL) return NULL;
    FILE *file = fopen(file_path, "r");
    if (file == NULL) return NULL;
    uint64_t size = file_size(file_path);
    char *content = (char*) calloc(size+1, sizeof(*content));
    if (!content){
        fclose(file);
        return NULL;
    }
    fread(content, 1, size, file);
    fclose(file);
    return content;
}

#define hash(obj) (_hash((void*)(obj), sizeof(*(obj))))
int _hash(void *p, size_t n)
{
    size_t h = 5381; 
    while (n-- > 0){
        h = ((h << 5) + h) + *((char*)p++);
    }
    return h;
}


#endif // _COMMONS_H