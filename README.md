字符串匹配算法实现
---
实现了kmp、bc、gs、bm、sunday、Karp-Rabin算法。<br />
经测试（n=rand()*rand(),m=rand()）：<br />
（1）debug:kr最快、其次gs、sunday、bm比kmp略胜。<br />
（2）realse:数据量中等时（千百万）全部差不多、当数据量越大时，kr性能越差、kmp越佳。<br />