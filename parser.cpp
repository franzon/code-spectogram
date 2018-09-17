#include <llvm-c/Types.h>
#include "llvm/IR/Metadata.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Pass.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include "AudioFile.h"

using namespace llvm;

int countInstructions(std::shared_ptr<Module> Mod)
{
    int count = 0;

    for (Module::iterator f = Mod->begin(), fend = Mod->end(); f != fend; ++f)
    {
        for (Function::iterator b = f->begin(), be = f->end(); b != be; ++b)
        {
            for (BasicBlock::iterator it = b->begin(), ite = b->end(); it != ite; ++it)
            {
                count++;
            }
        }
    }
    return count;
}

int main(int argc, char const *argv[])
{
    SMDiagnostic Err;
    LLVMContext Context;
    std::shared_ptr<Module> Mod(parseIRFile("test.ll", Err, Context));

    AudioFile<double> audioFile;
    AudioFile<double>::AudioBuffer buffer;
    buffer.resize(1);

    int numInstructions = countInstructions(Mod);
    buffer[0].resize(numInstructions);

    for (size_t i = 0; i < numInstructions; i++)
    {
        buffer[0][i] = 0;
    }

    std::map<std::string, double> amplitude;
    amplitude["alloca"] = 0;
    amplitude["store"] = 0.1;
    amplitude["br"] = 0.2;
    amplitude["load"] = 0.3;
    amplitude["icmp"] = 0.4;
    amplitude["add"] = 0.5;
    amplitude["ret"] = 0.6;

    int idx = 0;

    for (Module::iterator f = Mod->begin(), fend = Mod->end(); f != fend; ++f)
    {
        for (Function::iterator b = f->begin(), be = f->end(); b != be; ++b)
        {

            for (BasicBlock::iterator it = b->begin(), ite = b->end(); it != ite; ++it)
            {
                Instruction *ii = &*it;

                if (amplitude.count(ii->getOpcodeName()))
                {
                    buffer[0][idx] = amplitude[ii->getOpcodeName()];
                }

                // if (ii->mayReadOrWriteMemory())
                // {
                //     buffer[0][idx] = 1;
                // }

                idx++;
            }
        }
    }

    audioFile.setAudioBuffer(buffer);
    audioFile.save("audio.wav");

    return 0;
}
