###1、JointTrajectory
通过规划关节运动时间和经过的关节点，规划处关节运动曲线，并实现在特定时刻的运动位置、速度、加速度和力矩的反馈。

###2、 Footstep
设置每一步运动所采取的运动步态，三角行，梯形还是其他？设置腿部运动时抬脚速度，触地速度等参数。

###3、BaseAuto
bool BaseAuto::prepareComputation(const State& state, const Step& step, const StepQueue& queue, const AdapterBase& adapter)
为计算做准备，计算高度height_,落脚点footholdsInSupport_

##3、 Step
###3.1 Step
判断这个步骤是legmotion or basemotion， 以及相应运动状态，运动时长；

###3.2 StepQueue
对Step进行操作，包括起始step或者转换step，添加，跳过以及删除step

###3.3 StepParameters
设置步长中的一些参数，比如落脚点位置等参数；

3.4 StepComputer
计算,判断当前step的状态

###3.5 StepCompleter
没有搞懂这个这个类的作用，只有complete和setparameters

###3.6、CustomCommand
自定义命令

##4、executor
###4.1、State
主要设置机器人的各种状态，比如关节加速度等参数，凡是和机器人状态相关的参数，在此文件中均可以设置！

###4.2、StateBatch（状态的批处理）
关于机器人状态的处理，全部构成一个map，可以获取特定时刻机器人的状态，或者设置添加特定时刻机器人状态。

###4.3、AdaptorBase
机器人的坐标变换，通过输入坐标系与输出坐标系，获取相应的状态量在输出坐标系中的表达。
AdaptorBase是一个特备重要的类，其中定义的大部分为纯虚函数，在后续会有子类继承该类，你可以认为这个类相当于可以从adaptorgazebo/adaptordummy中获得机器人的实际状态或者仿真状态，以便与executor进行交互，完成一些状态设置和运算操作。
###4.4、StateBatchComputer（机器人状态的计算）
计算机器人当前运动的步骤id，计算支撑腿或者是摆动腿。？？？

###4.5、 Executor
bool Executor::resetStateWithRobot() 通过gazebo或者实际机器人的adaptor状态信息，更新state中所存储的机器人状态。
bool Executor::updateStateWithMeasurements() 同样通过adaptor更新机器人状态

###5、test_kp
5.1 在进行运算的时候，首先声明了state->quadrupedstate()->quadrupedkinematics()->load_urdf;
StepParameters(),只有几个结构体，比如footstepparameters，endeffectortargetparameters;
StepCompleter->stepparameters& adapter;
StepComputer->isDOne；
Executor->StepCompleter.initialize()->true;
Executor->State.initialize()->quadrupedstate.initialize()->jointpositions and posebasetoworld,etc.这也是为什么规划的角度始终显示0,1.57，-3.14的原因，始终输出的是这个角度；
Executor->adapter.setInternalDataFromState(state_),这个adapter将机器人的状态，也就是state.initialize()中完成初始化的状态写入到adapter中。
Executor->reset()->通过adapter获得各条腿的当前状态，controlsetup,设置关节角，写入到state中。
Stepconverter->adapter
5.2所以在完成executor.initialize()之后，完成了如下事情：
1、初始化了机器人的模型，加载了urdf，可以利用kdl进行运动学计算；
2、统一了机器人的状态，也就是adapter和state状态统一；

#一些需要注意的点
Q1：Executor中bool Executor::writeSupportLegs()
if (!queue_.active()) {
    for (const auto& limb : adapter_.getLimbs()) {
      state_.setSupportLeg(limb, !state_.isIgnoreContact(limb));
    }
    return true;
  }
忽略接触意味着这条腿是支撑腿？

Q2:![](assets/code-a8263afb.png)
这个preview、base以及gazebo含义是什么？adaptor针对的对象？base就是adaptor中adaptorbase，preview实物机器人，gazebo仿真adaptor?

Q3:![](assets/code-7cfdad83.png)
AdaptorBase没有被导出是一个pluginlib，为何能被加载，其次对应的包关系也不对？难道是继承关系？
Ans,基类不用被导出，但是需要声明，在plugin_description.xml中。

Q4: adapterGAZEBO he AdapterDummy这两个类有什么区别的？

Q5:代码中的是adaperDummy，但是起对应的类是notimplement?另外一个正逆运动学求解结果不一致。
Ans：好像是真的不一致，所设置的joints对最终的计算结果影响不大？，详细见Q7,另外这个AdapterDummy需要在src/adapterdummy中进行设置。

Q6:最终的adapter和kdl以及urdf文件如何连接到一起？
Ans：在quadrupedkinematics中一项LoadRobotDescriptionFromFile（）；
但是不需要从rosparam中进行加载吗？
在AdapterRosInterfaceBase::readRobotDescription();中进行了robotdescription加载；

Q7:为什么在test_kp文件中关节角不对？

Q8:preview_xxx，指的是可以在rviz中进行预览；那为什么没有加载rviz相关东西？大部分的是false,暂且先不管；
dummy，就是没有加载模型，怎么输入进去怎么反馈回来的

##关于gui界面的一些问题
在quadruped_locomotion/rqt_control_panel_plugin_widget.cpp中就是实现了以下功能：
![](assets/code-f53c8205.png)实际上是控制器的转换
另外
