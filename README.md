# CGCenter
a compute graphics learning &amp; coding center

**纸上得来终觉浅，绝知此事要躬行。**

这是一个使用opengl实现的渲染器，用来实践学到的图形学知识。当前该项目刚刚开工，只是有一些规划中要实现的东西，可能会根据时间以及未来的兴趣爱好改变实现内容，希望能够坚持下去（一个flag）

目前规划中要实现的效果如下：

### 引擎基本功能：

- 加载模型
  - [x] obj    ——计划8月22日前完成
- 摄像机
  - [x] 可漫游摄像机  ——计划8月13日前完成
- 几何体
  - [ ] 球体 Sphere ——计划8月29日前完成
  - [x] 平面 Plane ——计划8月15日前完成
  - [ ] 三角网格 TriMesh ——计划8月22日前完成
- 材质
  - [ ] 玻璃 Glass
  - [ ] 镜子 Mirror
  - [ ] 漫反射 Diffuse
  - [ ] 金属工作流 Metal Workflow
  - [ ] 毛玻璃 Frosted Glass
- 光源
  - [ ] 点光源 pointLight    ——计划8月15日前完成
  - [ ] 面光源 AreaLight
  - [ ] 直接光 DirectionalLight  ——计划9月5日前完成
  - [ ] 聚光灯 SpotLight
- 渲染管线
  - [x] 正向渲染 forward rendering  ——计划8月15日前完成
  - [ ] 延迟渲染 deferred rendering ——计划9月5日前完成
  - [ ] 延迟光照 deferred lighting、light pre-pass
  - [ ] 延迟贴图 deferred texture

### 阴影 Shadow 

- [ ] CSM-hard  ——计划9月12日前完成
- [ ] shadow-bias
- [ ] PCSS
- [ ] VSM

### 全局光照 GI

- [ ] RSM
- [ ] LPV
- [ ] SSGI
- [ ] VXGI

### 环境光遮蔽 AO

- [ ] SSAO
- [ ] HBAO
- [ ] SSDO
- [ ] GTAO

### 环境光照 IBL

- [ ] split-sum
- [ ] PRT-diffuse
- [ ] PRT-glossy

### 后处理算法 postprocess
- [ ] bloom
- [ ] CAS
- [ ] DLSS

### 实时光线追踪



### GPU-Driven



### 虚拟纹理 Virtual Texture



### GPU 粒子



### 遮挡剔除

