# Simple md5 bruteforce

That's a project "for fun". If you really want to bruteforce something, you probably should use a tool that handle GPU calculation. This one only use CPU (and only one thread, what a shame).

md5 implementation from https://github.com/kikito/md5.lua - thanks

## Classic bruteforce

### Build and usage
```
make
./a.out hash_to_reverse [options]
```
You will need openssl to build it.

### Options
```
./a.out hash    [-v[v]]         verbose mode lvl 1/2 (print on error output).
                [-r begin_with] provide password to begin with.
                [-f filepath]   provide file that contains hash to reverse.
                [-o filepath]   specify output file.
                [-q]            supress default output (not including verbose and file output).
```

## Dictionary

```
lua main.lua dictionary_path hash_to_reverse [-v]
```
