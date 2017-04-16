#!/bin/sh

CWD=`dirname $0`

cd $CWD
review-index -a --html > ../index.html
