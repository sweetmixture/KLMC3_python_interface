#!/bin/bash

# wkjee - manual compilation test 
cc -std=c11 -O3 -c call_py.c -I /work/e05/e05/wkjee/miniconda3/include/python3.11/ -I /work/e05/e05/wkjee/Software/gulpklmc/klmc3_tf_interface.update.12092023/KLMC3.112023/python_interface/include
cc -std=c11 -O3 -c /work/e05/e05/wkjee/Software/gulpklmc/klmc3_tf_interface.update.12092023/KLMC3.112023/python_interface/call_python_serial.c -I /work/e05/e05/wkjee/miniconda3/include/python3.11/
cc -std=c11 -O3 -o m.x call_python_serial.o call_py.o -L /work/e05/e05/wkjee/miniconda3/lib/ -lpython3.11
