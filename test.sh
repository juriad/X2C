#!/bin/sh 

rm -R t

find tests -iname "*.xsd" |

while read f; do
	mkdir t

	g="`dirname "$f"`/`basename "$f" ".xsd"`.xml"
	element=`grep "<[a-zA-Z]" "$g" | 
		head -1 | 
		sed 's/^[^a-zA-Z]*\([:a-zA-Z]\+\).*$/\1/' | 
		sed 's/.*://' | 
		sed 's/\(.\)\(.*\)/\U\1\E\2/'`
	echo $f

	cd src
	{
	qmake
	make
	./X2C "../$f" "" "xs" ../t
	} >/dev/null 2>&1
	cd ../t

	sed 's/${root}/'$element'/g' ../test.cpp.templ >main.cpp

	{
	qmake -project
	echo "QT += xml" >> t.pro
	qmake
	make
	} >/dev/null 2>&1
	./t "../$g"
	echo $?

	cd ..

	rm -R t
done

cd src
rm *.o
rm X2C
rm Makefile
cd ..
