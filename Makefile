CC ?= gcc

BUILD := .build

INCLUDES := -Iinclude

CFLAGS := -O2 $(INCLUDES)
CFLAGS += $(shell cat warning_flags.txt)

SRC := $(shell find day* -type f -name "*.c")
OBJS := $(SRC:%.c=$(BUILD)/%.o)

.PHONY: all
all: $(SRC:%.c=%)

%: $(BUILD)/%.o
	$(CC) -o $@ $<

$(BUILD)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(OBJS:.o=.d)

.PHONY: clean
clean:
	$(RM) -r $(BUILD) day*

GEN_BUILD := $(BUILD)/generate_day.o
.PHONY: generate_day
generate_day: $(GEN_BUILD)
	$(CC) -o generate_day $(GEN_BUILD)

$(GEN_BUILD): generate_day.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c generate_day.c -o $@
