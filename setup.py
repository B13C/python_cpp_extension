from setuptools import setup, Extension

setup(name="PythonExtention", version="1.0", ext_modules=[Extension("PythonExtention", sources=["dllmain.c","PythonExtention.cpp"])])