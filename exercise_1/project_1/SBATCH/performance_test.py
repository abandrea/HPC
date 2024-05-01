from mpi4py import MPI
import numpy as np
import time

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

# Create a numpy array of size 1M elements
data = np.random.rand(1000000) if rank == 0 else None

# Start timer
start_time = time.time()

# Broadcast data
comm.Bcast(data, root=0)

# End timer
end_time = time.time()

# Measure time taken for the broadcast
if rank == 0:
    print(f"Broadcast time for {size} processes: {end_time - start_time:.6f} seconds")
