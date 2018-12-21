# CPU0 工具鏈

## as0.js -- 組譯器

```
$ node as0 sum.as0 sum.obj0
Assembler:asmFile=sum.as0 objFile=sum.obj0
===============Assemble=============
[ '        LD     R1, sum      ; R1 = sum = 0',
  '        LD     R2, i        ; R2 = i = 1',
  '        LDI    R3, 10       ; R3 = 10',
  'FOR:    CMP    R2, R3       ; if (R2 > R3)',
  '        JGT    EXIT         ;   goto EXIT',
  '        ADD    R1, R1, R2   ; R1 = R1 + R2 (sum = sum + i)',
  '        ADDI   R2, R2, 1    ; R2 = R2 + 1  ( i  = i + 1)',
  '        JMP    FOR          ; goto FOR',
  'EXIT:   ST     R1, sum      ; sum = R1',
  '        ST     R2, i        ; i = R2',
  '        LD     R9, msgptr   ; R9= pointer(msg) = &msg',
  '        SWI    3            ; SWI 3 : 印出 R9 (=&msg) 中的字串',
  '        MOV    R9, R1       ; R9 = R1 = sum',
  '        SWI    4            ; SWI 2 : 印出 R9 (=R1=sum) 中的整數',
  '        RET                 ; return 返回上一層呼叫函數',
  'i:      RESW   1            ; int i',
  'sum:    WORD   0            ; int sum=0',
  'msg:    BYTE   "1+...+10=", 0   ; char *msg = "sum="',
  'msgptr: WORD   msg          ; char &msgptr = &msg' ]
=================PASS1================
0000          LD       R1,sum           L 00
0004          LD       R2,i             L 00
0008          LDI      R3,10            L 08
000C FOR      CMP      R2,R3            A 10
0010          JGT      EXIT             J 23
0014          ADD      R1,R1,R2         A 13
0018          ADDI     R2,R2,1          A 1B
001C          JMP      FOR              J 26
0020 EXIT     ST       R1,sum           L 01
0024          ST       R2,i             L 01
0028          LD       R9,msgptr        L 00
002C          SWI      3                J 2A
0030          MOV      R9,R1            A 12
0034          SWI      4                J 2A
0038          RET                       J 2C
003C i        RESW     1                D F0
0040 sum      WORD     0                D F2
0044 msg      BYTE     "1+...+10=",0    D F3
004E msgptr   WORD     msg              D F2
===============SYMBOL TABLE=========
FOR      000C
EXIT     0020
i        003C
sum      0040
msg      0044
msgptr   004E
=============PASS2==============
0000          LD       R1,sum           L 00 001F003C
0004          LD       R2,i             L 00 002F0034
0008          LDI      R3,10            L 08 0830000A
000C FOR      CMP      R2,R3            A 10 10230000
0010          JGT      EXIT             J 23 2300000C
0014          ADD      R1,R1,R2         A 13 13112000
0018          ADDI     R2,R2,1          A 1B 1B220001
001C          JMP      FOR              J 26 26FFFFEC
0020 EXIT     ST       R1,sum           L 01 011F001C
0024          ST       R2,i             L 01 012F0014
0028          LD       R9,msgptr        L 00 009F0022
002C          SWI      3                J 2A 2A000003
0030          MOV      R9,R1            A 12 12910000
0034          SWI      4                J 2A 2A000004
0038          RET                       J 2C 2C000000
003C i        RESW     1                D F0 00000000
0040 sum      WORD     0                D F2 00000000
0044 msg      BYTE     "1+...+10=",0    D F3 312B2E2E2E2B31303D00
004E msgptr   WORD     msg              D F2 00000044
=================SAVE OBJ FILE================

00 :  001F003C 002F0034 0830000A 10230000
10 :  2300000C 13112000 1B220001 26FFFFEC
20 :  011F001C 012F0014 009F0022 2A000003
30 :  12910000 2A000004 2C000000 00000000
40 :  00000000 312B2E2E 2E2B3130 3D000000
50 :  0044
```

## vm0.js

```
$ node vm0 sum.obj0
1+...+10=55
```

## j0c.js



```
$ node j0c test.j0 | out-file "test.ir0" -encoding utf8 
// 在 powerShell 中預設會輸出 UTF-16，所以得加 UTF8，不過這樣還是會有問題，所以還是改在 cmd 下用下列指令比較適合。
// 所以 Windows 中請在 cmd 中執行，不要用 PowerShell 
$ node j0c test.j0 > test.ir0 // 輸出到 test.ir0 中間檔
$ node j0c test.j0
        arg     10
        call    T1      sum
        =       s       T1
sum     function
        param   n
        =       s       0
        =       i       1
L1
        <=      T2      i       10
        if0     T2      L2
        +       T3      s       i
        =       s       T3
        ++      i
        goto    L1
L2
        return  s
        endf
        arg     3
        arg     5
        call    T4      max
        =       m       T4
max     function
        param   a
        param   b
        >       T5      a       b
        if0     T5      L3
        return  a
L3
        return  b
        endf
total   function
        param   a
        =       s       0
        =       i       0
L4      length  T6      a
        <       T7      i       T6
        if0     T7      L5
        []      T8      a       i
        +       T9      s       T8
        =       s       T9
        goto    L4
L5
        return  s
        endf
        array   T10
        apush   T10     1
        apush   T10     3
        apush   T10     7
        apush   T10     2
        apush   T10     6
        =       a       T10
        arg     a
        call    T11     total
        =       t       T11
        table   T12
        map     T12     e       "dog"
        map     T12     c       "狗"
        =       word    T12
```

