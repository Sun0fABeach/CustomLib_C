PROJECTNAME	= CustomLib_C
CC			= /usr/bin/gcc
CPPFLAGS	= -I include
CFLAGS		= -Wall -Wextra -std=gnu11 -g
LDFLAGS		=
COMPILE		= $(CC) $(CFLAGS) $(CPPFLAGS)
CDIR		= source
TDIR		= unittests
HDIR		= include

vpath %.c $(CDIR)
vpath %.h $(HDIR)

.PHONY: showpp open clean tar

test: test_dyn_input test_mylib test_strlib

test_%: %.c %.h $(TDIR)/test_%.c
	$(COMPILE) $^ -o $@

# helpers
showpp:
	$(COMPILE) $(CDIR)/*.c -E
open:
	vi -p $(CDIR)/*.c $(HDIR)/*.h Makefile
clean:
	rm -f test_* $(PROJECTNAME).tar
tar:
	tar -cvf $(PROJECTNAME).tar .
