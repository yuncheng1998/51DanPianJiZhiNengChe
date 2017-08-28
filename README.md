﻿# 51单片机智能车

-----
**基于89C52RC单片机的智能小车**

**模块和传感器**
> * L289N驱动
> * HC-06从机蓝牙模块
> * HC-SR04超声波模块
> * HC-SR04光电反射传感器
> * HC-SR04红外反射传感器

**成品图**

![cmd-markdown-logo](http://chuantu.biz/t6/24/1503829376x2071761721.jpg)

**原理图**

![cmd-markdown-logo](http://chuantu.biz/t6/24/1503829900x2071761721.jpg)

-------
**功能**

1.寻迹
>* 上电后即开始运行，悬空时暂停，当有黑线时沿黑线前进，没有黑线时直行

2.红外避障
>* 上电后按下红色按钮，听到蜂鸣器Bi即开始运行

3.遥控
>* 上电后，显示为0为停止，l^l为前进，l_l为后退，l-左拐，-l右拐
遥控器(NEC协议)  ch为前进，|<<左拐，>||右拐，>>|停止，+后退

4.超声波避障
>* 上电后，按下红色按钮即开始，设定距离为约10cm避障

5.PWM调速
>* 修改heaad.h中的 push_val_left/right 的值，在1到20之间
