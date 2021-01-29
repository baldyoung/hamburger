
/*
select 选择题
edit 简答题
*/

var QuestionJosn=[
{
	answerType : "select",
	questionId : "1",
	questionTitle : "关于mysql的描述正确的是？",
	questionItems :"mysql是一个关系型数据库;mysql是一个纯文本数据库;mysql是一个只能连接数据库的客户端;mysql啥也不是"
	
}, {
	answerType : "select",
	questionId : "2",
	questionTitle : "下面哪个不是数据库软件？",
	questionItems :"mysql;oracle;SQL Server;Tomcat"
	
}, {
	answerType : "select",
	questionId : "3",
	questionTitle : "关于数据库的描述正确的是？",
	questionItems :"数据库是一个图形编辑软件;数据库是一个音频播放软件;数据库是一个文本编辑软件;数据库是一个数据管理软件"
	
}, {
	answerType : "select",
	questionId : "4",
	questionTitle : "mysql中如果需要对数据进行查询，需要使用下面哪个关键字？",
	questionItems :"create;select;insert;chaxun;alter"
	
}, {
	answerType : "select",
	questionId : "5",
	questionTitle : "一下哪个SQL代码可以实现在MySQL中创建一个数据库？",
	questionItems :"create table A;create table databaseA;create database B;create databases C"
	
}, {
	answerType : "select",
	questionId : "6",
	questionTitle : "alter table的作用是？",
	questionItems :"修改数据库;删除数据库;删除表;修改表结构"
	
}, {
	answerType : "select",
	questionId : "7",
	questionTitle : "如果需要对查询结果进行排序一定会涉及下面的哪个关键字？",
	questionItems :"where;group;paixu;order"
	
}, {
	answerType : "select",
	questionId : "8",
	questionTitle : "下面哪个能获取当前用户所能操作的所有数据库的名字？",
	questionItems :"select Name from shujuku;show tables;show databases;show shujuku"
	
}, {
	answerType : "select",
	questionId : "9",
	questionTitle : "如果需要获取一个int字段所有值的平均值，应该使用下面哪个函数？",
	questionItems :"max();count();avg();sum();min()"
	
}, {
	answerType : "select",
	questionId : "10",
	questionTitle : "如何将student表中的studentAge字段的值全部改成15？",
	questionItems :"update student set studentAge = 15;update from student set studentAge = 15;update studentAge=15 from student;update studentAge=15"
	
}, {
	answerType : "select",
	questionId : "11",
	questionTitle : "如何启动mysql服务？",
	questionItems :"net mysql;net --install mysql;net start mysql;start mysql"
	
}, {
	answerType : "select",
	questionId : "12",
	questionTitle : "如何将student表中的studentName和studentAge字段的数据导出到文件studentData.txt？",
	questionItems :"select * from student into studentData.txt;select studentName, studentAge from student into outfile studentData.txt;select studentName, studentAge into outfile studentData.txt;select studentName from student into outfile studentData.txt"
	
}, {
	answerType : "select",
	questionId : "13",
	questionTitle : "alter table语法一般用于什么作用？",
	questionItems :"修改表数据;修改数据库名称;删除表;修改表结构"
	
}, {
	answerType : "select",
	questionId : "14",
	questionTitle : "create user 'jack'@'localhost' identified by '123456'的作用是？",
	questionItems :"创建一个可以远程登录的用户账号;创建一个只能进行本地登录的用户账号;创建一个叫jack的表;创建一个叫jack的数据库"
	
}, {
	answerType : "select",
	questionId : "15",
	questionTitle : "delete from student where studentAge is null的作用是？",
	questionItems :"删除student表中studentAge字段为空的数据;删除student表中的所有数据;删除studentAge表中的student数据;将student中的数据转移到studentAge中"
	
}, {
	answerType : "select",
	questionId : "16",
	questionTitle : "查询时如果需要对数据进行分页，一定会使用下面哪个关键字？",
	questionItems :"group;order;limit;drop"
	
}, {
	answerType : "select",
	questionId : "17",
	questionTitle : "mysql中删除一张表需要使用下面哪个关键字？",
	questionItems :"delete;drop;select;alter"
	
}, {
	answerType : "select",
	questionId : "18",
	questionTitle : "关于多表查询的说法正确的是？",
	questionItems :"mysql中无法实现多表查询;多表查询需要使用limit;多表查询一定要使用join;多表查询是将多张表进行逻辑之间的关联然后查询"
	
}, {
	answerType : "select",
	questionId : "19",
	questionTitle : "mysql -h localhost -u root -p mysql这条命令的作用是？",
	questionItems :"创建数据库;连接到数据库;安装数据库;注册数据库"
	
}, {
	answerType : "select",
	questionId : "20",
	questionTitle : "如果需要对数据进行模糊查询需要使用下面哪个关键字？",
	questionItems :"order;group;outfile;like"
	
}, {
	answerType : "select",
	questionId : "21",
	questionTitle : "where只能用在条件查询中？",
	questionItems :"对;错"
	
}, {
	answerType : "select",
	questionId : "22",
	questionTitle : "连接数据库之前一定要确保目标数据库已经开启了？",
	questionItems :"对;错"
	
}, {
	answerType : "select",
	questionId : "23",
	questionTitle : "use 关键字的作用是切换到指定数据库？",
	questionItems :"对;错"
	
}, {
	answerType : "select",
	questionId : "24",
	questionTitle : "mysqld --install mysql是用来启动mysql服务的命令？",
	questionItems :"对;错"
	
}, {
	answerType : "select",
	questionId : "25",
	questionTitle : "where和order by不能同时使用？",
	questionItems :"对;错"
	
}, {
	answerType : "edit",
	questionId : "26",
	questionTitle : "查询student表中所有studentSex的值为 女 的数据"
	
}, {
	answerType : "edit",
	questionId : "27",
	questionTitle : "查询student表中studentAge的最大值"
}, {
	answerType : "edit",
	questionId : "28",
	questionTitle : "查询student中的studentName字段的值，并按照studentAge的值从大到小排序"
}, {
	answerType : "edit",
	questionId : "29",
	questionTitle : "删除student表中所有studentAge为空的数据"
}, {
	answerType : "edit",
	questionId : "30",
	questionTitle : "将student表中studentPhone字段改名为phoneNumber，并将类型改为varchar(20)"
}
]

