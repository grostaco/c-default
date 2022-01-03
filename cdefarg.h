#define ARG(x) x
#define KWARG(x) args->x
#define pythonize(function_ret, function_name, args, kwargs) pythonize_I(function_ret, function_name, kwargs, args)
#define pythonize_I(function_ret, function_name, kwargs, ...) pythonize_II(function_ret, function_name, kwargs, __VA_ARGS__)
#define pythonize_II(function_ret, function_name, kwargs, ...) \
    struct func_params_ ## function_name {      \
        int sentinel_;                       \
        kwargs;                              \
    };                                       \
    function_ret function_name(__VA_ARGS__ __VA_OPT__(,) struct func_params_ ## function_name *args) 
#define pythonic(func_name, ...) \
    func_name (__VA_ARGS__ __VA_OPT__(,) (&(struct func_params_ ## func_name) { .sentinel_ = 0,  wrap_pythonic
#define wrap_pythonic(...) __VA_ARGS__ }))

#define ARGS(...) __VA_ARGS__
#define KWARGS(...) __VA_ARGS__