# findfile.c

Searches for a file in a directory.

An implementation of a Search Tree, written in C.

## Usage

```bash
cd extension
make
./findfile <filename> # to find a file in current directory 
./findfile <filename> <path/to/search/in/> #to find a file in a specific directory
```

## Running Tests

- Compile ./test.c 
- Run it :D 

## Libraries Used
- [Minunit (for unit testing)](https://github.com/siu/minunit) 
- [tinydir (very small platform agnostic C directory and file reader)](https://github.com/cxong/tinydir)