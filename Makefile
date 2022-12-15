##########################
##### COMPILER FLAGS #####
##########################
CC=clang
CFLAGS=-Wall -Wextra -pedantic -fdiagnostics-color=always
CFLAGS+=$(CPPFLAGS) -O0 -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address
LDFLAGS+=-fsanitize=address



############################
##### FILES TO COMPILE #####
############################



# Program:
ftc: 
	$(CC) $(CFLAGS) -o ftc src/ftc.c src/MegaMimes.c



# Format is:
## program_name: file_name1.o file_name2.o

#compile .c and .h file from src to root




# Object files
ftc.o:  src/ftc.c src/ftc.h src/MegaMimes.h
MegaMimes.o : src/MegaMimes.c src/MegaMimes.h
# Format is:
## file_name.o: <dependency.o> <header_file.h> file_name.c


##########################
##### OTHER COMMANDS #####
##########################

clean:
	rm -f *.o *_test ftc

# For the test, replace `solveur_main_test` with your program name.


.SILENT: clean
