#!/bin/bash

#g++ -shared -Wl,-soname,c_python -o c_python.so -fPIC c_python.cc

g++ -shared -o c_python.so -fPIC c_python.cc