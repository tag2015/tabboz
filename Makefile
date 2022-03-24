tabboz:
	g++ -I/mingw64/include -mwindows -DWIN32 -DUSE_OPENGL32 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -o 'tabboz.exe' 'main.cpp' gui/GUITabboz.cpp gui/GUIScuola.cpp -mwindows /mingw64/lib/libfltk.a -lole32 -luuid -lcomctl32
