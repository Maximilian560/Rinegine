



libs = 		-L$(RineginePath)Rinegine/other/GLFW/64/lib-mingw-w64 	-L$(RineginePath)Rinegine/other/FreeType/64/lib 
#\-L$(RineginePath)Rinegine/other/OpenSSL
includes = 		-I$(RineginePath)Rinegine/other/GLFW/64/include	-I$(RineginePath)Rinegine/other/FreeType/64/include/freetype2	-I$(RineginePath)Rinegine/other/GLAD/include	-I$(RineginePath)Rinegine/other/stb_master  -I$(RineginePath)Rinegine/other/OpenAL/include
#\-I$(RineginePath)Rinegine/other/OpenSSL/include 

compilator = D:/mingw/mingw64/bin/


libs32 =	-L$(RineginePath)Rinegine/other/GLFW/32/lib-mingw-w64	-L$(RineginePath)Rinegine/other/FreeType/32/lib 
#\-L$(RineginePath)Rinegine/other/OpenSSL
includes32 = 	-I$(RineginePath)Rinegine/other/GLFW/32/include	-I$(RineginePath)Rinegine/other/FreeType/32/include/freetype2	-I$(RineginePath)Rinegine/other/GLAD/include		-I$(RineginePath)Rinegine/other/stb_master -I$(RineginePath)Rinegine/other/OpenAL/include
#\-I$(RineginePath)Rinegine/other/OpenSSL/include 
compilator32 = D:/mingw/mingw32/bin/

link=  -lglfw3 -lgdi32 -lglu32 -lopengl32 -lkernel32 -luser32 -lws2_32 -lfreetype -lwinmm

outputo32Rinegine = $(RineginePath)Rinegine/other/glad-x32.o
outputoRinegine = $(RineginePath)Rinegine/other/glad.o