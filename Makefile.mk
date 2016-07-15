#------------------------------------------------------------------------------
CC=g++

THREAD_INCLUDE=pthread

MYPROGRAM=App

SOURCE=main.cpp GPIOLib.cpp UARTLib.cpp SPILib.cpp TCPClientLib.cpp TCPServerLib.cpp

#------------------------------------------------------------------------------

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)

	$(CC) -g -o $(MYPROGRAM) $(SOURCE)

clean:

	rm -f $(MYPROGRAM)
