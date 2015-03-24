# coding=utf-8

import os

if __name__ == "__main__":
	rootpath = u'E:\\GitHub\\Six_beauty\\代码'
	if not os.path.isdir(rootpath):
		raise Exception,u'rootpath error'

	hfile = open("E:\\GitHub\\Six_beauty\\gitrm.bat","w+")
	hdirs = open("E:\\GitHub\\Six_beauty\\gitrmdir.bat","w+")
	hfile.write("E:\n")
	hdirs.write("E:\n")

	for root,dirs,files in os.walk(rootpath):
		for fileItem in files:
			filepath = os.path.join(root,fileItem)
			filedir,filename = os.path.split(filepath)
			_,filetype = os.path.splitext(filepath)
			if(filetype == ".sdf" or filetype == ".exe"):
				cmd = u'cd {0} && git rm --cached {1}'.format(filedir,filename)
				hfile.write(cmd.encode('gb2312'))
				hfile.write("\n")


		for dirItem in dirs:
			if(dirItem == "Debug"):
				dirpath = os.path.join(root,dirItem)
				dirDir,dirname = os.path.split(dirpath)
				cmd = u'cd {0} && git rm --cached -r {1}'.format(dirDir,dirname)
				hdirs.write(cmd.encode('gb2312'))
				hdirs.write("\n")

	hdirs.write('git commit -m "ignore test"\n')
	hfile.write('git commit -m "ignore test"\n')
	hfile.close()
	hdirs.close()


