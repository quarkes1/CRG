# MALOEA

## 项目介绍

![intro1](/intro_pic/intro1.png)

### 本项目是模仿Malody（和部分Arcaea元素）制作的4k纯控制台音游，完全支持Malody的谱面

## 目前需要填的坑

- 设置判定难度，键位绑定 ，流速等调节
- 局域网linkplay

### 本游戏已经导入了部分Malody的初始谱面。若下载了Malody <a href="https://m.mugzone.net/wiki/1?lang=sc">官网下载</a> ，可以直接导入游戏内的谱面

## 谱面导入教程

- 在 /chart 下新建一个文件夹用来放待导入的文件
- 打开Malody所在目录，找到 /beatmap 文件夹并打开 ![guide1](/intro_pic/guide1.png)
- 若已经进行过游玩 ， Malody 会自动把 msz压缩文件解压，得到谱面文件夹，打开对应的文件夹 ![guide2](/intro_pic/guide2.png)
- 找到其中以.mc为后缀的为谱面文件(实质上是json)，以.ogg为后缀的音频文件，将其复制到 chart/(你新建的谱面文件夹名)/ 内 ![guide3](/intro_pic/guide3.png)
- 由于本程序不支持Malody的ogg vorbis , 因此需要将.ogg文件转为更通用的.wav格式 可以去 <a href = "https://www.freeconvert.com/zh/ogg-to-wav">这里</a>进行转换。