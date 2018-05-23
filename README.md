# Naive_Compiler

为了最终的编译原理大作业写的一个，<br>
非常奶衣服的一个，功能十分受限的编译器。<br>
其作用仅限于可以进行变量定义，赋值，计算，和输出。<br>

# 指令集（暂定）

<b>var x;</b>：定义变量x（浮点型），初值默认为0。也可以写为<b>var x = [expression];</b>的形式<br>
<b>x = [expression];</b>：将表达式<b>[expression]</b>的值赋值给<b>x</b>，表达式仅支持四则运算<br>
<b>print [expression];</b>：输出表达式[expression]的值<br>

# 开发日志

<b>2018/05/23</b>：已完成词法分析部分，并完成LR(1)分析器产生器中FIRST&FOLLOW集的生成。<br>
<b>2018/05/22</b>：吹下牛逼，开始看书。<br>
