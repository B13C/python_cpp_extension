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

PYTHONEXTENSION_API  PyObject* test_list(PyObject* self, PyObject* args) {
	PyObject* lst = nullptr;
	if (!PyArg_ParseTuple(args, "O", &lst)) {
		return nullptr;
	}

	if (!PyList_Check(lst)) {
		PyErr_SetString(PyExc_Exception, "arg must be list");
		return nullptr;
	}

	Py_ssize_t size = PyList_Size(lst);
	for (size_t i = 0; i < size; i++)
	{
		PyObject* val = PyList_GetItem(lst, i);
		int r = PyLong_AsLong(val);
		printf("%d ", r);
	}
	Py_RETURN_NONE;
}

PYTHONEXTENSION_API  PyObject* test_ret_tuple(PyObject* self, PyObject* args) {
	PyObject* tup = PyTuple_New(10);
	PyTuple_SetItem(tup, 0, PyLong_FromLong(10));
	PyTuple_SetItem(tup, 1, PyLong_FromLong(30));
	PyTuple_SetItem(tup, 2, PyUnicode_FromString("Test Tuple return string"));
	return tup;
}

PYTHONEXTENSION_API  PyObject* test_tuple(PyObject* self, PyObject* args) {
	PyObject* tup = nullptr;
	if (!PyArg_ParseTuple(args, "O", &tup)) {
		return  nullptr;
	}
	Py_ssize_t size = PyTuple_Size(tup);
	for (size_t i = 0; i < size; i++)
	{
		PyObject* val = PyTuple_GetItem(tup, i);
		int r = PyLong_AsLong(val);
		printf("val = %d\n", r);
	}
	Py_RETURN_NONE;
}

PYTHONEXTENSION_API  PyObject* test_kw(PyObject* self, PyObject* args, PyObject* kw) {
	const char* name = "";
	int age = 49;
	int score = 0;
	char key_name[] = "name";
	char key_age[] = "age";
	char key_score[] = "score";
	char* keys[] = { key_name, key_age , key_score , nullptr };
	if (!PyArg_ParseTupleAndKeywords(args, kw, "s|ii", keys, &name, &age, &score)) {
		return nullptr;
	}
	printf("Name is %s , age is %d , score is %d", name, age, score);
	Py_RETURN_NONE;
}

PYTHONEXTENSION_API  PyObject* test_string(PyObject* self, PyObject* args) {
	CPythonExtension cPythonExtension;
	char* str = 0;
	if (!PyArg_ParseTuple(args, "s", &str)) {
		return nullptr;
	}
	printf("PyArg_ParseTuple return string = %s\n", str);
	string s = cPythonExtension.retStr();
	return PyUnicode_FromString(s.c_str());
}

PYTHONEXTENSION_API  PyMethodDef  PyExtensionMethods[] = {
	{"test_string", test_string, METH_VARARGS, "Test String."},
	{"test_kw", (PyCFunction)test_kw, METH_KEYWORDS | METH_VARARGS, "Test Key words."},
	{"test_tuple", test_tuple, METH_VARARGS, "Test Tuple."},
	{"test_ret_tuple", test_ret_tuple, METH_NOARGS, "Test Return Tuple."},
	{"test_list", test_list, METH_VARARGS, "Test List."},
	{NULL, NULL, 0, NULL}
};

PYTHONEXTENSION_API  struct PyModuleDef pythonExtensionModule = {
	PyModuleDef_HEAD_INIT,
	"PythonExtention",
	"PythonExtention module",
	-1,
	PyExtensionMethods
};

PyMODINIT_FUNC PyInit_PythonExtention(void) {
	printf("PyInit_PythonExtention");
	return PyModule_Create(&pythonExtensionModule);
}
