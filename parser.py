import sys
from llvmcpy import llvm

buffer = llvm.create_memory_buffer_with_contents_of_file('test.ll')
context = llvm.get_global_context()
module = context.parse_ir(buffer)
for function in module.iter_functions():
    for bb in function.iter_basic_blocks():
        for instruction in bb.iter_instructions():
            pass
