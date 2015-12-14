FILE= Producer_Consumer

run: ${FILE}
	./${FILE}

# We include -lpthread here, for a program that uses POSIX threads.
# Newer versions of gcc allow you to simply invoke '-pthread' instead
#   of '-lpthread'
${FILE}: ${FILE}.c sem.c
	gcc -g -O0 sem.c -o ${FILE} ${FILE}.c -lpthread

gdb: ${FILE}
	gdb ${FILE}

vi: ${FILE}.c
	vi ${FILE}.c

emacs: ${FILE}.c
	emacs ${FILE}.c
