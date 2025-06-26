#見返すとき用に機能を横に記載
CC = gcc #コンパイラの指定
CFLAGS_LDFLAGS = -lm -lSDL2 -lSDL2_image -lSDL2_ttf #SDLヘッダ用フラグ, SDLリンク用フラグ

TARGET = main #出力ファイル名
SRCS = main.c window.c subfunction.c handle.c enemy.c update_info.c#ソースファイル名

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS_LDFLAGS)

clean:
	rm -f $(TARGET)