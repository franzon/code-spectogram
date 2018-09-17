all:
	clang++ `llvm-config --cxxflags --ldflags --libs --libfiles --system-libs`  parser.cpp AudioFile.cpp -I/usr/include/llvm-6.0/ -I/usr/include/llvm-c-6.0/ -o parser