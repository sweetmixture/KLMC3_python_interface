#include<stdio.h>
#include<stdlib.h>

#ifdef __PYTHON
#include"python_interface.h"
#include <Python.h>
#endif

int main()
{

#ifdef __PYTHON
	Py_Initialize();
	// Import the Python module once : module load once by each processor
	PyObject *sysPath = PySys_GetObject("path");
	PyList_Insert(sysPath, 0, PyUnicode_DecodeFSDefault("/work/e05/e05/wkjee/Software/gulpklmc/CPython"));
	PyObject *pModule = PyImport_ImportModule("test_module");

	if (pModule == NULL) {
		printf("Module Found Err\n");
		PyErr_Print();
		Py_Finalize();
		return 1; // Exit with an error code
	}

	//char* method = "random_gen";
	char method[256];
	strcpy(method,"random_gen");
	
	//bool call_python_serial(PyObject* pModule,const char *method_name);
	call_python_serial(pModule,method);

	Py_XDECREF(sysPath);
	Py_XDECREF(pModule);
	Py_Finalize();
#else
	printf("Python module is not loaded\n");
#endif
	return 0;
}
