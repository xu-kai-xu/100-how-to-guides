# 静态库与动态库

一切皆文件

库：函数的二进制实现

一切皆文件，库也是文件

动态库 & 静态库

动态库/共享库：运行时加载，会放在特定的位置，供大家来使用这些资源

静态库：编译时加载，自己写的资源，自己用，不会放在特定的位置

## 静态库

库名称：`libxx.a`

ar -cr libxx.a yyy.o zzz.o

发布到
头文件声明：/usr/local/include
库文件位置：/usr/local/lib

```
gcc -L/usr/local/lib -o main main.c -lxx
```

`-l` 链接选项，这个参数必须在最后，有依赖【当多个库之间存在依赖关系时】

> 当有多个库存在依赖关系时，被依赖的库，需要放在后面。

## 动态库

`ldd` 查看动态库依赖 【mac 无该命令】

库名称：`libxx.so`

```
gcc -shared -fpic -o libxx.so yyy.c zzz.c
```

`-shared` 生成动态库
`-fpic` 生成位置无关的代码

发布到
头文件声明：/usr/local/include
库文件位置：/usr/local/lib

在 `/etc/ld.so.conf` 中添加库文件路径 【mac 无该文件】

`/sbin/ldconfig` 重读   `/etc/ld.so.conf` 【mac 无该命令】



```
gcc -I/usr/local/include -L/usr/local/lib -o main main.c -lxx
```

`-I` 指定头文件路径
`-L` 指定库文件路径

> 如果有一个文件做成了同名的动态库和静态库，一定会首先链接动态库。所以，动态库和静态库一般不建议重名。

## 非root用户发布

```
cp xx.so ~/lib
export LD_LIBRARY_PATH=~/lib
```
