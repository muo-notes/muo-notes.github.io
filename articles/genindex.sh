#!/bin/sh

CWD=`dirname $0`

cd $CWD
dotnet ../generator/bin/Debug/netcoreapp1.0/generator.dll index
