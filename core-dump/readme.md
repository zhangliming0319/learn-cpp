./build.sh

./a.out
产生core文件
gdb a.out path/to/core

1.不生成core文件:
```
ulimit -c 0
```

2.生成不限制大小的core文件：
```
ulimit -c unlimited
```

3.检查生成core文件的选项是否打开 :
```
ulimit -a
```

core dump文件的位置可以通过/proc/sys/kernel/core_pattern文件进行配置。你可以查看这个文件的内容以确定core dump文件的实际位置。例如，运行
```
cat /proc/sys/kernel/core_pattern
```
要修改/proc/sys/kernel/core_pattern文件，你需要使用sysctl命令，而不是直接将内容重定向到文件。请使用以下命令：
```
sudo sysctl -w kernel.core_pattern="/tmp/core.%e.%p"
```
这将设置core dump文件的位置和名称。请注意，这个设置在系统重启后会丢失。要永久保存这个配置，可以将相应的命令添加到/etc/sysctl.conf文件中，或创建一个新的/etc/sysctl.d/目录下的配置文件。例如，创建一个名为/etc/sysctl.d/50-coredump.conf的文件，其中包含以下内容：
```
kernel.core_pattern=/tmp/core.%e.%p
```
