CC = gcc
TARGET = test
TARGET_DYN = test_dynamic

static:
	$(CC) test.c -L.. -lAddressBook -o $(TARGET)

shared:
	$(CC) test.c -L.. -Wl,-rpath=.. -lAddressBook -o $(TARGET)

dynamic:
	$(CC) test_dynamic.c -ldl -o $(TARGET_DYN)

clean:
	@echo Removing output files
	@rm $(TARGET) $(TARGET_DYN)
