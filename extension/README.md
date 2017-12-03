# findfile.c

Searches for a file in a directory.

You don't need to match case.

An implementation of a Search Tree, written in C.

Returns the full paths of any files it finds matching the input.

## Usage

```bash
cd extension
make
./findfile <filename> # to find a file in current directory
./findfile <filename> <path/to/search/in/> #to find a file in a specific directory
```

**NB:** do not include the angle brackets `<>`. For example, to find this README, you could type `./findunit readme`

## Running Tests

- We need some files to search from, so run `test_files/create_files.sh` to create 100 tiny text files with random names.


```
cd extension
make test
./findfile
```

## Libraries Used

- [Minunit (for unit testing)](http://www.jera.com/techinfo/jtns/jtn002.html) 
- [tinydir (very small platform agnostic C directory and file reader)](https://github.com/cxong/tinydir)

## References

- https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
- https://en.wikipedia.org/wiki/Binary_search_tree