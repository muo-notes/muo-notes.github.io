#!/bin/sh

CWD=`dirname $0`

cd $CWD
review-index -a --html | sed -e 's/<a name=/<a href=/g' > ../index.html
