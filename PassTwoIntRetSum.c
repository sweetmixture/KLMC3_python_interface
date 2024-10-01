#include <Python.h>
#include <mpi.h>

int call_python(PyObject *pModule, const char *method, const int arg1, const int arg2) {

    /* from module, load function */
    PyObject *pMethod = PyObject_GetAttrString(pModule, method); // New reference

	// callable check
    if (!PyCallable_Check(pMethod)) {
        printf("Method/Function Found Err\n");
        PyErr_Print();
        return 1;
    }

    /* setting input args */
    PyObject *pArgs = PyTuple_Pack(2, PyLong_FromLong(arg1), PyLong_FromLong(arg2)); // PyLong <=> C int, New reference

    /* call pMethod */
    PyObject *pRes = PyObject_CallObject(pMethod, pArgs); // New reference

    if (pRes != NULL) {
        long res = PyLong_AsLong(pRes); // Retreive PyLong to C int
        printf(" -- in python wrapper -- Sum of two integers: %ld\n", res);
        Py_XDECREF(pRes);
    } else {
        PyErr_Print();
    }

    /* MEM RELEASE ? */
    Py_XDECREF(pMethod);
    Py_XDECREF(pArgs);

    return 0;
}

int main() {
    // Initialize the Python interpreter
	
	MPI_Init(NULL,NULL);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	printf("rank %d\n",rank);

    Py_Initialize();

    // Import the Python module once : module load once by each processor - module search path added
    PyObject *sysPath = PySys_GetObject("path"); // Borrowed reference
    PyList_Insert(sysPath, 0, PyUnicode_DecodeFSDefault("/work/e05/e05/wkjee/Software/gulpklmc/CPython")); 

    PyObject *pModule = PyImport_ImportModule("my_python_module"); // New reference, module added

	// check if module exists
    if (pModule == NULL) {
        printf("Module Found Err, rank : %d\n",rank);
        PyErr_Print();
        Py_Finalize();
        return 1; // Exit with an error code
    }

    printf("-------------- call by wrapper, rank : %d \n",rank);

	if( rank == 0 ){
		printf(" * calling processor <1> -  %d\n",rank);
    	call_python(pModule, "add_two_integers", rank,rank);
	}
	MPI_Barrier(MPI_COMM_WORLD);

	if( rank == 1 ){
		printf(" * calling processor <2> -  %d\n",rank);
    	call_python(pModule, "add_two_integers", rank,rank);
	}
	MPI_Barrier(MPI_COMM_WORLD);
    // Finalize the Python interpreter when your program exits
    Py_XDECREF(sysPath);
    Py_XDECREF(pModule);
    Py_Finalize();

	MPI_Finalize();
    return 0; // Exit successfully
}
