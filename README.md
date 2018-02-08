# Simple md5 bruteforce

md5 implementation from https://github.com/kikito/md5.lua - thanks

## Classic bruteforce
```BASH
make
./a.out hash_to_reverse [-v[v]]
```
You will need openssl to build it.

## Dictionary
```BASH
lua main.lua dictionary_path hash_to_reverse [-v]
```
