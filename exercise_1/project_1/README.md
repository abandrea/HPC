# High Performance Computing Project
By Andrea Buscema

MSc in Data Science and Artificial Intelligence (DSAI) 

University of Trieste

# Task 1: Compare different openMPI algorithms for collective operations

This is the exercise for Prof. Cozzini section of the 2023/2024 HPC course. The objective of this exercise is to compare and evaluate the performance of different openMPI algorithms for two different collective operations, `broadcast` that is the mandatory one, and one between `gather`, `scatter`, `barrier`, `reduce`. It is needed to estimate the latency of default openMPI implementation, varying the number of processes and the size of the messages exchanged and then compare this latter with the values obtained using different algorithms. For this task, it is needed to use a well-known MPI benchmark tool, like `osu-micro-benchmarks` and run them on at least two nodes of the ORFEO cluster, choosing among `epyc`, `thin` and `fat`, using all the available cores on a single node.

# Starting point

The starting point of this project is the `osu-micro-benchmarks` tool. The `osu-micro-benchmarks` tool is a set of micro-benchmarks that can be used to evaluate the performance of collective operations in MPI. The `osu-micro-benchmarks` tool provides benchmarks for a wide range of collective operations, including `broadcast`, `gather`, `scatter`, `barrier`, and `reduce`. The `osu-micro-benchmarks` tool can be used to measure the latency and bandwidth of collective operations for different message sizes and numbers of processes.

The `osu-micro-benchmarks` tool provides several algorithms for each collective operation, and the choice of algorithm can have a significant impact on the performance of the operation. The performance of collective operations can be affected by factors such as the size of the message, the number of processes, the network topology, and the communication pattern. Therefore, it is important to evaluate the performance of collective operations using different algorithms and to choose the best algorithm based on the specific requirements of the parallel program.

## Replication of the project

Since the ORFEO cluster is not available to everyone, this project will be represented considering the usage for most HPCC systems with same characteristics of the ORFEO cluster. 

* The OS of ORFEO is Linux, so the cluster shell is `bash`. As recommended by the ORFEO documentation, if you want a valid, complete overview, follow the first three lectures of the "[The Missing Semester of Your CS Education](https://missing.csail.mit.edu/)", a course provided by MIT.
* SLURM is the workload manager used in the ORFEO cluster, an open-source job scheduler and resource management system used in high-performance computing (HPC) environments. It allows users to submit and manage jobs on a cluster of computers, allocating resources such as CPU time, memory, and GPUs.
* LMOD is the module system used in the ORFEO cluster. It allows users to easily manage their environment by loading and unloading software packages and libraries. The module system is used to manage the software environment on the cluster, allowing users to easily switch between different versions of software packages and libraries.

# Download and Compile the OSU Benchmarks

