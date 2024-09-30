#include <Python.h>

void print_sys_path() {
    // Get the sys.path object
    PyObject* sysPath = PySys_GetObject("path");

    // Check if sysPath is a list
    if (PyList_Check(sysPath)) {
        // Get the size of the list
        Py_ssize_t size = PyList_Size(sysPath);

        // Loop through the list and print each item
        for (Py_ssize_t i = 0; i < size; ++i) {
            PyObject* item = PyList_GetItem(sysPath, i);  // Borrowed reference

            // Ensure item is a string
            if (PyUnicode_Check(item)) {
                // Convert to C string and print it
                const char* pathStr = PyUnicode_AsUTF8(item);
                if (pathStr) {
                    printf("sys.path[%zd] = %s\n", i, pathStr);
                }
            } else {
                // Handle non-string items (just in case)
                printf("sys.path[%zd] is not a string\n", i);
            }
        }
    } else {
        printf("sys.path is not a list\n");
    }
}

int main(int argc, char *argv[]) {
    // Initialize the Python interpreter
    Py_Initialize();

    // Print the sys.path
    print_sys_path();

    // Finalize the Python interpreter
    Py_Finalize();

    return 0;
}

/* Possible Output

$. /print_python_list_object.x 

sys.path[0] = /work/y07/shared/utils/core/bolt/0.8/modules
sys.path[1] = /work/e05/e05/wkjee/miniconda3/lib/python311.zip
sys.path[2] = /work/e05/e05/wkjee/miniconda3/lib/python3.11
sys.path[3] = /work/e05/e05/wkjee/miniconda3/lib/python3.11/lib-dynload
sys.path[4] = /work/e05/e05/wkjee/miniconda3/lib/python3.11/site-packages
sys.path[5] = /mnt/lustre/a2fs-work2/work/e05/e05/wkjee/Software/Scripts/Python/AppOutputAnalysis
sys.path[6] = /mnt/lustre/a2fs-work2/work/e05/e05/wkjee/Software/MultiToolkit

*/
