run:
	g++ \
		-lm \
		-o photoshop \
		src/image/*.cpp \
		src/main.cpp

clean:
	rm photoshop
