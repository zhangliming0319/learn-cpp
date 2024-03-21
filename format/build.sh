#!/bin/bash

TARGET=''
COMPLIE_PARAMETER=''


echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
echo "[-r :release verision]  [-d :debug verision] [-v :open complie log]"
echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

while getopts ":drv" opt
do
    case $opt in
        d)
        echo "-> build debug verision"
        TARGET+=' -DCMAKE_BUILD_TYPE=Debug'
        ;;
        r)
        echo "-> build release verision"
        TARGET+=' -DCMAKE_BUILD_TYPE=Release'
        ;;
        v)
        echo "open complie log"
        TARGET+=' -DCMAKE_VERBOSE_MAKEFILE=ON'
        ;;
        ?)
        echo "-d build debug verision  -r build release verision -v open complie log"
        exit 1;;
    esac
done

echo ${TARGET} ${COMPLIE_PARAMETER}

mkdir -p ./build
rm -rf bin
cd ./build 
rm -rf *
cmake ${TARGET} ${COMPLIE_PARAMETER} ../; make -j16;

if [[ $TARGET == *'DEMO'* ]]
then
    cp ../demo/*.xml ../bin/
fi

