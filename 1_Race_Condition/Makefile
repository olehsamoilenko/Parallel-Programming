all:
	gcc prog.c -pthread -o race_condition
	gcc mutex.c -pthread -o mutex
	gcc semaphore.c -pthread -o semaphore -Wno-deprecated

clean:
	rm race_condition mutex semaphore
