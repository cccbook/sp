# 機器架構

## 歷史觀點

### Stored Procedure

```
Today’s computers are built on two key principles:
1. Instructions are represented as numbers.
2. Programs are stored in memory to be read or written, just like data.
These principles lead to the stored-program concept
```

### 歷史上的計算機架構

1. accumulator : 計算結果預設存回累積器
    * EX: EDSAC, IBM701, PDP8, Intel 8008, Motorola 6800, 
2. register-memory : 允許一個運算元在記憶體中。
    * EX: IBM 360, DEC/VAX, Motorola 68000, Intel 80386, AMD 64
3. register-register (load-store) :  只能對暫存器進行運算指令，需用 load-store 先載入暫存器。
    * EX: CDC 6600, ARM, MIPS, SPARC, PowerPC, RISC-V

