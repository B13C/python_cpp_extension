#include "pch.h"
#include "framework.h"
#include "PythonExtension.h"

// 这是导出变量的一个示例
PYTHONEXTENSION_API int nPythonExtension = 0;

// 这是导出函数的一个示例。
PYTHONEXTENSION_API int fnPythonExtension(void)
{
	return 0;
}

// 这是已导出类的构造函数。
CPythonExtension::CPythonExtension()
{
	return;
}
string CPythonExtension::retStr() {
	string str = string("PyUnicode_FromString in c format , From CPP Class!");
	return str;
}

PYTHONEXTENSION_API  PyObject* test_string(PyObject* self, PyObject* args) {
	CPythonExtension cPythonExtension;
	char* str = 0;
	string s = cPythonExtension.retStr();
	return PyUnicode_FromString(s.c_str());
}

PYTHONEXTENSION_API  PyMethodDef FibonacciMethods[] = {
	//{"fibonacci", fibonacci, METH_VARARGS, "Calculate Fibonacci numbers."},
	{"test_string", test_string, METH_VARARGS, "Calculate Fibonacci numbers."},
	{NULL, NULL, 0, NULL}
};

PYTHONEXTENSION_API  struct PyModuleDef fibmodule = {
	PyModuleDef_HEAD_INIT,
	"PythonExtention",
	"PythonExtention module",
	-1,
	FibonacciMethods
};

PyMODINIT_FUNC PyInit_PythonExtention(void) {
	printf("PyInit_PythonExtention");
	return PyModule_Create(&fibmodule);
}
