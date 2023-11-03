# source
# GetIntegerDouble.c  
# GetReturnString.c
# PassTwoIntRetSum.c
# SimpleCall.c

# Python.h header + library link
cc -std=c11 -O3 -o GetIntegerDouble.x GetIntegerDouble.c -I /work/e05/e05/wkjee/miniconda3/include/python3.11/ -L /work/e05/e05/wkjee/miniconda3/lib/ -lpython3.11
cc -std=c11 -O3 -o GetReturnString.x GetReturnString.c   -I /work/e05/e05/wkjee/miniconda3/include/python3.11/ -L /work/e05/e05/wkjee/miniconda3/lib/ -lpython3.11
cc -std=c11 -O3 -o PassTwoIntRetSum.x PassTwoIntRetSum.c -I /work/e05/e05/wkjee/miniconda3/include/python3.11/ -L /work/e05/e05/wkjee/miniconda3/lib/ -lpython3.11
cc -std=c11 -O3 -o SimpleCall.x SimpleCall.c             -I /work/e05/e05/wkjee/miniconda3/include/python3.11/ -L /work/e05/e05/wkjee/miniconda3/lib/ -lpython3.11
cc -std=c11 -O3 -o CallClassMethod.x CallClassMethod.c   -I /work/e05/e05/wkjee/miniconda3/include/python3.11/ -L /work/e05/e05/wkjee/miniconda3/lib/ -lpython3.11
# set python library path : put this in .bashrc
# export LD_LIBRARY_PATH=/work/e05/e05/wkjee/miniconda3/lib/:$LD_LIBRARY_PATH
# setting python module path
export PYTHONPATH=$PYTHONPATH:/work/e05/e05/wkjee/Software/gulpklmc/CPython
