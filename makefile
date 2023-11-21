###############################################################################
# (part 3)
# purpose: makefile for flex example (Arithmetic Expressions)
# author:  Joe Crumpton
#
# 'make'        build executable file
# 'make clean'  removes all intermediate (lex.yy.c and *.o) and executable files
#
# This makefile purposely avoids macros to make the rules more clear.
# For more information about makefiles:
#      http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
#      http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#      http://www.gnu.org/software/make/manual/make.html
#
###############################################################################

# variables used in the following rules
LEX      = flex
CXX      = g++
CC       = gcc
RM       = rm
SCENE    = scene.sdf
# -g generate debug information for gdb
# -Wno-c++11-extensions silence the c++11 error warnings
# -std=c++11 assert that we are using c++11
CXXFLAGS = -g -Wno-c++11-extensions -o3 -I eigen-3.4.0/ -lm -lpthread -lX11
CCFLAGS  = -g 
# don't ever remove these file types
.PRECIOUS = *.l *.h *.cpp [Mm]akefile

RayTracer: RayTracer.cpp Primitive.o Ray.o Parser.o lex.yy.o MathUtils.o Light.o
	$(CXX) $(CXXFLAGS) -o RayTracer RayTracer.cpp Primitive.o Ray.o Parser.o lex.yy.o MathUtils.o Light.o

MathUtils.o: MathUtils.cpp
	$(CXX) $(CXXFLAGS) -o MathUtils.o -c MathUtils.cpp

Light.o:  Light.cpp
	$(CXX) $(CXXFLAGS) -o Light.o -c Light.cpp
Primitive.o: Primitive.cpp
	$(CXX) $(CXXFLAGS) -o Primitive.o -c Primitive.cpp

Ray.o: Ray.cpp
	$(CXX) $(CXXFLAGS) -o Ray.o -c Ray.cpp

Parser.o: Parser.cpp Parser.h lexer.h
	$(CXX) $(CXXFLAGS) -o Parser.o -c Parser.cpp

lex.yy.o: lex.yy.c lexer.h
	$(CC) $(CCFLAGS) -o lex.yy.o -c lex.yy.c

lex.yy.c: rules.l lexer.h
	$(LEX) -o lex.yy.c rules.l

clean: 
	$(RM) *.o lex.yy.c RayTracer
#   delete all generated files	

ring:
	ls $(.PRECIOUS)
#   tell us what is precious here
