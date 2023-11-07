#include <Python.h>

void modifyObject(PyObject** objPtr) {
    // Allocate a new Python string object
    *objPtr = PyUnicode_FromString("Modified String");
}

int main() {
    Py_Initialize();

    PyObject* originalObj = PyUnicode_FromString("Original String");
    printf("Before: %s\n", PyUnicode_AsUTF8(originalObj));

    // Pass a pointer to the originalObj pointer
    modifyObject(&originalObj);

    printf("After: %s\n", PyUnicode_AsUTF8(originalObj));

    Py_XDECREF(originalObj);
    Py_Finalize();

    return 0;
}


/*

You are correct that PyObject* is already a pointer to a Python object, so you might wonder why you would pass it as PyObject** (a pointer to a pointer) to a C function.
The reason for passing a pointer to a pointer (PyObject**) is related to memory management and object ownership in C when interfacing with Python.

When you pass a PyObject* to a C function, you are passing a reference to a Python object.
However, in certain situations, the C function might need to modify the object itself, like reassigning the pointer to point to a different Python object.
If you simply pass PyObject*, any changes made to the pointer inside the function won't be reflected outside of the function.
This is because C passes arguments by value, so the function gets a copy of the pointer.

By passing PyObject**, you are passing a reference to a pointer.
This means the function can modify the actual pointer in the calling code, not just the copy of the pointer.
This is useful when the function needs to return a new Python object or modify the existing object, as those changes will be visible outside of the function.

In this example, modifyObject takes a PyObject** and assigns a new string object to the pointer.
This change is visible outside the function because we are modifying the actual pointer, not just a copy.
When you run this code, you'll see that the modified string is printed, indicating that the originalObj pointer has been modified inside the function.

*/
