# Exercise 1: VM Obfuscation Basics

Change the working directory:

```sh
cd exercise_1
```

In this exercise we are going to explore the concept of VM obfuscation.

1. Build `minivm.cpp`:
   ```sh
   clang-20 -O3 -fno-slp-vectorize -std=c++17 minivm.cpp -o minivm
   ```
2. Run the VM (`./minivm 1 2 3 4`) and do the following exercises:
   - Extract the active VM bytecode (look at the source code).
   - How many registers does the VM have? `Response = 256`
   - Make a list of all the operations and what they do.

    ```c
    #define LABEL_PLACEHOLDER(index) OPCODE(0), 0x12, 0x34, 0x56, 0x78, index, 0x87, 0x65, 0x43, 0x21
    #define RET(op)                  OPCODE(1), op
    #define ADD(dst, op1, op2)       OPCODE(2), dst, op1, op2
    #define MOVIMM(dst, imm64)       OPCODE(3), dst, IMM64(imm64)
    #define CMP(dst, op1, op2)       OPCODE(4), dst, op1, op2
    #define JCC(cond, label)         OPCODE(5), cond, label
    #define XOR(dst, op1, op2)       OPCODE(6), dst, op1, op2
    #define OR(dst, op1, op2)        OPCODE(7), dst, op1, op2
    #define MUL(dst, op1, op2)       OPCODE(8), dst, op1, op2
    ```

   - What does the active VM bytecode do? Write it as C pseudocode.

    ```c
    int bc(int a, int b, int c, int d) {
        x = a | b
        y = c^d
        return x + y
    }
    ```

3. For this exercise you will write your own bytecode. Look at the commented-out example code to figure out how to do it.
   - Implement a function that adds the first two arguments together: `return a + b`
   - Implement a function that multiplies the first two arguments together: `return a * b`
   - Implement a function that implements: `return a - b`
   - Implement a function that implements: `return a == 42 ? 1337 : 0`

   ```c
    constexpr uint8_t bytecode1[] = {
        MOVIMM(REG(254), 42),
        CMP(REG(255), REG(0), REG(254)),
        JCC(REG(255), 0), // jumps to LABEL_PLACEHOLDER(0) if REG(255) != 0
        MOVIMM(REG(254), 0),
        RET(REG(254)),
        LABEL_PLACEHOLDER(0),
        MOVIMM(REG(254), 1337),
        RET(REG(254)),
    };
   ```

If you finish early, here are a few bonus exercises (not required):

1. Extend `minivm.cpp` so it becomes possible to implement `fib(n)` (iterative).
2. Implement the `fib(n)` function to verify your new opcodes.

Do these exercises for `minivm-tailcall.cpp` (make sure to recompile):

3. Analyze the `minivm` binary in you favorite disassembler/decompiler. Would it be difficult to write a disassembler for the VM bytecode if the opcodes were switched around?
4. Which C++ attribute is responsible for the `jmp reg` opcode at the end of the handler?