## ir2as0

```
$ node ir2as0 test.ir0
//      arg     10
        LD      R1      10
        PUSH    R1
//      call    T1      sum
        CALL    sum
        ST      R1      T1
//      =       s       T1
        LD      R1      T1
        ST      R1      s
// sum  function
sum
//      param   n
        POP     R1
        ST      R1      n
//      =       s       0
        LD      R1      0
        ST      R1      s
//      =       i       1
        LD      R1      1
        ST      R1      i
// L1
L1
//      <=      T2      i       10
        LD      R1      i
        LD      R2      10
        CMP     R1      R2
        JLE     CSET0
        LDI     R1      1
        JMP     CEXIT0
CSET0   LDI     R1      0
CEXIT0  ST      R1      T2
//      if0     T2      L2
        CMP     R0      T2
        JEQ     L2
//      +       T3      s       i
        LD      R1      s
        LD      R2      i
        ADD     R3      R1      R2
        ST      R3      T3
//      =       s       T3
        LD      R1      T3
        ST      R1      s
//      ++      i
        LDI     R1      1
        LD      R2      i
        ADD     R2      R1      R2
        ST      R2      i       undefined
//      goto    L1
        JMP     L1
// L2
L2
//      return  s
        LD      R1      s
        RET
//      endf
//      arg     3
        LD      R1      3
        PUSH    R1
//      arg     5
        LD      R1      5
        PUSH    R1
//      call    T4      max
        CALL    max
        ST      R1      T4
//      =       m       T4
        LD      R1      T4
        ST      R1      m
// max  function
max
//      param   a
        POP     R1
        ST      R1      a
//      param   b
        POP     R1
        ST      R1      b
//      >       T5      a       b
        LD      R1      a
        LD      R2      b
        CMP     R1      R2
        JGT     CSET0
        LDI     R1      1
        JMP     CEXIT0
CSET0   LDI     R1      0
CEXIT0  ST      R1      T5
//      if0     T5      L3
        CMP     R0      T5
        JEQ     L3
//      return  a
        LD      R1      a
        RET
// L3
L3
//      return  b
        LD      R1      b
        RET
//      endf
// total        function
total
//      param   a
        POP     R1
        ST      R1      a
//      =       s       0
        LD      R1      0
        ST      R1      s
//      =       i       0
        LD      R1      0
        ST      R1      i
// L4   length  T6      a
L4
        LD      R1      a
        CALL    ALEN
        ST      R1      T6
//      <       T7      i       T6
        LD      R1      i
        LD      R2      T6
        CMP     R1      R2
        JLT     CSET0
        LDI     R1      1
        JMP     CEXIT0
CSET0   LDI     R1      0
CEXIT0  ST      R1      T7
//      if0     T7      L5
        CMP     R0      T7
        JEQ     L5
//      []      T8      a       i
        LD      R1      a
        LD      R2      i
        CALL    AGET
        ST      R1      T8
//      +       T9      s       T8
        LD      R1      s
        LD      R2      T8
        ADD     R3      R1      R2
        ST      R3      T9
//      =       s       T9
        LD      R1      T9
        ST      R1      s
//      goto    L4
        JMP     L4
// L5
L5
//      return  s
        LD      R1      s
        RET
//      endf
//      array   T10
        LD      R1      T10
        CALL    ARRAY
//      apush   T10     1
        LD      R1      T10
        LD      R2      1
        CALL    APUSH
//      apush   T10     3
        LD      R1      T10
        LD      R2      3
        CALL    APUSH
//      apush   T10     7
        LD      R1      T10
        LD      R2      7
        CALL    APUSH
//      apush   T10     2
        LD      R1      T10
        LD      R2      2
        CALL    APUSH
//      apush   T10     6
        LD      R1      T10
        LD      R2      6
        CALL    APUSH
//      =       a       T10
        LD      R1      T10
        ST      R1      a
//      arg     a
        LD      R1      a
        PUSH    R1
//      call    T11     total
        CALL    total
        ST      R1      T11
//      =       t       T11
        LD      R1      T11
        ST      R1      t
//      table   T12
        LD      R1      T12
        CALL    TABLE
//      map     T12     e       "dog"
        LD      R1      T12
        LD      R2      e
        LD      R3      "dog"
        CALL    TMAP
//      map     T12     c       "狗"
        LD      R1      T12
        LD      R2      c
        LD      R3      "狗"
        CALL    TMAP
//      =       word    T12
        LD      R1      T12
        ST      R1      word

```