##1、关于roslaunch内容，
可以查看博客：https://blog.csdn.net/weixin_41995979/article/details/81784987
1.1 ros::init从参数服务器中获取参数。可以看get_param_from_rosparam.cpp
##2、gitpush:
git init
git add .
git commit -m "提交说明注释"
git remote add origin git@github.com:git的账号/learngit.git
本地第一次推送用-u
git push -u origin master
第一次推送失败可能是本地没有远程仓库的readme.md文件
git pull --rebase origin master
然后再继续推送
git push -u origin master
##3 rosrun rqt_tf_tree rosrun rqt_tf_tree
##4 ros::spin()和ros::spinonce()
https://www.cnblogs.com/liu-fa/p/5925381.html
##5 action_name
https://docs.ros.org/api/actionlib/html/classactionlib_1_1SimpleActionClient.html#details

##6、tf
在加载urdf时，各个关节的tf自动加载吗？
可以测试一下，rviz
Nope, robot_state_publisher

##7、ros_controllers
需要将基类中的虚函数在子类中实现，不然出现报错：
类似于：https://answers.ros.org/question/276638/rqt-custom-plugin-undefined-symbol/
没有这种类之类的
解决方式：https://www.youtube.com/watch?v=4xZKflNlJho

##8、realtime——tools
https://design.ros2.org/articles/realtime_background.html
