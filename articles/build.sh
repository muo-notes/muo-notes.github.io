#!/bin/sh

if [ -z "$1" ]; then
	echo "usage: ./build.sh foobar.re"
	exit
fi

dotnet ../generator/bin/Debug/netcoreapp2.0/generator.dll $1
./genindex.sh
./sitemap.sh
git add $1 ../${1%.re}.html ../index.html ../sitemap.txt
