# C 程式的品質

## 正確性 -- test

1. gcc 可加上 -Wall 參數，嚴格檢查語法 (Warning Alll)
2. 可用 valgrind 檢查記憶體相關問題 (存取超過，有分配沒釋放...)。
3. 用 assert 防護
4. 單元測試
5. 使用 gprof 了解效能狀況 ...


## 速度

* [Optimization of Computer Programs in C](http://icps.u-strasbg.fr/~bastoul/local_copies/lee.html) (超讚!)

```
1. Introduction
2. Compute-bound
    Choose a Better Algorithm
    Write Clear, Simple Code
    Perspective
    Understand your Compiler Options
    Inlining
    Loop Unrolling
    Loop Jamming
    Loop Inversion
    Strength Reduction
    Loop Invariant Computations
    Code for Common Case
    Tail Recursion Elimination
    Table Lookup
    Sorting
    Variables
    Function Calls
    Digestibility
    String Operations
    FP Parallelism
    Get a Better Compiler
    Stack Usage
    Code it in Assembly
    Shared Library Overhead
    Machine-Specific Optimization
Memory-bound
    Locality of Reference
    Column-major Accessing
    Don't Copy Large Things
    Split or Merge Arrays
    Reduce Padding
    Increase Padding
    March Forward
    Beware the Power of Two
    Memory Leaks
    Be Stringy
    Hinting
    Fix the Problem in Hardware
    Cache Profilers
IO-bound
    Sequential Access
    Random Access
    Terminals
    Sockets
    SFIO
```

* [Wikibook: Optimizing C++](https://en.wikibooks.org/wiki/Optimizing_C%2B%2B) (讚，完整！)

* [Tips for Optimizing C/C++ Code (PDF)](https://people.cs.clemson.edu/~dhouse/courses/405/papers/optimize.pdf)

1. Remember Ahmdal’s Law: 
2. Code for correctness first, then optimize!
3. People I know who write very efficient code say they spend at least twice as long optimizing code as they spend
writing code.
4. Jumps/branches are expensive. Minimize their use whenever possible.
5. Think about the order of array indices.
6. Think about instruction-level-parallelism
7. Avoid/reduce the number of local variables.
8. Reduce the number of function parameters.
9. Pass structures by reference, not by value.
10. If you do not need a return value from a function, do not define one.
11. Try to avoid casting where possible
12. Be very careful when declaring C++ object variables.
13. Make default class constructors as lightweight as possible.
14. Use shift operations >> and << instead of integer multiplication and division, where possible
15. Be careful using table-lookup functions.
16. For most classes, use the operators += , -= , *= , and /= , instead of the operators + , - , * , and /
17. For basic data types, use the operators + , - , * , and / instead of the operators += , -= , *= , and /= .
18. Delay declaring local variables
19. For objects, use the prefix operator (++obj) instead of the postfix operator (obj++).
20. Be careful using templates.
21. Avoid dynamic memory allocation during computation
22. Find and utilize information about your system’s memory cache
23. Avoid unnecessary data initialization
24. Try to early loop termination and early function returns
25. Simplify your equations on paper!
26. The difference between math on integers, fixed points, 32-bit floats, and 64-bit doubles is not as big as you might think.
27. Consider ways of rephrasing your math to eliminate expensive operations.

我的補充 (C 語言)

1. 注意區域性 (ex: 索引順序 for i for j ...)
2. 使用 inline
3. 注意 word 大小與 align 問題
4. 減少跳躍
5. 減少乘除法，盡量用移位
6. 迴圈不變量提出到外面
7. 減少 I/O 與讀寫頭移動次數 (緩衝 ...)
8. 減少 malloc 後又釋放的次數，採用一次性大區塊。


* [Cheap trick to speed up recursion in C++](https://wordsandbuttons.online/cheap_trick_to_speed_up_recursion_in_cpp.html)

* [PROGRAMMING IN C -- C FOR SPEED! Techniques To Transform Your Turtle Code BY JOHN ALLEN](https://www.atarimagazines.com/startv5n6/c_for_speed.html)

* [Writing Efficient C and C Code Optimization](https://www.codeproject.com/Articles/6154/Writing-Efficient-C-and-C-Code-Optimization)





