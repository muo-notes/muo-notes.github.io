#!/bin/sh

CWD=`dirname $0`

cd $CWD
dotnet ../generator/bin/Debug/netcoreapp2.0/generator.dll index
