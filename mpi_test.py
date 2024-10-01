#
#   UV-VIS FHIaims analyser
#
#   07.2024 WKJEE
#
from mpi4py import MPI

#
# MPI extension
#
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

print(rank)
