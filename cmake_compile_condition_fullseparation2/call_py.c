#include<stdio.h>

#ifdef __PYTHON
#include"python_interface.h"

void PyInit(PyObject** sysPath, PyObject** pModule){

	/*
		IMPORTANT:
		The variables from the main scope, sysPath<PyObject*> and pModule<PyObject*>, they are modified within this function scope,
		therefore they must be passed to this scope as 'reference' -> explaining using double pointer
	*/

	Py_Initialize();

	// modified here
	*sysPath = PySys_GetObject("path");
	PyList_Insert(*sysPath,0,PyUnicode_DecodeFSDefault("/work/e05/e05/wkjee/Software/gulpklmc/CPython"));

	// modified here
	*pModule = PyImport_ImportModule("test_module");

	if( *pModule == NULL ){
		PyErr_Print();
		Py_XDECREF(*sysPath);
		Py_Finalize();
	}

	return;
}

void PyFinal(PyObject* sysPath,PyObject* pModule){

	/*
		In this scope there is no modification on PyObject*
	*/

	Py_XDECREF(sysPath);
	Py_XDECREF(pModule);
	Py_Finalize();
}
#endif

int main()
{

#ifdef __PYTHON

	PyObject* sysPath;
	PyObject* pModule;
	//PyInit(&sysPath,&pModule);
	python_serial_init(&sysPath,&pModule,"/work/e05/e05/wkjee/Software/gulpklmc/CPython","test_module");

	char* method = "random_gen";
	//bool call_python_serial(PyObject* pModule,const char *method_name);
	call_python_serial(pModule,method); // -> segmentation fault 

	printf("flagZero\n");
	//PyFinal(sysPath,pModule);
	python_serial_final(sysPath,pModule);
	printf("flagZero\n");
#else
	printf("Python module is not loaded\n");
#endif
	return 0;
}
