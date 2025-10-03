clang-20 -target riscv64 -march=rv64im -mcmodel=medany -Os -c import.c -o import.o
ld.lld-20 -o import.elf --oformat=elf -emit-relocs -T ../riscvm/lib/linker.ld --Map=import.map import.o
llvm-objcopy-20 -O binary  import.elf import.pre.bin
../riscvm/build-linux/riscvm  import.pre.bin