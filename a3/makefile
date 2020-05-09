# CS315 Makefile for Program 3: kd
# Feel free to modify as needed.
# Original author: Raphael Finkel 1/2020

CFLAGS = -Wall -g
CPPFLAGS = -Wall -g
GOAL = kd

NUMPOINTS = 50
SEED = 42
MODULUS = 1000
NUMPROBES = 10

# compile the student program
make: kd.cpp kdTree.cpp kdNode.cpp
	g++ kd.cpp kdTree.cpp kdNode.cpp -o $(GOAL)

# run the student program, placing the result in tmpRun.out
run: $(GOAL) randGen.pl
	./randGen.pl $(SEED) $(MODULUS) | ./$(GOAL) $(NUMPOINTS) $(NUMPROBES) > tmpRun.out
	cat tmpRun.out

# compile and run a known working program, placing the result in tmpWorking.out
runWorking: workingKD randGen.pl
	./randGen.pl $(SEED) $(MODULUS) | ./workingKD $(NUMPOINTS) $(NUMPROBES) > tmpWorking.out
	cat tmpWorking.out

# get the randGen.pl program
randGen.pl:
	wget http://www.cs.uky.edu/~raphael/courses/CS315/prog1/randGen.pl
	chmod +x randGen.pl

# get the workingKD program
workingKD:
	wget http://www.cs.uky.edu/~raphael/courses/CS315/prog3/workingKD
	chmod +x workingKD

# Modify the following recipe to zip exactly what you want to include.
zipAll:
	zip toSubmit.zip $(GOAL) $(GOAL).cpp $(GOAL)Tree.* $(GOAL)Node.* makefile README tmpRun.out
