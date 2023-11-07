cmake_minimum_required(VERSION 3.11)
project(YourProjectName VERSION 1.0 LANGUAGES C)


if (PYTHON_INTERFACE)
	add_compile_definitions(__PYTHON)	# ENABLEING __PYTHON FLAG DURING THE COMPILATION
	# Source files
	set(SOURCES 
	    call_py.c
	    /work/e05/e05/wkjee/Software/gulpklmc/klmc3_tf_interface.update.12092023/KLMC3.112023/python_interface/call_python_serial.c
	)
	# Include directories
	include_directories(
	    /work/e05/e05/wkjee/miniconda3/include/python3.11/
	    /work/e05/e05/wkjee/Software/gulpklmc/klmc3_tf_interface.update.12092023/KLMC3.112023/python_interface/include
	)
	# Compile the sources into an executable
	add_executable(m.x ${SOURCES})
	# Compiler flags
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -O3")
	# Link the Python library
	target_link_libraries(m.x /work/e05/e05/wkjee/miniconda3/lib/libpython3.11.so)

	# POSSIBLE COMMAND : cmake -DPYTHON_INTERFACE=ON /path/to/your/source/directory
else()

set(SOURCES
	call_py.c
)
add_executable(m.x ${SOURCES})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGSE} -std=c11 -O3")

endif()
