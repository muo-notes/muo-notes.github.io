#!/bin/sh

# usage: ./rebuild.sh

src="*.re"

for p in ${src}
do
  ./build.sh $p
done
