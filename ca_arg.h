#ifndef _CA_ARG_H
#define _CA_ARG_H

#define ca_len(...) sizeof((typeof(__VA_ARGS__)[]){__VA_ARGS__})/sizeof(typeof(__VA_ARGS__))
#define ca_args(...) ca_len(__VA_ARGS__), __VA_ARGS__
#define ca_array(...) ca_len(__VA_ARGS__), (typeof(__VA_ARGS__)[]){__VA_ARGS__}

#endif // _CA_ARG_H