# 编译原理实验相关项目及文件
## 相关说明
1. 文件夹

文件夹|说明
|:--:|:--:|
Output|输出文件
Src|代码文件（包括词法分析的两个输入文件）
Project|完整的VS2017项目
2. 可执行文件

   Output里输出的可执行文件执行时的指令格式为：

    `可执行文件名 输入文件名`
     （可执行文件名不包含后缀）

## 词法分析
### 相关问题
1. 对齐问题
 
 解决方案：C++有个库叫iomanip，里面提供了对齐函数，可用以下代码实现对齐：

    cout.fill(' '); //注意此处需为单引号，双引号会报错
    cout<<left<<setw(16)<<statement;
    cout<<" "<<code<<endl;


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
