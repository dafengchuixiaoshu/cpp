#!/usr/bin/python
# -*- coding: UTF-8 -*-

#########################################################################
# Author: coderqiuan@163.com
# Created on: 2016-11-04 18:08
#########################################################################

print "hello world!";
print "你好，世界！"

'''
日期与实践模
datetime模块
pytz模块
dateutil模块
'''

import time;
print "当前时间：", time.time();
print "本地时间为 :", time.localtime(time.time());
print "本地时间为 :", time.asctime(time.localtime(time.time()));
print time.strftime("%Y-%m-%d %H:%M:%S", time.localtime());
print time.strftime("%a %b %d %H:%M:%S %Y", time.localtime());
a = "Sat Mar 28 22:24:24 2016";
print time.mktime(time.strptime(a,"%a %b %d %H:%M:%S %Y"));

import calendar;
print calendar.month(2016, 1);

import math;
content = dir(math);
print content;

'''
PYTHONPATH: PYTHONPATH是Python搜索路径，默认我们import的模块都会从PYTHONPATH里面寻找。
PYTHONSTARTUP: Python启动后，先寻找PYTHONSTARTUP环境变量，然后执行此文件中变量指定的执行代码。
PYTHONCASEOK: 加入PYTHONCASEOK的环境变量, 就会使python导入模块的时候不区分大小写.
PYTHONHOME: 另一种模块搜索路径。它通常内嵌于的PYTHONSTARTUP或PYTHONPATH目录中，使得两个模块库更容易切换。

-d: 在解析时显示调试信息
-O: 生成优化代码 ( .pyo 文件 )
-S: 启动时不引入查找Python路径的位置
-V: 输出Python版本号
-X: 从 1.6版本之后基于内建的异常（仅仅用于字符串）已过时。
-c: cmd执行 Python 脚本，并将运行结果作为 cmd 字符串。
file: 在给定的python文件执行python脚本。

python中的标识符是区分大小写的。
以下划线开头的标识符是有特殊意义的。以单下划线开头（_foo）的代表不能直接访问的类属性，需通过类提供的接口进行访问，不能用"from xxx import *"而导入；
以双下划线开头的（__foo）代表类的私有成员；以双下划线开头和结尾的（__foo__）代表python里特殊方法专用的标识，如__init__（）代表类的构造函数。

IndentationError: unexpected indent错误是python编译器是在告诉你"Hi，老兄，你的文件里格式不对了，可能是tab和空格没对齐的问题"，所有python对格式要求非常严格。
IndentationError: unindent does not match any outer indentation level错误表明，你使用的缩进方式不一致，有的是tab键缩进，有的是空格缩进，改为一致即可。

关键字：and exec not assert finally or break for pass class from print continue global raise def if return del import try elif in while else is with except lambda yield

abs(x)返回数字的绝对值，如abs(-10) 返回 10
ceil(x)返回数字的上入整数，如math.ceil(4.1) 返回 5
cmp(x, y)如果 x < y 返回 -1, 如果 x == y 返回 0, 如果 x > y 返回 1
exp(x)返回e的x次幂(ex),如math.exp(1) 返回2.718281828459045
fabs(x)返回数字的绝对值，如math.fabs(-10) 返回10.0
floor(x)返回数字的下舍整数，如math.floor(4.9)返回 4
log(x)如math.log(math.e)返回1.0,math.log(100,10)返回2.0
log10(x)返回以10为基数的x的对数，如math.log10(100)返回 2.0
max(x1, x2,...)返回给定参数的最大值，参数可以为序列。
min(x1, x2,...)返回给定参数的最小值，参数可以为序列。
modf(x)返回x的整数部分与小数部分，两部分的数值符号与x相同，整数部分以浮点型表示。
pow(x, y)x**y 运算后的值。
round(x [,n])返回浮点数x的四舍五入值，如给出n值，则代表舍入到小数点后的位数。
sqrt(x)返回数字x的平方根，数字可以为负数，返回类型为实数，如math.sqrt(4)返回 2+0j

choice(seq)从序列的元素中随机挑选一个元素，比如random.choice(range(10))，从0到9中随机挑选一个整数。
randrange ([start,] stop [,step])从指定范围内，按指定基数递增的集合中获取一个随机数，基数缺省值为1
random()随机生成下一个实数，它在[0,1)范围内。
seed([x])改变随机数生成器的种子seed。如果你不了解其原理，你不必特别去设定seed，Python会帮你选择seed。
shuffle(lst)将序列的所有元素随机排序
uniform(x, y)随机生成下一个实数，它在[x,y]范围内

acos(x)返回x的反余弦弧度值。
asin(x)返回x的反正弦弧度值。
atan(x)返回x的反正切弧度值。
atan2(y, x)返回给定的 X 及 Y 坐标值的反正切值。
cos(x)返回x的弧度的余弦值。
hypot(x, y)返回欧几里德范数 sqrt(x*x + y*y)。
sin(x)返回的x弧度的正弦值。
tan(x)返回x弧度的正切值。
degrees(x)将弧度转换为角度,如degrees(math.pi/2) ， 返回90.0
radians(x)将角度转换为弧度

dir()
globals()和locals()函数
根据调用地方的不同，globals()和locals()函数可被用来返回全局和局部命名空间里的名字。
如果在函数内部调用locals()，返回的是所有能在该函数里访问的命名。
如果在函数内部调用globals()，返回的是所有在该函数里能访问的全局名字。
两个函数的返回类型都是字典。所以名字们能用keys()函数摘取。
'''

'''
File 对象方法: file对象提供了操作文件的一系列方法。
OS 对象方法: 提供了处理文件及目录的一系列方法。
'''
# 打开一个文件
fo = open("foo.txt", "r+")
str = fo.read(10);
print "读取的字符串是 : ", str

# 查找当前位置
position = fo.tell();
print "当前文件位置 : ", position

# 把指针再次重新定位到文件开头
position = fo.seek(0, 0);
str = fo.read(10);
print "重新读取字符串 : ", str

fo.write( "www.runoob.com!\nVery good site!\n");

os.rename( "test1.txt", "test2.txt" );
# 删除一个已经存在的文件test2.txt
os.remove("test2.txt")

# 关闭打开的文件
fo.close()

import os
# 创建目录test
 os.mkdir("test")
# 将当前目录改为"/home/newdir"
 os.chdir("/home/newdir")
# 给出当前的目录
 os.getcwd()
# 删除”/tmp/test”目录
 os.rmdir( "/tmp/test"  )

