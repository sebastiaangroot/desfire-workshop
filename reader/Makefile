all: chal1 chal2 chal3

chal%:
	$(CC) src/$@.c libfreefare/libfreefare/.libs/libfreefare.so -I libfreefare/libfreefare -lnfc -o bin/$@

clean:
	rm bin/chal1 bin/chal2 bin/chal3
