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
###3 rosrun rqt_tf_tree rosrun rqt_tf_tree
###4 ros::spin()和ros::spinonce()
https://www.cnblogs.com/liu-fa/p/5925381.html
###5 action_name
https://docs.ros.org/api/actionlib/html/classactionlib_1_1SimpleActionClient.html#details
