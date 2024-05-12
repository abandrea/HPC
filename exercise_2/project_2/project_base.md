# HPC - Exercise 2 (2c) - Mandelbrot set using MPI+OpenMP (Project 2)

## Description

The aim of this project is to implement a parallel version of the Mandelbrot set using MPI and OpenMP. The program generates an image of the Mandelbrot set and saves it to a file. The program is parallelized using MPI and OpenMP. The MPI processes are used to divide the image into horizontal strips, which are then processed in parallel using OpenMP threads.

## Project Breakdown

### 1. Understanding the Mandelbrot Set Calculation

- For each point $c=x+iy$ in the specified complex plane, determine whether $c$ belongs to the Mandelbrot set $\mathcal{M}$ by iterating:
$$f_c(z) = z^2 + c$$ 
$\space$ starting with $z_0 = 0$ up to a maximum number of iterations $I_{max}$.

- A point $c$ is in the Mandelbrot set if the absolute value $|z_n|$ doesn not exceed 2 for all iterations up to $I_{max}$.

### 2. Parameter Handling and Grid Setup

- Read and handle command line arguments to set the grid dimensions, region of interest in the complex plane, and maximum iterations. 

- Compute $\Delta x$ and $\Delta y$ to map pixel indices to the complex plane coordinates.

### 3. Data Structure

- Initialize a 2D array (matrix `M`) where each element corresponds to a pixel. The type of elements in `M` can be `char` (for $I_{max} \leq 255$) or `short int` (for larger $I_{max}$, up to 65535). 

### 4. Parallel Computation Using MPI + OpenMP

- **MPI Setup**: Split the computation domain among MPI processes, each handling a subset of the complex grid.
- **OpenMP Setup**: Within each MPI process, use OpenMP threads to parallelize the claculation across the subset of points assigned to that process.
- Inizialize MPI with `MPI_Init_threads` to ensure compatibility between MPI and OpenMP.

### 5. I/O Operations 

- Perform strong and weak scaling tests to evaluate:
    - **OMP scaling**: Increasing number of OpenMP threads under a single MPI process.
    - **MPI scaling**: Increasing number of MPI processes, preferably across multiple nodes, with one OpenMP thread per process.

### 6. Implementation of PGM File 

To integrate the `.pgm` file writing into MPI+OpenMP code, it is necessary to create a function that will handle writing the output matrix `M` to a PGM file in a binary format, which is more efficient than the ASCII format.

______

# Step 1: Basic Mandelbrot Set Computation

Function in C to compute whether a point belongs to the Mandelbrot set. 

- Complex Number Operations: Recall that the Madelbrot set computation involves complex number arithmetic, particularly squaring complex numbers and adding them. In C, will be managed by representig a complex number $c = x + iy$ using two doubles for the real (x) and imaginary (y) parts.
- Iterative Calculation: For each point $c$ on the complex plane, iterate the function $f_c(z) = z^2 + c$, starting with $z = 0$, until either the magnitude of $z$ exceeds 2 (indicating the sequence will diverge) or a maximum number of iterations in reached.
**Desiderable functions**

- Complex Number Calculation: The Mandelbrot function computes $z$ for each iteration from 0 to `max_iter` or unitl $|z|$ exceeds 2 (for example, $|z|^2 > 4$).
- Output: Depending on the iteration count when the loop exits, we know if the point $c$ might be in the Mandelbrot set (if it reaches `max_iter` without exceeding the magnitude conditions).

> **Note 1**: Mandelbrot set lives roughly in the circular region centered on $(-0.75, 0)$ with a radius of $\sim 2$.

> **Note 2:** the multiplication of 2 complex numbers is defined as $(x_1 + iy_1)\,\times\,(x_2+iy_2) = (x_1x_2 - y_1y_2) + i(x_1y_2+x_2y_1)$

With those notes in mind, we can expand basic Mandelbrot set computation to more accurately explore regions within the Mandelbrot set and potentially implement functionality that considers complex number multiplication.

### Expanding the Calculation to a Grid

Since the Mandelbrot set resides within a circle centered around $(-0.75, 0)$ with a radius of $\sim 2$, we can set our program to generate a grid of points around this region to visualize the set. To do this efficiently and effectively, it is possible to start by computing a range of points that covers this area.

**Implementation steps**:
1. Setup a grid: Defining a grid of complex nubers centered around $(-0.75, 0)$ with a radius of $\sim 2$.
2. Iterating over each point: For each point on this grid, it is possible to determine whether it belongs to the Mandelbrot set using the iterative method.

For the first test, it was implemented a simple script where the program writes the output to a file in txt format, in ASCII mode. 

## Test 1

Compiling the program with the following command:
```bash
gcc -o mandelbrot_local mandelbrot_test_local.c -lm
```

and then running it:
```bash
./mandelbrot_local
```

The output file `mandelbrot_output.txt` will contain a textual representation of the Mandelbrot set data in ASCII format.Each line in the file corresponds to a row of pixels, where '.' represents points within the Mandelbrot set, and ' ' (space) represents points outside the set.

![Mandelbrot test_1](figures/test_1.png)

## Test 2

Since the first test was successful, it is possible to move on and implement the script and replace the ASCII output with a binary PGM file format.

![Mandelbrot test_2](figures/test_2.png)

# Step 2: Parallelizing the Mandelbrot Set Calculation

The next step is to parallelize the Mandelbrot set computation using MPI and OpenMP, aiming for a hybrid approach to efficiently leverage multiple processors and cores. 

To use MPI (Message Passing Interface), we need to include MPI functions in the script and initialize MPI in the program. This will allow us to run across multiple processes, which may be distributed across different nodes in a cluster.

OpenMP will be used for shared-memory parallelism within each MPI process. This will allows each process to further split its workload among multiple threas, making effective use of multi-core architectures.

We will also need to divide the problem so that each MPI process is responsible for a specific part of the image. This involves splitting the image grid into segments (typically horizontal stripes) that each process will compute.

Each MPI process will use OpenMP to parallelize the within its segment, spreading the work across multiple threads. 

Then, one all processes have completed their computations, the results need to be gathered and assembled into the final PGM image. This can be handled in various ways, including using MPI I/O to write directly to the file in parallel.

Since the project requires the creation of a hybrid script, we could start by integrating MPI to handle calculation on multiple nodes. After establishing a working MPI base, we can add OpenMP to further optimise the calculations within each node.

## MPI integration

The MPI integration allows the calculation to be distributed over several nodes in the cluster. Each node will calculate a part of the final image.

