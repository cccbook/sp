macro fset PI
  @PI
  D=A
  @16
  swi
mend

macro fput
  @18
  swi
mend

macro fadd f
  @19
  swi
  @PI
  D=A
mend

macro fmul f
 fmul f
 @f
 D=A
 @21
 swi
mend
