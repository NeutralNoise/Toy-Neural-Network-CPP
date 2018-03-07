# Toy-Neural-Network-CPP
Port of Coding Trains Neural Network from Java Script to C++.
It is implemented with header only files to make its a close to Coding Trains code as possible.

The main reason I did this was I really wanted to use lambdas and the way the code was build gave me this chance. I hope to convert to other examples at some point later.

# Compiling

### Linux:
To compile on linux you will need a compiler that supports c++11.

cd Toy-Neural-Network-CPP/examples

g++ -std=c++11 XOR.cpp -o xor

### Windows
On Windows the code will compile with Code::Blocks using w64-mingw I'm unsure about mingw but it should be fine. You will need to turn on -std=c++11 flag in the compiler options.

The code does not compile with Visual Studio 2013 but I think the compiler doesn't have the complete c++11 support in that version. A newer version (2015/2017) should be able to compile it fine.

All you have to do is create a new project and then add the cpp file in examples that you want to compile and then compile it and your done.
