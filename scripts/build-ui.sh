if [ ! -d "./dest" ]
then
    mkdir dest;
fi


# TODO find better way to compile everything
g++ -c -o dest/tmp.o src/ui/main.cpp

g++ dest/tmp.o -o dest/ui.o -lsfml-graphics -lsfml-window -lsfml-system

rm dest/tmp.o