CC = cc
CFLAGS = -Wall -Wextra -pedantic -std=c11

CLEAN = rm -rf
MKDIR = mkdir

DIRT = test
DIRS = src
DIRB = build
DIRBT = build/test
UNITY = src/dep/Unity/src/unity.c

test: build_tests run_tests

build_tests: cleanup
	$(MKDIR) $(DIRB) $(DIRBT)
	$(CC) $(DIRT)/*.c $(DIRS)/*.c $(UNITY) -o $(DIRBT)/testLine $(CFLAGS)

run_tests:
	$(DIRBT)/testLine

cleanup:
	$(CLEAN) $(DIRB)