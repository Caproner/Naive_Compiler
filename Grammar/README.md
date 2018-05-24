# 文法

<p>
其中终结符为小写，非终结符为大写。<br>
v表示关键字var<br>
p表示关键字print<br>
x表示变量<br>
c表示常量<br>
</p>

```
S→vx
S→x=E
S→vx=E
S→px
E→E+T
E→E-T
E→T
T→T*F
T→T/F
T→F
F→(E)
F→x
F→c
```