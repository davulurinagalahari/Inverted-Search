CC = gcc
CFLAGS = -Wall
TARGET = output

SRC = main.c create_db.c display_db.c save_db.c search_db.c update_db.c validation.c

$(TARGET):
	$(CC) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
