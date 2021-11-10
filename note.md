工程构建方式：

cd build

cmake .. -G "Visual Studio 16 2019" -A x64

记录几个小bug，assimp-vc142-mt.dll、glew32.dll和glfw3.dll是我自己编译的dll，容易和windows自带的dll冲突，所以需要单独把它们拷贝到可执行文件下面



一些小疑问：

怎么组织drawmesh的代码（例如想要绘制阴影时候的prog和正常绘制的program不同）

怎么组织各种不同的light和shader之间的关系

怎么把UI的参数透传下来，怎么去设计一个合理的UI类