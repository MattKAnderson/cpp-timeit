# cpp-timeit

A CPP header only template library for timing the execution of functions with arbitrary parameters

# Usage

The library can be fetched or installed with CMake, or the include/timeit.hpp file can be copied to your include folder. 

E.x. fetch command with CMake
```cmake
# In CMakeLists.txt
FetchContent_Declare(
    cpp-timeit
    GIT_REPOSITORY https://github.com/MattKAnderson/cpp-timeit
    GIT_TAG main
)
FetchContent_MakeAvailable(cpp-timeit)

# link the library to your target
target_link_library(my_target timeit::timeit)

# then include the header with #include <timeit.hpp>
```

# Examples

With the `sample` function you can take a single measurement of the function execution time. The method returns the time in milliseconds as a double. 

```cpp
// signature for function in example
double some_operation(std::vector<double>& values, double A, int B);

// arguments
std::vector<double> some_vector = something;
double A = 29.123;
int B = 3;

double execution_time = timeit::sample(some_operation, some_vector, A, B);
```

The arguments and return type are arbitrary

```cpp
// signature for function in example
std::vector<int> some_vector_operation(std::vector<int>& vecA, std::vector<int>& vecB);

// arguments
std::vector<int> a_vector = something;
std::vector<int> another_vector = something_else;

double execution_time = timeit::sample(some_vector_operation, a_vector, another_vector);
```

The `print` function is similar to the `sample` function except it prints the elapsed time rather than return it.

```cpp
// arguments
std::vector<int> a_long_vector = something;

timeit::print(std::sort, a_long_vector.begin(), a_long_vector.end());

/*
 *   >> Elapsed time: 0.305 s
 */ 
```

The `stats` function will execute the function the specified number of times and return execution statistics in a std::unordered_map<string, double>

```cpp
// signature for function in example
double some_operation(std::vector<double>& values, double A, int B);

// arguments
std::vector<double> some_vector = something;
double A = 29.123;
int B = 3;
int nsamples = 100

std::unordered_map<string, double> stats = timeit::stats(nsamples, some_operation, some_vector, A, B);

/*
 *   Possible output:
 *
 *     {"n_samples": 100, "max": 0.321, "min": 0.288, "mean": 0.301, "center": 0.309}
 *
 */
```


