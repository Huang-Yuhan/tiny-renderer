# Tiny Render

## 读取Model

在本次用到的Obj文件中格式比较简单

```obj
v -1 -1 -1
v  1 -1 -1
v  1 -1  1
v -1 -1  1

vt 0 0
vt 1 0
vt 1 1
vt 0 1

vn 0 1 0

f 3/3/1 2/2/1 1/1/1
f 4/4/1 3/3/1 1/1/1

```

- v a b c 表示一个顶点的坐标为(a,b,c)
- vt a b 表示UV坐标
- vn a b c 表示法向量
- f a1/b1/c1 a2/b2/c2 a3/b3/c3 表示面，a/b/c分别是顶点，UV，法向量的**索引**

## 摄像机

一个摄像机应该有以下参数

- 位置 : cameraPosition : vec3
- 方向 : cameraDirection : vec3
实际上是摄像机空间的z轴正方向
- 右轴 : cameraRight : vec3
实际上是摄像机空间的x轴正方向
- 上轴 : cameraUp : vec3
实际上是摄像机空间的y轴正方向

**注** : 我们使用的坐标系是右手系，y表示纵坐标

那么根据以上参数我们就可以得到LookAt矩阵

