# 编译原理实验相关项目及文件

## 词法分析
### 相关问题
1. 对齐问题
 
 解决方案：C++有个库叫iomanip，里面提供了对齐函数，可用以下代码实现对齐：

    cout.fill(' '); //注意此处需为单引号，双引号会报错
    cout<<left<<setw(16)<<statement;
    cout<<" "<<code<<endl;
输出结果如下：
![部分输出结果截图]("./.1.png")

## 语法分析
### 相关问题
1. 文法中如何区分类似于下列产生式所对应的不同结果
> <说明语句>→<变量说明>│<函数说明>

解决方案： 多用一个指针，使之指向当前指针的下一个数据。判断该指针指向的数据对应的语句内容即可进行区分。

    void  ExplanatoryStatement()
    {	
        auto next_pointer = pointer + 1;   
        if ((*next_pointer).code == FUNCTION)    //下一条语句为FUNCTION时，对应于函数说明
            FunctionDescription();   //函数说明
        else
            VariableDescription();   //变量说明
    }



###### 有问题欢迎联系 邮箱：<2017060101001@std.uestc.edu.cn>