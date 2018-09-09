#include <llvm-c/Types.h>
#include "llvm/IR/Metadata.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Pass.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>

using namespace llvm;

int main(int argc, char const *argv[])
{
    SMDiagnostic Err;
    LLVMContext Context;
    std::unique_ptr<Module> Mod(parseIRFile("test.ll", Err, Context));

    for (Module::iterator f = Mod->begin(), fend = Mod->end(); f != fend; ++f)
    {
        for (Function::iterator b = f->begin(), be = f->end(); b != be; ++b)
        {

            for (BasicBlock::iterator it = b->begin(), ite = b->end(); it != ite; ++it)
            {
                Instruction *ii = &*it;

                if (ii->mayReadOrWriteMemory())
                {
                    std::cout << "Acesso a memória" << std::endl;
                }
            }
        }
    }

    return 0;
}
