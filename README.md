# 42 Academy+Plus - get_next_line

A 42 (school) project that required us to create a function capable of fetching information from multiple file descriptors line by line, being allowed to only read chunks of data of specific sizes - imagine reading chunks that contain 2 and a half lines, or a tenth of a line, having to return one single whole line, from multiple file descriptors at the same time, keeping everything organized -

For more details regarding the project see 'get_next_line - Subject(EN).pdf'

## How to use

Using a terminal from within the get_next_line directory:
- run the command `make -C libft` to create the library **libft.a**
- include **"get_next_line.h"** header in your project and use the function **get_next_line** wherever you need it
  - its prototype is `int				get_next_line(int const fd, char **line)` where **fd** is the file descriptor from which you will read and **line** is a pointer to a **char*** containing a line read from **fd** (if there was no error while processing the **fd** and there was a line to read)
  - the function will return **1** if a line WAS read, **0** if the reading has finished or **-1** if an error was encountered
- compile your code using the following commands:
```
gcc -Wall -Wextra -Werror -I **path_to**/libft/includes/ -c get_next_line.c
gcc -Wall -Wextra -Werror -I **path_to**/libft/includes/ -c yourSource.c
gcc -o yourBinaryName get_next_line.o yourSource.o -L **path_to**/libft/ -lft
```
Replace `**path_to**` with the right path to libft/includes/ and libft/.

**Done!** As long as you're reading from file descriptors that can be accesed, get_next_line should be able to fetch lines from multiple file descriptors at the same time without any problems.

# How to test

If you want to test the code, or your own implementation of fillit you can use 
- @jgigault's [42FileChecker](https://github.com/jgigault/42FileChecker)

and follow the instructions on his repository. (*Note: by the time you're reading this there's a good chance there are a lot more get_next_line testers out there, so look them up yourself as well.*)
