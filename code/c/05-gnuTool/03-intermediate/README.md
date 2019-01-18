# Gcc 中間碼

## Gimple

```
PS D:\ccc\book\sp\code\c\05-gnuTool\03-rtl> gcc -c -fdump-tree-gimple add.c
PS D:\ccc\book\sp\code\c\05-gnuTool\03-rtl> cat .\add.c.004t.gimple
add (int a, int b)
{
  int D.1485;

  D.1485 = a + b;
  return D.1485;
}
```

## RTL

```
PS D:\ccc\book\sp\code\c\05-gnuTool\03-rtl> gcc -c -fdump-rtl-expand add.c

PS D:\ccc\book\sp\code\c\05-gnuTool\03-rtl> cat .\add.c.191r.expand

;; Function add (add, funcdef_no=0, decl_uid=1482, cgraph_uid=0, symbol_order=0)


;; Generating RTL for gimple basic block 2

;; Generating RTL for gimple basic block 3


try_optimize_cfg iteration 1

Merging block 3 into block 2...
Merged blocks 2 and 3.
Merged 2 and 3 without moving.
Merging block 4 into block 2...
Merged blocks 2 and 4.
Merged 2 and 4 without moving.
Removing jump 11.
Merging block 5 into block 2...
Merged blocks 2 and 5.
Merged 2 and 5 without moving.


try_optimize_cfg iteration 2



;;
;; Full RTL generated for this function:
;;
(note 1 0 3 NOTE_INSN_DELETED)
(note 3 1 2 2 [bb 2] NOTE_INSN_BASIC_BLOCK)
(note 2 3 5 2 NOTE_INSN_FUNCTION_BEG)
(insn 5 2 6 2 (set (reg:SI 89)
        (mem/c:SI (reg/f:SI 81 virtual-incoming-args) [0 a+0 S4 A32])) add.c:2 -1
     (nil))
(insn 6 5 7 2 (set (reg:SI 90)
        (mem/c:SI (plus:SI (reg/f:SI 81 virtual-incoming-args)
                (const_int 4 [0x4])) [0 b+0 S4 A32])) add.c:2 -1
     (nil))
(insn 7 6 10 2 (parallel [
            (set (reg:SI 87 [ D.1488 ])
                (plus:SI (reg:SI 89)
                    (reg:SI 90)))
            (clobber (reg:CC 17 flags))
        ]) add.c:2 -1
     (expr_list:REG_EQUAL (plus:SI (mem/c:SI (reg/f:SI 81 virtual-incoming-args) [0 a+0 S4 A32])
            (mem/c:SI (plus:SI (reg/f:SI 81 virtual-incoming-args)
                    (const_int 4 [0x4])) [0 b+0 S4 A32]))
        (nil)))
(insn 10 7 14 2 (set (reg:SI 88 [ <retval> ])
        (reg:SI 87 [ D.1488 ])) add.c:2 -1
     (nil))
(insn 14 10 15 2 (set (reg/i:SI 0 ax)
        (reg:SI 88 [ <retval> ])) add.c:3 -1
     (nil))
(insn 15 14 0 2 (use (reg/i:SI 0 ax)) add.c:3 -1
     (nil))
```

