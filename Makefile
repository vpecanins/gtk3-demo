CC:=gcc
BUILD_DIR:= build

GTK_FLAGS := $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS  := $(shell pkg-config --libs gtk+-3.0)

SRCFILES     := $(shell find -type f -name "*.c" -printf '%P\n')
SRCFILES_OBJ := $(patsubst %.c,%.o,$(SRCFILES))
OBJFILES     := $(addprefix $(BUILD_DIR)/, $(SRCFILES_OBJ))
DEPFILES     := $(patsubst %.o,%.d,$(OBJFILES))

INCLUDE_DIRS := ./

WARNINGS := -Wall -Wextra
            
CFLAGS := -g3 -std=gnu99 $(WARNINGS) $(GTK_FLAGS)
LIBS := -lg -lc -lstdc++ -lm -lgmodule-2.0 $(GTK_LIBS)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIRS) -MMD -MP -c $< $(LIBS) -o $@


.PHONY: all clean

all: $(BUILD_DIR) main

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPFILES)

main: $(OBJFILES)
	$(CC) $(CFLAGS) -rdynamic $^ $(LIBS) -o $@ 
	
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

print-%: ; @echo $*=$($*)

