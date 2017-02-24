#!/bin/sh

# usage: ./build.sh foobar.re

dotnet ../generator/bin/Debug/netcoreapp1.0/generator.dll $1
