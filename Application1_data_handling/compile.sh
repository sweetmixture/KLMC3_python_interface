# source
# print_python_list_object.c


INCL="-I /work/e05/e05/wkjee/miniconda3/include/python3.11/"
LINK="-L /work/e05/e05/wkjee/miniconda3/lib/ -lpython3.11"

# Python.h header + library link
cc -std=c11 -O3 -o print_python_list_object.x print_python_list_object.c ${INCL} ${LINK}
cc -std=c11 -O3 -o pass_data_c2py_str_double_arr.x pass_data_c2py_str_double_arr.c ${INCL} ${LINK}
cc -std=c11 -O3 -o pass_data_c2py_double_arr_change.x pass_data_c2py_double_arr_change.c ${INCL} ${LINK}

# set python library path : put this in .bashrc
# export LD_LIBRARY_PATH=/work/e05/e05/wkjee/miniconda3/lib/:$LD_LIBRARY_PATH
# setting python module path
export PYTHONPATH=$PYTHONPATH:/work/e05/e05/wkjee/Software/gulpklmc/CPython
