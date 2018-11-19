CC := clang++-6.0
CONFIG := llvm-config-6.0

all:
	$(CC) `$(CONFIG) --cxxflags --ldflags --libs --libfiles --system-libs`  parser.cpp AudioFile.cpp -I/usr/include/llvm-6.0/ -I/usr/include/llvm-c-6.0/ -o parser