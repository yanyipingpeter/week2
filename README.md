# week2
简易聊天系统
=====================================================

### Development Enviroment
- Windows 2010

### Language 
- C++ 11
- CMake



### Program Description
该程序能够实现两个客户端的简易聊天，服务端会接收和转发相关信息。


### Developers
    Yiping Yan

### Instruction
- 1.下载文件后，使用CMake分别创建工程。得到两个sln文件（client.sln和server.sln）
- 2.打开sln文件分别编译，编译完成后在两个工程目录下分别会有一个Debug文件夹；
- 3.分别进入Debug文件夹，可以看到两个exe文件，分别是server.exe和client.exe
- 4.运行一个server.exe和两个client.exe.
- 5.server.exe将监听接入的客户端
- 6.两个客户端启动后，要先进行登录，目前仅支持两个客户，yyp和zt，密码分别是111和222；
- 7.登录完成后，一方发送send首先发起聊天，另一方输入其他以接受信息。务必一方发send，另一方发其他。
- 8.随后可以进行一来一回的聊天。一方发送消息之后必须等回复才可以继续发送信息。
   
    


