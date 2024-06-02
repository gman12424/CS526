# June 24, 2004
#
# Makefile for compiling accompanying software for
# "Discrete-Event Simulation: A First Course" by Park and Leemis
#

CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lm

OBJFILES = acs boxes buffon bvs cdh craps det ddh estimate Final1 Final3 Final52 galileo geometricTest hat idiotsDelight integers msq pdf rngs.o rvgs.o rvms.o san sieve sis1 sis2 sis3 sis4 snow ssms ssq1 ssq2 ssq21 ssq22 ssq3 ssq4 test triangle ttr uvs uvs2

all: $(OBJFILES)

acs: acs.c
	$(CC) $(LDFLAGS) $< -o $@

boxes: boxes.c rngs.o
	$(CC) $(LDFLAGS) $^ -o $@

buffon: buffon.c rng.o
	$(CC) $(LDFLAGS) $^ -o $@

cdh: cdh.c
	$(CC) $(LDFLAGS) $^ -o $@

craps: craps.c rng.o
	$(CC) $(LDFLAGS) $^ -o $@

det: det.c rng.o
	$(CC) $(LDFLAGS) $^ -o $@

ddh: ddh.c
	$(CC) $(LDFLAGS) $^ -o $@

estimate: estimate.c rngs.o rvms.o
	$(CC) $(LDFLAGS) $^ -o $@

Final1: Final1.c rngs.o rvgs.o
	$(CC) $(LDFLAGS) $^ -o $@

Final3: Final3.c rngs.o rvgs.o
	$(CC) $(LDFLAGS) $^ -o $@

Final52: Final52.c rngs.o rvgs.o
	$(CC) $(LDFLAGS) $^ -o $@

galileo: galileo.c rng.o
	$(CC) $(LDFLAGS) $^ -o $@

geometricTest: geometricTest.c rngs.o rvgs.o
	$(CC) $(LDFLAGS) $^ -o $@

hat: hat.c rng.o
	$(CC) $(LDFLAGS) $^ -o $@

idiotsDelight: idiotsDelight.c rngs.o
	$(CC) $(LDFLAGS) $^ -o $@

integers: integers.c rngs.o
	$(CC) $(LDFLAGS) $^ -o $@

msq: msq.c rngs.o
	$(CC) $(LDFLAGS) $^ -o $@

pdf: pdf.c rngs.o
	$(CC) $(LDFLAGS) $^ -o $@

rng.o: rng.c rng.h
	$(CC) -c $<

rngs.o: rngs.c rngs.h
	$(CC) -c $<

rvgs.o: rvgs.c rvgs.h rngs.c rngs.h
	$(CC) -c $<

rvms.o: rvms.c rvms.h rngs.c rngs.h
	$(CC) -c $<

san: san.c rngs.o
	$(CC) $(LDFLAGS) $^ -o $@

sieve: sieve.c
	$(CC) $(LDFLAGS) $^ -o $@

sis1: sis1.c
	$(CC) $(LDFLAGS) $^ -o $@

sis2: sis2.c rng.o
	$(CC) $(LDFLAGS) $^ -o $@

sis3: sis3.c rngs.o
	$(CC) $(LDFLAGS) $^ -o $@

sis4: sis4.c rngs.o rvgs.o
	$(CC) $(LDFLAGS) $^ -o $@

snow: snow.c rngs.o
	$(CC) $(LDFLAGS) $^ -o $@

ssms: ssms.c rngs.o
	$(CC) $(LDFLAGS) $^ -o $@

ssq1: ssq1.c
	$(CC) $(LDFLAGS) $^ -o $@

ssq2: ssq2.c rng.o
	$(CC) $(LDFLAGS) $^ -o $@

ssq21: ssq21.c rngs.o
	$(CC) $(LDFLAGS) $^ -o $@

ssq22: ssq22.c rngs.o
	$(CC) $(LDFLAGS) $^ -o $@

ssq3: ssq3.c rngs.o
	$(CC) $(LDFLAGS) $^ -o $@

ssq4: ssq4.c rngs.o rvgs.o
	$(CC) $(LDFLAGS) $^ -o $@

test: test.c rngs.o
	$(CC) $(LDFLAGS) $^ -o $@

triangle: triangle.c rng.o
	$(CC) $(LDFLAGS) $^ -o $@

ttr:  ttr.c rngs.o rvgs.o
	$(CC) $(LDFLAGS) $^ -o $@

uvs: uvs.c rngs.o rvgs.o
	$(CC) $(LDFLAGS) $^ -o $@

uvs2: uvs2.c rngs.o rvgs.o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	/bin/rm -f $(OBJFILES) core*
