# CS315 Makefile for Program 5: Families
# Feel free to modify as needed.
# Original author: Raphael Finkel 4/2020

CFLAGS = -Wall -g
CPPFLAGS = -Wall -g
GOAL = genealogy
DATA = data.txt
WORKING = workingGenealogy
PROG = prog5

# compile the student program, placing the result in tmpRun.out
make: $(GOAL).* familyTree.* family.* person.* A5queue.*
	g++  $(GOAL).cpp familyTree.* family.* person.* A5queue.* -o $(GOAL)

# run the student program, placing the result in tmpRun.out
run:
	./$(GOAL) < $(DATA) > tmpRun.out
	less tmpRun.out

# run a known working program, placing the result in tmpWorking.out
runWorking: $(WORKING) $(DATA)
	./$(WORKING) < $(DATA) > tmpWorking.out
	less tmpWorking.out

# get the working program
$(WORKING):
	wget http://www.cs.uky.edu/~raphael/courses/CS315/$(PROG)/$(WORKING)
	chmod +x $(WORKING)

# get the data
$(DATA):
	wget http://www.cs.uky.edu/~raphael/courses/CS315/$(PROG)/$(DATA)

# Modify the following recipe to zip exactly what you want to include.
zipAll:
	zip $(GOAL).zip $(GOAL).* familyTree.* family.* person.* A5queue.* makefile README *.out *.txt
