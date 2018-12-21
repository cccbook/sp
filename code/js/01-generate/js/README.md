# generate

## genexp

```
$ node genexp
4-5
6-4+7
8*(4-(6))+7-4
6
7
2+(7)
6+(6)+((3*2*(0)))
5-((((1)*3))-0)+1+(8-1)+5+7
(((0+2))-7)
8-((((8)*0)*3)+5*1)
```

## genAssign

```
$ node genAssign
c=2+8*3
z=2*5+0*3
b=6+(3*5+8*0)
z=6
x=8*8
x=(5+(5+6)*1)
c=(7*7+7*5)
c=3*2+(7*8+8*8)*4
y=0*(2+5*8)+7*0
x=(3+(0*6+(5+0*(3+7*6))*((((5*(3*0)))*8)*8+((2+5))*7))*(5+8))
```

## genWhile

```
$ node genWhile

while (x) {
  while (x*(6*2)+4) {
    while (a) {
      while (9*y+(0*1+2*3)*b) {
        z=8*x
        while (a+x*((c+6)*4+5*(((9))+((x)*1+3*x)*c))) {
          b=a+b*x
        }
      }
    }
    b=y*5
  }
}
x=1*(c*a+6)+6
x=4
```

## genCall

```
$ node genCall

b=(5*x)
z=apply(5*a)

$ node genCall

while ((x+y*1)*4+c) {
  b=((7*(y*0)+8)*c+6*0)
  a=4*(((2+c*y)+6))
  a=c+x*x
}
a=((1*0))*7+2*8
x=9*3
c=get(y1)
```

## genFunction.js

```
$ node genFunction

function apply(z,b,c) {
  b=(5*6)
  c=8
  y=(b*0)+0
  x=set(1*x+5(3)*x1c*((x))+(6*(8))*5((5)*8))
}

$ node genFunction

function apply(y,y,z,b) {
  y=9*(9*x+0*(2))
  y=set(787*a+8(3*0+0*b)*(3*6)+43+(c*1+5)*2)
}

$ node genFunction

function set(y) {
  y=a*3
  c=toString(2*06+30*(y*8+4)ac*x+(a*1+(6*x)*8)0y*5+(c*1+2*x)*y)
}

$ node genFunction
function set(y,c,z) {
  while ((1*((5+3*(((7+5*3)*(c))*6+b*9))+(b)*(((8+(8)*4)*(4+(5*7)*b)))))*7) {
    while (7) {
      y=b+2*a
      c=4*b
      z=toString(((7*0)+9)+cy*9(6+4))
    }
    a=parse(((1*8+2))+2*13*(y*(a))7+((a)*(x+x)+(a)))
    z=(4+((4)+(((a*0)*8))*2))*8+3
  }
  x=2
}
```

## genProgram.js

```
function apply(x,b) {
  y=((6*8))*7+((x*(x)))
  c=set(1)
  while ((((0+x*((6*((4*2+0*7)*3+4))))*(b))*9)*(2)) {
    b=c*2
    while (6) {
      while (y) {
        z=x
        while (5*a) {
          z=(5)*c
          b=0
        }
      }
      c=x+1
    }
    b=9
  }
}
function print(b,x,b) {
  z=(((((x)*(4+y)+x*7)*8+x*((b)+2))*9+x)+5)*0
  c=run(8*1)
  while (3*((y*5+(y)))+y) {
    a=4*((7*0))+3*(6+7)
    b=9
    y=6
    c=3
  }
}
function get(b,x,z,c) {
  b=y+(3)*(9)
  while (0+(7)) {
    b=3+3
    a=a+y
  }
}
function set(b) {
  x=b*x
  a=(8)
  while ((5+(b))*8+4*7) {
    a=0
    c=print(0)
  }
  z=run(((((2)))*0+((((7)))+8*(x)))*y)
}

```