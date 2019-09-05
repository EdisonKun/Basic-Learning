##1、关于roslaunch内容，
可以查看博客：https://blog.csdn.net/weixin_41995979/article/details/81784987
###1.1 ros::init从参数服务器中获取参数。
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
