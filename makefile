#見返すとき用に機能を横に記載
CC = gcc #コンパイラの指定
CFLAGS_LDFLAGS = `sdl-config --cflags --libs` #SDLヘッダ用フラグ, SDLリンク用フラグ

TARGET = main #出力ファイル名
SRCS = main.c player.c #ソースファイル名

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS_LDFLAGS)

clean:
	rm -f $(TARGET)