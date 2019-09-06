run:
	g++ \
		-lm -std=c++11 \
		-o photoshop \
		src/image/*.cpp \
		src/main.cpp

clean:
	rm photoshop
