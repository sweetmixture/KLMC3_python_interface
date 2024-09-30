# source
# GetIntegerDouble.c  
# GetReturnString.c
# PassTwoIntRetSum.c
# SimpleCall.c

# Python.h header + library link
scorep-cc -std=c11 -O3 -o spd-GetIntegerDouble.x -g GetIntegerDouble.c -I /work/e05/e05/wkjee/miniconda3/include/python3.11/ -L /work/e05/e05/wkjee/miniconda3/lib/ -lpython3.11
scorep-cc -std=c11 -O3 -o spd-GetReturnString.x -g GetReturnString.c   -I /work/e05/e05/wkjee/miniconda3/include/python3.11/ -L /work/e05/e05/wkjee/miniconda3/lib/ -lpython3.11
scorep-cc -std=c11 -O3 -o spd-PassTwoIntRetSum.x -g PassTwoIntRetSum.c -I /work/e05/e05/wkjee/miniconda3/include/python3.11/ -L /work/e05/e05/wkjee/miniconda3/lib/ -lpython3.11
scorep-cc -std=c11 -O3 -o spd-SimpleCall.x -g SimpleCall.c             -I /work/e05/e05/wkjee/miniconda3/include/python3.11/ -L /work/e05/e05/wkjee/miniconda3/lib/ -lpython3.11
scorep-cc -std=c11 -O3 -o spd-CallClassMethod.x -g CallClassMethod.c   -I /work/e05/e05/wkjee/miniconda3/include/python3.11/ -L /work/e05/e05/wkjee/miniconda3/lib/ -lpython3.11
# set python library path : put this in .bashrc
# export LD_LIBRARY_PATH=/work/e05/e05/wkjee/miniconda3/lib/:$LD_LIBRARY_PATH
# setting python module path
export PYTHONPATH=$PYTHONPATH:/work/e05/e05/wkjee/Software/gulpklmc/CPython
