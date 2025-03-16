echo "Compiling..."

if [ "$1" == "ladder" ]; then
    g++ -o output ladder.cpp dijkstras.cpp ladder_main.cpp
else 
    g++ -o output dijkstras.cpp dijkstras_main.cpp
fi


if [ $? -eq 0 ]; then
    ./output
else
    echo "Error compiling."
fi