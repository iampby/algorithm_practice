位图实现
---
实现了resize(重设大小)、set（标记）、clear（清除标记）、test（检测）。<br />
有2个版本位图，一个无符号64位为元素标记，一个有符号采用嵌套位图的方式实现。<br />
大部分操作采用位操作。经测试，对几十万的数据标记，清除，花费为毫秒级别。