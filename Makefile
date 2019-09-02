TARGET = EASolver
OBJS = easolver.o main.o matrix.o readwrite.o stdatomweight.o
CC = g++

$(TARGET): $(OBJS) 
	$(CC) -o $@ $(OBJS)
%.o : %.cpp
	$(CC) -c $^ -o $@

.PHONY:clean
clean:
	-rm -rf $(OBJS)
