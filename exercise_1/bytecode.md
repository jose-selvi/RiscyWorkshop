```c
constexpr uint8_t bytecode1[] = {
    OR(REG(4), REG(0), REG(1)),
    XOR(REG(5), REG(2), REG(3)),
    ADD(REG(6), REG(4), REG(5)),
    RET(REG(6)),
};
```

r4 = r0 || r1
r5 = r2 XOR r3
r6 = r4 + r5
ret r6