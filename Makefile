#Makefile to build 'Trove' project

PROJECT =  trove
HEADERS =  $(PROJECT).h
OBJ     =  trove.o globals.o trovefile.o update.o words.o remove.o indexing.o findfiles.o filenames.o build.o


C11     =  gcc -std=c11
CFLAGS  =  -Wall -Werror 


$(PROJECT) : $(OBJ)
	$(C11) $(CFLAGS) -o $(PROJECT) $(OBJ)


%.o : %.c $(HEADERS)
	$(C11) $(CFLAGS) -c $<

clean :
	rm -f $(PROJECT) $(OBJ)