Once accessed the server, in this case, the ORFEO cluster, it is needed to download the `osu-micro-benchmarks` tool from the official website. The `osu-micro-benchmarks` tool can be downloaded from the official website using the following command via wget (or directly from the [official page](https://mvapich.cse.ohio-state.edu/benchmarks/)):

```bash
wget https://mvapich.cse.ohio-state.edu/download/mvapich/osu-micro-benchmarks-7.3.tar.gz
```
then, it is needed to extract the downloaded file using the following command:

```bash
tar -xzvf osu-micro-benchmarks-7.3.tar.gz
```

**Before compiling** it is needed to load any necessary modules (e.g., `openmpi`, compilers), and then following the [compilation instructions](https://mvapich.cse.ohio-state.edu/static/media/mvapich/README-OMB.txt). To see the available modules, it is possible to use the command `module avail`, which will show all the available modules. To load a module, use the command `module load <module_name>`. For example, to load the `openmpi` module, use the command `module load openmpi`.

After loading the necessary modules, it is possible to compile the `osu-micro-benchmarks` tool using the following commands (inside the extracted folder):

```bash
./configure CC=mpicc CXX=mpicxx  # Ensure these are the MPI compilers
make
```








# Objectives

The main objectives of this project are:

1. Evaluate the performance of different openMPI algorithms for two different collective operations, `broadcast` and one between `gather`, `scatter`, `barrier`, `reduce`.
2. Estimate the latency of the default openMPI implementation for the two collective operations, varying the number of processes and the size of the messages exchanged.
3. Compare the performance of the default openMPI implementation with the performance of different algorithms for the two collective operations.
4. Analyze the performance of the collective operations using different algorithms and evaluate the impact of factors such as the size of the message, the number of processes, the network topology, and the communication pattern.
5. Choose the best algorithm for the two collective operations based on the specific requirements of the parallel program.





# Table of Contents
## 1.1. Broadcast

The first collective operation to be analyzed is the `broadcast`. The `broadcast` operation is a one-to-all communication operation that sends a message from the root process to all other processes in the communicator. The root process is the one that sends the message, while the other processes receive the message. The `broadcast` operation is a blocking operation, meaning that the root process will not continue executing until all other processes have received the message. The `broadcast` operation is commonly used in parallel computing to distribute data to all processes in a parallel program.

The `broadcast` operation is implemented in MPI using the `MPI_Bcast` function. The `MPI_Bcast` function takes three arguments: the buffer containing the message to be sent, the size of the message in bytes, and the rank of the root process. The `MPI_Bcast` function is called by all processes in the communicator, and the message is sent from the root process to all other processes.

The `broadcast` operation is a fundamental operation in parallel computing, and it is used in many parallel algorithms and applications. The performance of the `broadcast` operation can have a significant impact on the overall performance of a parallel program. Therefore, it is important to understand the performance characteristics of the `broadcast` operation and to choose the best algorithm for the `broadcast` operation based on the specific requirements of the parallel program.

## 1.2. Gather

The second collective operation to be analyzed is the `gather`. The `gather` operation is a many-to-one communication operation that collects data from all processes in the communicator and sends it to a single process. The `gather` operation is the inverse of the `scatter` operation, which sends data from a single process to all other processes. The `gather` operation is a blocking operation, meaning that all processes must participate in the operation, and the operation will not complete until all processes have sent their data.

The `gather` operation is implemented in MPI using the `MPI_Gather` function. The `MPI_Gather` function takes five arguments: the buffer containing the data to be sent, the size of the data in bytes, the data type of the data, the buffer where the data will be received, and the rank of the root process. The `MPI_Gather` function is called by all processes in the communicator, and the data is sent from all processes to the root process.

The `gather` operation is commonly used in parallel computing to collect data from all processes in a parallel program and combine it into a single data structure. The `gather` operation is used in many parallel algorithms and applications, and the performance of the `gather` operation can have a significant impact on the overall performance of a parallel program. Therefore, it is important to understand the performance characteristics of the `gather` operation and to choose the best algorithm for the `gather` operation based on the specific requirements of the parallel program.

## 1.3. Scatter

The third collective operation to be analyzed is the `scatter`. The `scatter` operation is a one-to-many communication operation that sends data from a single process to all other processes in the communicator. The `scatter` operation is the inverse of the `gather` operation, which collects data from all processes and sends it to a single process. The `scatter` operation is a blocking operation, meaning that all processes must participate in the operation, and the operation will not complete until all processes have received their data.

The `scatter` operation is implemented in MPI using the `MPI_Scatter` function. The `MPI_Scatter` function takes five arguments: the buffer containing the data to be sent, the size of the data in bytes, the data type of the data, the buffer where the data will be received, and the rank of the root process. The `MPI_Scatter` function is called by all processes in the communicator, and the data is sent from the root process to all other processes.

The `scatter` operation is commonly used in parallel computing to distribute data from a single process to all processes in a parallel program. The `scatter` operation is used in many parallel algorithms and applications, and the performance of the `scatter` operation can have a significant impact on the overall performance of a parallel program. Therefore, it is important to understand the performance characteristics of the `scatter` operation and to choose the best algorithm for the `scatter` operation based on the specific requirements of the parallel program.

## 1.4. Barrier

The fourth collective operation to be analyzed is the `barrier`. The `barrier` operation is a synchronization operation that blocks all processes in the communicator until all processes have reached the barrier. The `barrier` operation is a blocking operation, meaning that all processes must participate in the operation, and the operation will not complete until all processes have reached the barrier.

The `barrier` operation is implemented in MPI using the `MPI_Barrier` function. The `MPI_Barrier` function takes one argument: the communicator in which the barrier will be applied. The `MPI_Barrier` function is called by all processes in the communicator, and the operation will not complete until all processes have reached the barrier.

The `barrier` operation is commonly used in parallel computing to synchronize the execution of processes in a parallel program. The `barrier` operation is used to ensure that all processes have reached a certain point in the program before continuing execution. The `barrier` operation is used in many parallel algorithms and applications, and the performance of the `barrier` operation can have a significant impact on the overall performance of a parallel program. Therefore, it is important to understand the performance characteristics of the `barrier` operation and to choose the best algorithm for the `barrier` operation based on the specific requirements of the parallel program.

## 1.5. Reduce

The fifth collective operation to be analyzed is the `reduce`. The `reduce` operation is a many-to-one communication operation that combines data from all processes in the communicator into a single value. The `reduce` operation is the inverse of the `scatter` operation, which sends data from a single process to all other processes. The `reduce` operation is a blocking operation, meaning that all processes must participate in the operation, and the operation will not complete until all processes have sent their data.

The `reduce` operation is implemented in MPI using the `MPI_Reduce` function. The `MPI_Reduce` function takes five arguments: the buffer containing the data to be sent, the buffer where the result will be stored, the size of the data in bytes, the data type of the data, and the reduction operation to be applied. The `MPI_Reduce` function is called by all processes in the communicator, and the data is combined into a single value using the specified reduction operation.

The `reduce` operation is commonly used in parallel computing to combine data from all processes in a parallel program into a single value. The `reduce` operation is used in many parallel algorithms and applications, and the performance of the `reduce` operation can have a significant impact on the overall performance of a parallel program. Therefore, it is important to understand the performance characteristics of the `reduce` operation and to choose the best algorithm for the `reduce` operation based on the specific requirements of the parallel program.

## 1.6. Algorithms

The performance of collective operations in MPI can be significantly affected by the choice of algorithm used to implement the operation. MPI provides several algorithms for each collective operation, and the choice of algorithm can have a significant impact on the performance of the operation. The performance of collective operations can be affected by factors such as the size of the message, the number of processes, the network topology, and the communication pattern.

The performance of collective operations can be evaluated using a well-known MPI benchmark tool, such as `osu-micro-benchmarks`. The `osu-micro-benchmarks` tool provides a set of micro-benchmarks that can be used to evaluate the performance of collective operations in MPI. The `osu-micro-benchmarks` tool provides benchmarks for a wide range of collective operations, including `broadcast`, `gather`, `scatter`, `barrier`, and `reduce`. The `osu-micro-benchmarks` tool can be used to measure the latency and bandwidth of collective operations for different message sizes and numbers of processes.

The performance of collective operations can be evaluated using different algorithms provided by MPI. The performance of collective operations can be affected by factors such as the size of the message, the number of processes, the network topology, and the communication pattern. Therefore, it is important to evaluate the performance of collective operations using different algorithms and to choose the best algorithm based on the specific requirements of the parallel program.

