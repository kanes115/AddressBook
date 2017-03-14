CC = gcc
TARGET = test
TARGET_DYN = test_dynamic

static:
	$(CC) test.c -g -L.. -lAddressBook -o $(TARGET)

shared:
	$(CC) test.c -g -L.. -Wl,-rpath=.. -lAddressBook -o $(TARGET)

dynamic:
	$(CC) test_dynamic.c -g -ldl -o $(TARGET_DYN)

clean:
	@echo Removing output files
	@rm -f $(TARGET) $(TARGET_DYN) *.o
