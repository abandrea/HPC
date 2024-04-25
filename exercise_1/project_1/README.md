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
$ ./configure CC=mpicc CXX=mpicxx  # Ensure these are the MPI compilers
$ make
```
In order to don't repeat the same commands every time, it is possible to create a script that loads the necessary modules automatically. What was done in my case was to create a script called `.bashrc`:

```bash
$ echo "module load openMPI/4.1.5/gnu/12.2.1" >> ~/.bashrc
```
in which the `openMPI` module it can be loaded with this command:

```bash
$ source ~/.bashrc
```

From here, it is possible to go on with the execution of the benchmarks.

# Execution of the Benchmarks

The `osu-micro-benchmarks` tool provides several benchmarks for different collective operations, including `broadcast`, `gather`, `scatter`, `barrier`, and `reduce`. The performance of collective operations can be evaluated using different algorithms provided by MPI. The performance of collective operations can be affected by factors such as the size of the message, the number of processes, the network topology, and the communication pattern. Therefore, it is important to evaluate the performance of collective operations using different algorithms and to choose the best algorithm based on the specific requirements of the parallel program.

The `osu-micro-benchmarks` tool provides several options to control the execution of the benchmarks, including the number of processes, the size of the message, and the algorithm used for the collective operation. The `osu-micro-benchmarks` tool can be used to measure the latency and bandwidth of collective operations for different message sizes and numbers of processes.

## Broadcast Benchmark

The `broadcast` benchmark measures the performance of the `broadcast` operation in MPI. The `broadcast` operation is a one-to-all communication operation that sends a message from the root process to all other processes in the communicator. The `broadcast` benchmark measures the latency and bandwidth of the `broadcast` operation for different message sizes and numbers of processes.

The `broadcast` benchmark can be executed using the following command:

```bash
$ mpirun -np <num_processes> osu_bcast
```

## Reduce Benchmark

The `reduce` benchmark measures the performance of the `reduce` operation in MPI. The `reduce` operation is a many-to-one communication operation that combines data from all processes in the communicator into a single value. The `reduce` benchmark measures the latency and bandwidth of the `reduce` operation for different message sizes and numbers of processes.

The `reduce` benchmark can be executed using the following command:

```bash
$ mpirun -np <num_processes> osu_reduce
```

For this project, it will be tested broadcast and reduce. For both, will be tested the latency and bandwidth of the default openMPI implementation, varying the number of processes and the size of the messages exchanged. Then, it will be compared with the values obtained using different algorithms, using 1 (basic_linear), 2 (chain) and 3 (pipeline) algorithms.

### 1. Basic Linear

The `basic_linear` algorithm is a simple algorithm that sends the message from the root process to all other processes in a linear fashion. The `basic_linear` algorithm is a straightforward algorithm that sends the message from the root process to all other processes one by one. The `basic_linear` algorithm is a simple algorithm that is easy to implement and understand.

### 2. Chain

The `chain` algorithm is a more complex algorithm that sends the message from the root process to all other processes in a chain fashion. The `chain` algorithm is a more complex algorithm that sends the message from the root process to all other processes in a chain fashion. The `chain` algorithm is a more complex algorithm that is more efficient than the `basic_linear` algorithm.

### 3. Pipeline

The `pipeline` algorithm is a more complex algorithm that sends the message from the root process to all other processes in a pipeline fashion. The `pipeline` algorithm is a more complex algorithm that sends the message from the root process to all other processes in a pipeline fashion. The `pipeline` algorithm is a more complex algorithm that is more efficient than the `chain` algorithm.

# Execution of the Benchmarks in a HPC Cluster

For the execution of the benchmarks, it is needed to use the `mpirun` command, which is used to launch MPI applications. The `mpirun` command takes several arguments, including the number of processes, the name of the executable, and any additional arguments that need to be passed to the executable. The `mpirun` command is used to launch MPI applications on a cluster of computers, distributing the processes across the available nodes.

The parameters for this project are the following:

* Number of processes: 2, 4, 8, 16, 32, 64, 128, 256 (powers of 2)
* Message size: 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576

Number of processes will be tested from 2 to 256 (powers of 2), while the message size will be tested from 2 bytes to 1 MB. The benchmarks will be executed using the default openMPI implementation and the `basic_linear`, `chain`, and `pipeline` algorithms for the `broadcast` and `reduce` operations.

The execution of the benchmarks can be done using the following commands:

```bash
$ mpirun -np <num_processes> osu_bcast -m <message_size> -a 1
$ mpirun -np <num_processes> osu_bcast -m <message_size> -a 2
$ mpirun -np <num_processes> osu_bcast -m <message_size> -a 3

$ mpirun -np <num_processes> osu_reduce -m <message_size> -a 1
$ mpirun -np <num_processes> osu_reduce -m <message_size> -a 2
$ mpirun -np <num_processes> osu_reduce -m <message_size> -a 3
```

# Execution of the Benchmarks in the ORFEO Cluster

Since in the ORFEO cluster I don't have the priority, it is important to check and verify every parameters in order to not waste resources and doing the job in the right way. The ORFEO cluster is a shared resource, and it is important to be considerate of other users. 

### 1. Checking Partitions and Nodes Availability

This first check can be done using the command `sinfo` that shows the status of the partitions and nodes in the cluster, including the number of nodes available, the number of nodes in use, and the number of nodes down. 

During the project, the only available partitions were `THIN` and `FAT`. 

|**THIN Nodes** | **FAT Nodes** |
|---------------|---------------|
|10 nodes       | 2 nodes       |
|768 GB of RAM  | 1536 GB of RAM|
|24 cores       | 36 cores      |
|1.997 Tflops   | 3.456 Tflops  |

### 2. Job Duration Estimation

It is important to consider a few factors :
1. Benchmarking Time: How long doeas a single run of the benchmark take? So, it should be run a preliminary test to get this basic timing information. 
2. Repetitions: How many times will repeat each benchmark to ensure accurate results? We'll want multiple runs to average out any variability.
3. Algotirhms and Message Size: If we are testing different algorithms and message sizes, we need to account for the time it takes to test each variation.
4. Data Collection and Analysis Overhead: Consider the time needed to gather results and perfom any on-the-fly analysis or data storage operations.
5. Buffer Time: Always add some extra time as a buffer to account for enexpected delays, such as the job starting a bit late due to system load or other minor issues. 






<!-- It is important to estimate the duration of the job in order to not waste resources. The duration of the job can be estimated using the following formula:

```bash
estimated-time-for-job = (number-of-processes * message-size) / bandwidth
``` -->





THIN

```bash
#!/bin/bash
#SBATCH --job-name=bcast-benchmark
#SBATCH --output=bcast_output_%j.txt
#SBATCH --error=bcast_error_%j.txt
#SBATCH --partition=THIN
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=24
#SBATCH --time=<estimated-time-for-job>
#SBATCH --exclusive

# Load the necessary modules
module load openmpi

# Add your benchmark commands here
```

FAT

```bash
#!/bin/bash
#SBATCH --job-name=bcast-benchmark
#SBATCH --output=bcast_output_%j.txt
#SBATCH --error=bcast_error_%j.txt
#SBATCH --partition=THIN
#SBATCH --constraint=FAT
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=36
#SBATCH --time=<estimated-time-for-job>
#SBATCH --exclusive

# Load the necessary modules
module load openmpi

# Add your benchmark commands here
```

