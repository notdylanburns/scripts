GO_C := gccgo

CFLAGS := -O2 -Werror -Wall -Wextra
TARGET := sd

$(TARGET): strdir.go
	$(GO_C) $(CFLAGS) -o $@ $<

install:
	cp $(TARGET) /usr/local/bin/$(TARGET)

.PHONY: $(TARGET)