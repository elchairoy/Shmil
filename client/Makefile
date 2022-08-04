BIN     := bin
SRC     := src
INCLUDE := include

CC       := gcc
CC_FLAGS := -Wall -ansi -pedantic -ggdb -I${INCLUDE} -I${SRC} -lm

VALGRIND       := valgrind
VALGRIND_FLAGS := --leak-check=yes --error-exitcode=2

SOURCES := $(shell find ${SRC} -type f -name '*.c')
HEADERS := $(shell find . -type f -name '*.h')

CLIENT := ${BIN}/client.bin 

all: ${CLIENT}

run: ${CLIENT}
	./${CLIENT}

${CLIENT}: ${SOURCES} ${HEADERS}
	mkdir -p ${BIN}
	${CC} -o ${CLIENT} ${CC_FLAGS} $^ 

valgrind: ${CLIENT}
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes ./${CLIENT}

clean:
	rm -f ${CLIENT}