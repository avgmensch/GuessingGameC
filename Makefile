# ===========================
# Command setup
# ===========================

CC = gcc
CFLAGS = -Wall -Werror -Os -MMD -MP -c
LD = gcc
LDFLAGS = -s

FMT = astyle
FMTFLAGS = \
	--style=allman\
	--max-code-length=100\
	--suffix=none\
	--verbose

RM = rm -rf
MKDIR = mkdir -p

# ===========================
# File and folders
# ===========================

MAKEFILE = Makefile
OUT_NAME = guessing_game

OUT_DIR = ./
SRC_DIR = source/
OBJ_DIR = .objects/

OUT_FILE  = $(OUT_DIR)$(OUT_NAME)$(if $(OS)==Windows_NT,.exe)
SRC_FILES = $(wildcard $(SRC_DIR)*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_FILES))
DEP_FILES = $(OBJ_FILES:%.o=%.d)

# ===========================
# Default target
# ===========================

bin: $(OUT_FILE)

$(OUT_FILE): $(OBJ_FILES) | $(OUT_DIR)
	$(LD) $(LDFLAGS) -o $@ $^

-include $(DEP_FILES)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(MAKEFILE) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# ===========================
# Other rules
# ===========================

$(OUT_DIR) $(SRC_DIR) $(OBJ_DIR):
	$(MKDIR) $@

# ===========================
# Phony targets
# ===========================

run: $(OUT_FILE)
	@./$<

fmt: $(SRC_FILES)
	$(FMT) $(FMTFLAGS) $^

clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(OUT_FILE)

.PHONY: run clean fmt