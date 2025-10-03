#include <stdint.h>

static __attribute((noinline)) uint64_t resolve_import(const char* module, const char* function)
{
    // asm volatile("ebreak"); // TODO: replace with scall
    register uint64_t a0 asm("a0") = (uint64_t)module;
    register uint64_t a1 asm("a1") = (uint64_t)function;
    register uint64_t a7 asm("a7") = 10105;
    asm volatile("scall" : "+r"(a0) : "r"(a1), "r"(a7) : "memory");
    return a0;
}

static __attribute((noinline)) uint64_t host_call(uint64_t fn, uint64_t args[13])
{
    // asm volatile("ebreak"); // TODO: replace with scall
    register uint64_t a0 asm("a0") = fn;
    register uint64_t a1 asm("a1") = (uint64_t)args;
    register uint64_t a7 asm("a7") = 20000;
    asm volatile("scall" : "+r"(a0) : "r"(a1), "r"(a7) : "memory");
    return a0;
}

static __attribute((noinline)) uint64_t exit(int exit_code)
{
    register uint64_t a0 asm("a0") = exit_code;
    register uint64_t a1 asm("a1") = 0; // unused
    register uint64_t a7 asm("a7") = 10000;
    asm volatile("scall" : "+r"(a0) : "r"(a1), "r"(a7) : "memory");
    return a0;
}

void _start() __attribute__((section(".text.start")));

void _start()
{
    // TODO: call resolve_import and host_call here
    char     s[] = "Hello from RISC-V!";
    uint64_t fn  = resolve_import(0, "puts");
    uint64_t args[13];
    args[0]      = (uint64_t)(&s);
    uint64_t res = host_call(fn, args);
    exit(0);
    asm volatile("ebreak");
}
