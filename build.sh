#!/bin/sh

if [[ "$1" = "clean" ]]; then
	cp main.cpp main
	rm *.o
	rm *.cpp
	rm *.h
	rm gen*
	rm Mak*	
else
	cp main main.cpp
	qmake -project
	echo "QT += xml" >> gen.pro
	qmake
	make
	./gen
fi
