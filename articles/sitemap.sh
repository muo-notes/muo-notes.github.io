#!/bin/bash

cd ../
ls *.html | sort > sitemap.txt
sed -e "s/^/https:\/\/notes.muo.jp\//g" sitemap.txt | tee sitemap.txt >/dev/null
