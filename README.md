# c-keyword-default
A simple C macro to make keyword default arguments inspired by `m1lkweed#4353`. See `main.c` for examples


# How it works

From `main.c`
```c
pythonize(void, foo, ARGS(int x, int y), KWARGS(int a; int b)) {
    printf("x: %d\ny: %d\na: %d\nb: %d\n", ARG(x), ARG(y), KWARG(a), KWARG(b));
};
```
Once expanded will generate something equivalent to 
```c
struct func_params_foo { int sentinel_; int a; int b; }; 
void foo(int x, int y , struct func_params_foo *args) {
    printf("x: %d\ny: %d\na: %d\nb: %d\n", x, y, args->a, args->b);
};
```

It is important to note that `ARGS(int x, int y)` keeps the arguments packed together.

For invoking such a function, it should be called through the `pythonic` macro
```c
pythonic(foo, 1, 2)(.a = 1);
```
Will expand into
```c
foo (1, 2 , (&(struct func_params_foo) { .sentinel_ = 0, .a = 1 }));
```

# Why not to use this
While it may appear to be incredibly easy to use, it will not be as easy to debug. Your linter will most likely reject any code using `pythonize` instantly. A better alternative is to simply create specialized structs for yourself.

For example, if you incorrectly miss an argument 
```c
pythonize(void, foo, ARGS(int x, int y), KWARGS(int a; int b)) {
    printf("x: %d\ny: %d\na: %d\nb: %d\n", ARG(x), ARG(y), KWARG(a), KWARG(b));
};

pythonic(foo, 1)(.a = 1);
```
You'll get this horrendous error message, something right out of a badly written C++ error message
```
<source>:14:43: warning: passing argument 2 of 'foo' makes integer from pointer without a cast [-Wint-conversion]
   14 |     func_name (__VA_ARGS__ __VA_OPT__(,) (&(struct func_params_ ## func_name) { .sentinel_ = 0,  wrap_pythonic
      |                                           ^
      |                                           |
      |                                           struct func_params_foo *
<source>:25:5: note: in expansion of macro 'pythonic'
   25 |     pythonic(foo, 1)(.a = 1); // returns 42
      |     ^~~~~~~~
<source>:20:38: note: expected 'int' but argument is of type 'struct func_params_foo *'
   20 | pythonize(void, foo, ARGS(int x, int y), KWARGS(int a; int b)) {
      |                                  ~~~~^
<source>:12:32: note: in definition of macro 'pythonize_II'
   12 |     function_ret function_name(__VA_ARGS__ __VA_OPT__(,) struct func_params_ ## function_name *args)
      |                                ^~~~~~~~~~~
<source>:5:62: note: in expansion of macro 'pythonize_I'
    5 | #define pythonize(function_ret, function_name, args, kwargs) pythonize_I(function_ret, function_name, kwargs, args)
      |                                                              ^~~~~~~~~~~
<source>:20:1: note: in expansion of macro 'pythonize'
   20 | pythonize(void, foo, ARGS(int x, int y), KWARGS(int a; int b)) {
      | ^~~~~~~~~
<source>:20:22: note: in expansion of macro 'ARGS'
   20 | pythonize(void, foo, ARGS(int x, int y), KWARGS(int a; int b)) {
      |                      ^~~~
<source>:25:14: error: too few arguments to function 'foo'
   25 |     pythonic(foo, 1)(.a = 1); // returns 42
      |              ^~~
<source>:14:5: note: in definition of macro 'pythonic'
   14 |     func_name (__VA_ARGS__ __VA_OPT__(,) (&(struct func_params_ ## func_name) { .sentinel_ = 0,  wrap_pythonic
      |     ^~~~~~~~~
<source>:20:17: note: declared here
   20 | pythonize(void, foo, ARGS(int x, int y), KWARGS(int a; int b)) {
      |                 ^~~
<source>:12:18: note: in definition of macro 'pythonize_II'
   12 |     function_ret function_name(__VA_ARGS__ __VA_OPT__(,) struct func_params_ ## function_name *args)
      |                  ^~~~~~~~~~~~~
<source>:5:62: note: in expansion of macro 'pythonize_I'
    5 | #define pythonize(function_ret, function_name, args, kwargs) pythonize_I(function_ret, function_name, kwargs, args)
      |                                                              ^~~~~~~~~~~
<source>:20:1: note: in expansion of macro 'pythonize'
   20 | pythonize(void, foo, ARGS(int x, int y), KWARGS(int a; int b)) {
      | ^~~~~~~~~ 
```
So save yourself the trouble and resist the temptation to make a macro to make anything similar to this. 

If you want to use this anyway, be my guest. Adding pragma to disable warnings around the code using pythonize can be a start.

# Contact Info
If you wish to inquire further about this code, contact me through discord.

Discord - `(traits*)sbrk(sizeof *traits)#1732` 