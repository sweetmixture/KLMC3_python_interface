#include<stdio.h>
#include"python_interface.h"

int main()
{
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

	//bool call_python_serial(PyObject* pModule,const char *method_name);

	char* method = "random_gen";
	call_python_serial(pModule,method);

	Py_XDECREF(sysPath);
	Py_XDECREF(pModule);
	Py_Finalize();

	return 0;
}
