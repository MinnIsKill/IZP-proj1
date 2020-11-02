  # the compiler: gcc for C program, define as g++ for C++
  CC = gcc

  # compiler flags:
  #  -g    		adds debugging information to the executable file
  #  -std=c99	
  #  -Wall 		turns on most, but not all, compiler warnings
  #  -Wextra	
  #  -Werror	
  CFLAGS  = -std=c99 -Wall -Wextra -Werror

  # the build target executable:
  TARGET = sheet

  all: $(TARGET)

  $(TARGET): $(TARGET).c
  	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET)

  clean:
  	$(RM) $(TARGET)