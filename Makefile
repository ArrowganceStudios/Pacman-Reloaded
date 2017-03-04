CXX = $(CROSS)g++
PKG = $(CROSS)pkg-config
RM  = rm

ALLEGRO  = allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5
LDFLAGS  = $(LDFLAGS_CUSTOM) $$($(PKG) --libs $(ALLEGRO))
CPPFLAGS = $(CFLAGS_CUSTOM) $$($(PKG) --cflags $(ALLEGRO)) -std=c++11

SRCS = $(wildcard src/*.cpp)
OBJS = $(subst .cpp,.o,$(SRCS))
OUT  = pacman

.PHONY: all
all: $(OUT)

$(OUT): $(OBJS)
	$(CXX) -o pacman $(OBJS) $(LDFLAGS)

.PHONY: clean
clean:
	-$(RM) src/*.o main $(OUT)
