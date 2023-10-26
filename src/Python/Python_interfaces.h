/**
 * @file Python_interface.h
 * @author  SourDumplings (changzheng300@foxmail.com)
 * @brief 可暴露给 Python3 调用的接口 
 * @version 1.0.0
 * @date 2023-10-26
 * 
 * @copyright Copyright (c) 2023 SourDumplings
 * 
 */

#include <Python.h>

bool Is_prime(int x, int method);
int Add(int x, int y);

PyObject* Wrapp_Is_prime(PyObject* self, PyObject* args);
PyObject* Wrapp_Add(PyObject* self, PyObject* args);

static PyMethodDef py3_interfaces[] = {
    {"Add", Wrapp_Add, METH_VARARGS, "计算 x + y"},
    {"Is_prime", Wrapp_Is_prime, METH_VARARGS, "判断是否是素数, method 0 蛮力算法，1 素数表算法，2 正则表达式算法"},
    {NULL, NULL},
};

// Python3 以后使用
static struct PyModuleDef CZDSAPy3Mod = 
{
    PyModuleDef_HEAD_INIT,
    "CZDSAPy3Mod", /* name of module */
    "",          /* module documentation, may be NULL */
    -1,          /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    py3_interfaces
};

PyMODINIT_FUNC PyInit_libdsa(void);