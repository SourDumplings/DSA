/**
 * @file Python_interfaces.cpp
 * @author  SourDumplings (changzheng300@foxmail.com)
 * @brief 
 * @version 1.0.0
 * @date 2023-10-26
 * 
 * @copyright Copyright (c) 2023 SourDumplings
 * 
 */

#include "Python_interfaces.h"
#include "../Algorithms/Is_prime.h"

bool Is_prime(int x, int method)
{
    return CZ::Is_prime(x, static_cast<CZ::PrimeAccessories::IsPrimeMethod>(method));
}

int Add(int x, int y)
{
    return x + y;
}

PyObject* Wrapp_Is_prime(PyObject* self, PyObject* args)
{
    int x;
    int method;
    if (!PyArg_ParseTuple(args, "ii", &x, &method)) 
    { 
        return NULL;
    } 
    return Py_BuildValue("i", Is_prime(x, method));
}

PyObject* Wrapp_Add(PyObject* self, PyObject* args)
{
    int x;
    int y;
    if (!PyArg_ParseTuple(args, "ii", &x, &y)) 
    {
        return NULL;
    }
    return Py_BuildValue("i", Add(x, y));
}

PyMODINIT_FUNC PyInit_libdsa(void)
{
    return PyModule_Create(&CZDSAPy3Mod);
}