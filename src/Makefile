CXX = g++
IDIR = ../include/
ODIR = ./obj
CXXFlAG = -I $(IDIR)
OpenGL = -lGL -lGLU -lglut -lGLEW
GTK = `pkg-config --cflags --libs gtk+-2.0`
_DEPS = vertex.h edge.h surface.h model_2d.h model_3d.h
SRC = vertex.cpp edge.cpp surface.cpp model_2d.cpp model_3d.cpp main.cpp
OBJ = $(patsubst %,$(ODIR)/%,$(SRC:.cpp=.o))
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c $< -o $@ $(CXXFlAG) $(GTK)

app : $(OBJ)
	$(CXX) $^ -o $@ $(CXXFlAG) $(OpenGL) $(GTK)

# ./obj/vertex.o: vertex.cpp $(DEPS)
# 	g++ -c $< -o $@ $(CXXFlAG)

# ./obj/edge.o: edge.cpp $(DEPS)
# 	g++ -c $< -o $@ $(CXXFlAG)

# ./obj/surface.o: surface.cpp $(DEPS)
# 	g++ -c $< -o $@ $(CXXFlAG)

# ./obj/model_2d.o: model_2d.cpp $(DEPS)
# 	g++ -c $< -o $@ $(CXXFlAG)

# ./obj/model_3d.o: model_3d.cpp $(DEPS)
# 	g++ -c $< -o $@ $(CXXFlAG)

# ./obj/main.o: main.cpp $(DEPS)
# 	g++ -c $< -o $@ $(CXXFlAG) $(OpenGL)

# app : $(OBJ)
# 	$(CXX) $^ -o $@

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o core
