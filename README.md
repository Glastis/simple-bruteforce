# Simple md5 bruteforce

That's a project "for fun". If you really want to bruteforce something, you probably should use a tool that handle GPU calculation. This one only use CPU (and only one thread, what a shame).

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
