# --- Configuration ---
BUILD   := build
TARGET  := $(BUILD)/Machina.exe
RARG    := hello

CC      := g++
# Added -fno-diagnostics-show-caret to CFLAGS for cleaner pragma output
CFLAGS  := -fno-diagnostics-show-caret -Wall
INCLUDE := 
LIB     := -L.
LIBS    := 

# --- Source & Objects ---
# This ensures .o files are tracked inside the $(BUILD) directory
SRC     := $(wildcard *.cpp)
OBJ     := $(SRC:%.cpp=$(BUILD)/%.o)

# --- Rules ---

all: $(BUILD) $(TARGET)
	@echo done linking and compiling

# Create build directory if it doesn't exist
$(BUILD):
	@if not exist "$(BUILD)" mkdir "$(BUILD)"

# Link the executable
$(TARGET): $(OBJ)
	@echo Linking $@
	@$(CC) -o $@ $(OBJ) $(LIB) $(LIBS)

# Compile .c files to .o files in the build directory
$(BUILD)/%.o: %.cpp
	@echo Compiling $<
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

# Clean up
clean:
	@if exist "$(BUILD)" rd /s /q "$(BUILD)"
	@del *.o > out
	@echo Cleaned $(BUILD) directory
	@cls

# Run the target
run: all
	@echo running $(TARGET)
	@echo -----------------------------------
	@./$(TARGET) $(RARG)
