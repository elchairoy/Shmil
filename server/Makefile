BIN     := bin
SRC     := src
INCLUDE := include

CC       := gcc
CC_FLAGS := -Wall -ansi -pedantic -ggdb -I${INCLUDE} -I${SRC} -lm

VALGRIND       := valgrind
VALGRIND_FLAGS := --leak-check=yes --error-exitcode=2

SOURCES := $(shell find ${SRC} -type f -name '*.c')
HEADERS := $(shell find . -type f -name '*.h')

SERVER := ${BIN}/server.bin 

all: ${SERVER}

run: ${SERVER}
	./${SERVER}

${SERVER}: ${SOURCES} ${HEADERS}
	mkdir -p ${BIN}
	${CC} -o ${SERVER} ${CC_FLAGS} $^ 

valgrind: ${SERVER}
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes ./${SERVER}

clean:
	rm -f ${SERVER}