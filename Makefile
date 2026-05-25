myls: myls.c mylib.c myls.h
	gcc myls.c -g -o myls
clean:
	rm myls
