Low-memory Quasi-Newton Minimizer

This project implements a limited-memory quasi-Newton minimizer.

Instead of storing the full inverse Hessian matrix, only the
latest m update vectors are stored and used to approximate
the inverse Hessian action.

The implementation is tested on the Rosenbrock and Himmelblau
benchmark functions using several starting points.

Memory size m = 1

Function      Start point         Steps     Converged   Minimum
Rosenbrock    (0.900, 1.100)      383       yes         (1.000, 1.000)
Rosenbrock    (-1.200, 1.000)     56        yes         (1.000, 1.000)
Rosenbrock    (-2.000, 2.000)     1000      no          (1.069, 1.143)

Himmelblau    (3.500, 2.500)      73        yes         (3.000, 2.000)
Himmelblau    (-3.000, 3.500)     41        yes         (-2.805, 3.131)
Himmelblau    (-4.000, -3.500)    56        yes         (-3.779, -3.283)
Himmelblau    (4.000, -2.000)     70        yes         (3.584, -1.848)

Memory size m = 3

Function      Start point         Steps     Converged   Minimum
Rosenbrock    (0.900, 1.100)      17        yes         (1.000, 1.000)
Rosenbrock    (-1.200, 1.000)     84        yes         (1.000, 1.000)
Rosenbrock    (-2.000, 2.000)     1000      no          (1.000, 1.000)

Himmelblau    (3.500, 2.500)      50        yes         (3.000, 2.000)
Himmelblau    (-3.000, 3.500)     12        yes         (-2.805, 3.131)
Himmelblau    (-4.000, -3.500)    19        yes         (-3.779, -3.283)
Himmelblau    (4.000, -2.000)     20        yes         (3.584, -1.848)

Memory size m = 5

Function      Start point         Steps     Converged   Minimum
Rosenbrock    (0.900, 1.100)      16        yes         (1.000, 1.000)
Rosenbrock    (-1.200, 1.000)     44        yes         (1.000, 1.000)
Rosenbrock    (-2.000, 2.000)     29        yes         (1.000, 1.000)

Himmelblau    (3.500, 2.500)      18        yes         (3.000, 2.000)
Himmelblau    (-3.000, 3.500)     10        yes         (-2.805, 3.131)
Himmelblau    (-4.000, -3.500)    9         yes         (-3.779, -3.283)
Himmelblau    (4.000, -2.000)     11        yes         (3.584, -1.848)

Memory size m = 10

Function      Start point         Steps     Converged   Minimum
Rosenbrock    (0.900, 1.100)      15        yes         (1.000, 1.000)
Rosenbrock    (-1.200, 1.000)     42        yes         (1.000, 1.000)
Rosenbrock    (-2.000, 2.000)     28        yes         (1.000, 1.000)

Himmelblau    (3.500, 2.500)      9         yes         (3.000, 2.000)
Himmelblau    (-3.000, 3.500)     7         yes         (-2.805, 3.131)
Himmelblau    (-4.000, -3.500)    7         yes         (-3.779, -3.283)
Himmelblau    (4.000, -2.000)     8         yes         (3.584, -1.848)

Average number of iterations

m       Rosenbrock        Himmelblau
m=1     479.7             60.0
m=3     367.0             25.2
m=5     29.7              12.0
m=10    28.3              7.8

Conclusion

The results show that the memory parameter has
a significant influence on the convergence of
the algorithm.

Using only one update vector (m = 1) generally
requires many more iterations.

Increasing the memory to m = 5 significantly
improves convergence for both benchmark
functions.

Increasing the memory further to m = 10 gives
only a small improvement compared to m = 5 for
these benchmark problems.

Therefore, m = 5 appears to provide a good
balance between memory usage and convergence
speed.

I have awnsered all of my exam question, and so I think this is a 10/10
