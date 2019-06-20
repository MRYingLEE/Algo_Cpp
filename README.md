# Algo_Cpp
Some ideas, code snippets about Algorithm design and implementation, especially for C++. The primary topics include automatic memorization.

# Automatic memorization

## Objectives: 
  Competative Oriented. This is not a general automatic memorization solution or framework. Instead this is for rush coding. 
  
  Technically, the following functions are supported:
    T<unsigned int> int_1d;
    T<unsigned int, unsigned int> int_2d;
    T<unsigned int, unsigned int> int_3d;
  
  1. The syntax should be simple, compatiable to C++ 11. 
  
  2. The recursive function code is not needed to be modified.
  
  3. The speed is the top priority.
    
  4. Best practice usage demo is provided.
  
## Logical

1. Vanilar version: corresponding vectors will be used to store function values.

2. Rolling version: An anvanced vector with rolling window and assigned offset will be used to store.
  This is to save the space. Just in case.

3. We use functors to extend the original recursive function code.

## Usage in rush coding

1. Write your recursive function code, which is intuitive.

  Make sure your function is immutable. In other words, the same parameters always return the same value;
  Put all non integer parameters as global variables.
  
2. After successful running, copy the code snippet AFTER your recursive function.

3. Change slightly the functor variable declare section if needed.

