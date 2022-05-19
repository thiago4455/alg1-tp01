OBJFILES = main
TARGET=tp01

OBJFILES := $(addsuffix .o, $(OBJFILES))
COMMAND = g++ -g -Wall -o $(TARGET) $(addprefix src/, $(OBJFILES))
CLEAR_COMMAND = $(RM)  $(addprefix src/, $(OBJFILES)) $(TARGET)

.SILENT:

all: $(TARGET)

@ $(TARGET): $(addprefix src/, $(OBJFILES))
	$(COMMAND)

run:$(TARGET)
	@./$(TARGET)
	@$(CLEAR_COMMAND)

 
clean:
	$(CLEAR_COMMAND)