# High Performance Computing Project
By Andrea Buscema

MSc in Data Science and Artificial Intelligence (DSAI) 

University of Trieste

# Task 1: Compare different openMPI algorithms for collective operations

This is the first assignment for Prof. Cozzini section of the 2023/2024 HPC course. The objective of this exercise is to compare and evaluate the performance of different openMPI algorithms for two different collective operations, `broadcast` that is the mandatory one, and one between `gather`, `scatter`, `barrier`, `reduce`. It is needed to estimate the latency of default openMPI implementation, varying the number of processes and the size of the messages exchanged and then compare this latter with the values obtained using different algorithms. For this task, it is needed to use a well-known MPI benchmark tool, like `osu-micro-benchmarks` and run them on at least two nodes of the ORFEO cluster, choosing among `EPYC`, `THIN` and `FAT`, using all the available cores on a single node.


# Task 2: Mandelbrot Set using hydrid implementation MPI + OpenMP

This is the second assignment for Prof. Tornatore section of the 2023/2024 HPC course. The objective of this exercise is to implement a parallel version of the Mandelbrot Set using a hybrid approach, combining MPI and OpenMP. The goal is to parallelize the computation of the Mandelbrot Set using MPI to distribute the work among different processes and OpenMP to exploit the parallelism within each process. The implementation should be able to generate the Mandelbrot Set for a given range of complex numbers and produce an image representing the set. The performance of the parallel implementation should be evaluated by measuring the execution time for different numbers of processes and threads, and comparing it with the sequential version. The implementation should be tested on the ORFEO cluster using multiple nodes and cores to assess its scalability and efficiency.

--------------

## Things to know

### What is ORFEO Cluster?

ORFEO (Open Research Facility for Epigenomics and Other) is a modern data center hosted in a container within the AREA Science Park, in Trieste (Italy) (https://orfeo-doc.areasciencepark.it/). ORFEO is a high-performance computing system designed to offer over 14 million calculation hours annually. If features advanced hardare including eight NVIDIA Tesla V100 GPUs and two NVIDIA DGX systems, each equipped with eight NVIDIA A100 GPUs and 1 TiB of RAM, facilitating cutting-edge AI performance for both inference and training tasks.

This computational resource is accessible to students, startups, and researchers from partner institutions, primarily in Life Sciences and Innovative Materials fields. 

### What is MPI?
MPI, Message Passing Interface, is a standardized and portable system for programming parallel computers. It allows for efficient communication across different computing architectures, making it crucial for high-performance computing (HPC). MPI supports both individual and collective communication between processors, is scalable, and can handle extensive data operations. It's widely used in computational sciences for tasks that require significant computational resources, such as simulations in physics, chemistry, genomics, and more.

### What is openMPI?
OpenMPI is an open-source implementation of the MPI standard. It provides a powerful and flexible platform for parallel computing, enabling users to develop and run parallel applications efficiently. OpenMPI supports various programming languages, including C, C++, and Fortran, making it accessible to a broad range of developers and researchers. It's widely used in scientific computing, data analysis, and other fields that require high-performance computing capabilities.
