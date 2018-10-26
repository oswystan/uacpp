#######################################################################
##                     Copyright (C) 2018 wystan
##
##       filename: makefile
##    description: 
##        created: 2018-10-25 12:10:36
##         author: wystan
## 
#######################################################################
.PHONY: all build test install doc

a: uacpp.cpp  main.cpp uacpp.h
	g++ -std=c++11 $^ -o $@
	./a

clean:
	rm -f ./a
#######################################################################
