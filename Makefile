run:
	g++ \
		-lm -std=c++11 \
		-o photoshop \
		src/image/*.cpp \
		src/main.cpp \
		-O2 -L/usr/X11R6/lib -lm -lpthread -lX11

clean:
	rm photoshop

windows:
  g++ -lm -o photoshop src/image/*.cpp src/main.cpp -O2 -lgdi32 && photoshop
