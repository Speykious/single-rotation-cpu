CPP=g++			# Name of the compiler
LINKS=-g -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system		# Links like libraries
EXEC=single_rotation.exe	# Name of the final compiled program

all:
	${CPP} ../src/*.cpp -L../lib -I../include ${LINKS} -c
	${CPP} *.o -L../lib -I../include ${LINKS} -o ${EXEC}
	./${EXEC}