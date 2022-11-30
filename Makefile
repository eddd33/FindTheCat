##########################
##### COMPILER FLAGS #####
##########################
#CC=clang
#CFLAGS=-Wall -Wextra -pedantic -fdiagnostics-color=always
#CFLAGS+=$(CPPFLAGS) -O0 -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls
#LDFLAGS+=-fsanitize=address



############################
##### FILES TO COMPILE #####
############################

# Program:
ftc: ftc.o
gcc -o ftc ftc.o
# Format is:
## program_name: file_name1.o file_name2.o


# Object files
ftc.o:  ftc.c ftc.h
gcc -c ftc.c
# Format is:
## file_name.o: <dependency.o> <header_file.h> file_name.c


##########################
##### OTHER COMMANDS #####
##########################

clean:
	rm -f *.o *_test

# For the test, replace `solveur_main_test` with your program name.


.SILENT: clean
