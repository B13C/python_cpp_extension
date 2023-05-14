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


// 自定义类型
typedef struct {
	PyObject_HEAD
		int value;
} MyTypeObject;

// 析构函数
static void MyType_dealloc(MyTypeObject* self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

//构造函数
static PyObject* MyType_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
	MyTypeObject* self;
	self = (MyTypeObject*)type->tp_alloc(type, 0);
	if (self != NULL) {
		self->value = 0;
	}
	return (PyObject*)self;
}

// 初始化函数
static int MyType_init(MyTypeObject* self, PyObject* args, PyObject* kwds) {
	char value[] = "value";
	static char* kwlist[] = { value, NULL };
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist, &self->value)) {
		return -1;
	}
	return 0;
}

// 成员函数
static PyMemberDef MyType_members[] = {
	{"value", T_INT, offsetof(MyTypeObject, value), 0, "MyType value"},
	{NULL}
};

static PyTypeObject MyType = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"my_module.MyType",         /* tp_name */
	sizeof(MyTypeObject),       /* tp_basicsize */
	0,                          /* tp_itemsize */
	(destructor)MyType_dealloc, /* tp_dealloc */
	0,                          /* tp_print */
	0,                          /* tp_getattr */
	0,                          /* tp_setattr */
	0,                          /* tp_reserved */
	0,                          /* tp_repr */
	0,                          /* tp_as_number */
	0,                          /* tp_as_sequence */
	0,                          /* tp_as_mapping */
	0,                          /* tp_hash  */
	0,                          /* tp_call */
	0,                          /* tp_str */
	0,                          /* tp_getattro */
	0,                          /* tp_setattro */
	0,                          /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT,         /* tp_flags */
	"MyType objects",           /* tp_doc */
	0,                          /* tp_traverse */
	0,                          /* tp_clear */
	0,                          /* tp_richcompare */
	0,                          /* tp_weaklistoffset */
	0,                          /* tp_iter */
	0,                          /* tp_iternext */
	0,                          /* tp_methods */
	MyType_members,             /* tp_members */
	0,                          /* tp_getset */
	0,                          /* tp_base */
	0,                          /* tp_dict */
	0,                          /* tp_descr_get */
	0,                          /* tp_descr_set */
	0,                          /* tp_dictoffset */
	(initproc)MyType_init,      /* tp_init */
	0,                          /* tp_alloc */
	MyType_new,                 /* tp_new */
};

// 配置
PYTHONEXTENSION_API  PyMethodDef  PyExtensionMethods[] = {
	{"test_string", test_string, METH_VARARGS, "Test String."},
	{"test_kw", (PyCFunction)test_kw, METH_KEYWORDS | METH_VARARGS, "Test Key words."},
	{"test_tuple", test_tuple, METH_VARARGS, "Test Tuple."},
	{"test_ret_tuple", test_ret_tuple, METH_NOARGS, "Test Return Tuple."},
	{"test_list", test_list, METH_VARARGS, "Test List."},
	{NULL, NULL, 0, NULL}
};

// 模块定义
PYTHONEXTENSION_API  struct PyModuleDef pythonExtensionModule = {
	PyModuleDef_HEAD_INIT,
	"PythonExtention",
	"PythonExtention module",
	-1,
	PyExtensionMethods
};

// 初始化模块
PyMODINIT_FUNC PyInit_PythonExtention(void) {
	printf("PyInit_PythonExtention");
	PyObject* m;
	m = PyModule_Create(&pythonExtensionModule);
	if (m == NULL) {
		return NULL;
	}
	// 初始化类
	if (PyType_Ready(&MyType) < 0) {
		return NULL;
	}
	// 引用计数+1
	Py_INCREF(&MyType);
	PyModule_AddObject(m, "MyType", (PyObject*)&MyType);
	return m;
}
