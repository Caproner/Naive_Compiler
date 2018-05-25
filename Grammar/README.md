# 文法

其中终结符为小写，非终结符为大写。

``v``表示关键字``var``

``p``表示关键字``print``

``x``表示变量

``c``表示常量


```
S→vx
S→x=E
S→vx=E
S→pE
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
