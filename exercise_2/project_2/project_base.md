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



## Conclusion

1. **Computational Efficiency**:
    - OpenMP: Shows a significant improvement in execution time with the initial increase in the number of threads, but quickly reaches a saturation point. Efficiency decreases when the number of threads exceeds the number of physical cores, suggesting scalability limitations due to hardware resource saturation and context management.
    - MPI: Efficiency increases up to a certain point with the addition of processes, but shows peaks of inefficiency at certain levels of parallelisation, especially at 24 processes. This is indicative of significant overhead in handling communication and synchronisation between distributed processes.

2. **Bottlenecks**:
    - OpenMP: The main bottlenecks are related to memory management and synchronisation between threads, with a significant drop in major page faults and a stabilisation in unintentional context switches as threads increase.
    - MPI: Shows increases in major page faults and unintentional context switches with the addition of processes, indicating pressures on memory and inefficiencies in CPU scheduling due to more complex management of context and inter-process communication.

3. **Parallelisation Impact**:
    - OpenMP: The effective CPU utilisation increases with the addition of threads, but the execution time stabilises, indicating that beyond a certain number of threads, the addition of further threads does not bring significant benefits.
    - MPI: CPU utilisation improves almost linearly with increasing number of processes, but execution time shows peaks of inefficiency, suggesting that resource management and communication between processes may become problematic with a high number of processes.

General considerations:

- **Scalability**: OpenMP is generally more effective in improving execution time up to a certain number of cores on a single node, while MPI scales better on distributed systems, albeit with a higher communication overhead.
- **Simplicity of Implementation**: OpenMP tends to be simpler to implement for parallelism on a single node, whereas MPI requires more complex management but is essential for computation on multiple nodes.
- **Resource Utilisation**: OpenMP may suffer from scalability problems related to resource saturation of a single node, such as memory and CPU bandwidth. MPI, on the other hand, can exploit resources of multiple nodes but requires efficient management of communication and synchronisation to minimise overhead.

In the context of parallel computing, strong scalability and weak scalability analyses provide crucial metrics for evaluating the effectiveness of parallelisation methods such as OpenMP and MPI. Understanding how these two approaches handle scalability can help to outline optimal strategies for their use. Here is an overview of both types of scalability and how OpenMP and MPI perform in each scenario:

### Strong Scalability

- Definition: Strong scalability occurs when the total problem remains constant while the number of processors (or threads) increases. In this scenario, the focus is on reducing the execution time while keeping the problem size unchanged.
- OpenMP: Generally shows good strong scalability until the number of threads exceeds the number of physical cores. Beyond this point, efficiency may decrease due to thread management overhead and competition for limited hardware resources, as shown by the data with a plateau in execution time.
- MPI: Strong scalability may be more complex to achieve due to the overhead introduced by communication between processes, especially on multiple nodes. However, MPI can effectively handle strong scalability on larger distributed systems if communication is optimised and data is distributed equally.

### Weak Scalability

- Definition: Weak scalability occurs when the problem size per processor (or thread) remains constant while the total number of processors increases. The goal is to keep the execution time constant while the total problem size increases.
- OpenMP: Can handle weak scalability well up to a certain point, especially on machines with a large number of cores. However, problems such as memory and bandwidth saturation can become limiting when the problem per thread becomes too large.
- MPI: It is often better suited for weak scaling on a large scale due to its ability to distribute the workload over a large number of processes and nodes. The challenge remains in optimising problem partitioning and communication to maintain a uniform execution time.

### Practical Implications

**OpenMP**:

- Good for problems that can be decomposed into work units that can be handled efficiently on a single node.
- Less effective when the number of threads exceeds the number of available cores due to scheduling overhead and competition for resources.

**MPI**:

- Scalable on distributed architectures, ideal for problems requiring large amounts of distributed computing and data.
- Requires attention to data decomposition and algorithm design to minimise communication and maximise efficiency.

### Optimal Strategies

- For OpenMP, the optimal strategy is to limit the number of threads to the number of physical cores and exploit data locality to maximise cache efficiency.
- For MPI, it is essential to optimise workload distribution and communication, using techniques such as dynamic load balancing and efficient data decomposition algorithms.

The choice between OpenMP and MPI should be based on the nature of the problem, the topology of the available computing system, and the specific performance and scalability goals. While OpenMP is ideal for optimisation and efficiency on a single node with multi-threading, MPI is indispensable for applications that need to scale across multiple nodes, despite the additional cost in terms of communication management.