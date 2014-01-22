CCFLAG = -pedantic -Wall -Werror -ggdb3 -std=gnu++98
OBJ = texture
SOURCE = texture.cpp

$(OBJ): $(SOURCE) Vec.h Ray.h Shape.h Texture.h Image.o ONB.o ImageTexture.o UVSphere.o
	g++ $(CCFLAG) -o $(OBJ) $(SOURCE) Image.o ONB.o ImageTexture.o UVSphere.o

Image.o:Image.cpp Vec.h Image.h
	g++ -c $(CCFLAG) Image.cpp

ONB.o: ONB.cpp
	g++ -c $(CCFLAG) ONB.cpp

ImageTexture.o: ImageTexture.cpp Image.h
	g++ -c $(CCFLAG) ImageTexture.cpp

UVSphere.o: UVSphere.cpp
	g++ -c $(CCFLAG) UVSphere.cpp

clean:
	rm *.o *~ $(OBJ)