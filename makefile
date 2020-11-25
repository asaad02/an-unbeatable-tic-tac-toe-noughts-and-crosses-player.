CFLAGS = -std=c99 -Wall -pedantic   
CC =gcc


all: ttt2.o show_node count_nodes


Clean:

	rm* .o -i
show_node: show_node.o ttt2.o ttt1.o
	gcc -std=c99 -Wall -pedantic  ttt2.c ttt1.c show_node.c -o show_node

count_nodes: count_nodes.o ttt2.o ttt1.o
	gcc -std=c99 -Wall -pedantic   ttt2.c ttt1.c count_nodes.c -o count_nodes


ttt1.o: ttt1.c
	$(CC) $(CFLAGS) -c ttt1.c -o $@

ttt2.o: ttt2.c
	$(CC) $(CFLAGS) -c ttt2.c -o $@


show_node.o:show_node.c
	$(CC) $(CFLAGS) -c show_node.c -o $@

count_nodes.o: count_nodes.c
	$(CC) $(CFLAGS) -c  count_nodes.c  -o $@

