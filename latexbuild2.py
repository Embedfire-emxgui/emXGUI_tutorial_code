# -*- coding: utf-8 -*-

import datetime, os, sys, shutil

name = "[野火]emXGUI应用开发实战—基于STM32"
#输出PDF文档 名称格式 type = 1：手册  type = 0：教程
type = 0

time = datetime.datetime.now().year * 10000 + datetime.datetime.now().month * 100 + datetime.datetime.now().day



if type == 1:
    pdfname_time = '[野火] ' + name + str(time) + '.pdf'
    pdfname = '[野火] ' + name + '.pdf'
else:
    pdfname_time = '[野火EmbedFire]《' + name + '》—' + str(time) + '.pdf'
    pdfname = '[野火EmbedFire]《' + name + '》' + '.pdf'

print(pdfname_time)
print(pdfname)

os.rename('_build/latex/output.pdf', '_build/latex/' + pdfname_time)
shutil.copy('_build/latex/' + pdfname_time, '_build/' + pdfname)


#-------------------------------------------------------------------------------#
old_str = '        <meta http-equiv="refresh" content="0; url=zh/latest/index.html" />\n'

f = open("_static/html/index.html", "r", encoding="utf-8") 
line = f.readline()
f_new = open("_build/index.html", "w", encoding="utf-8") 

while line:
    if line == old_str:
        line = '        <meta http-equiv="refresh" content="0; url=' + pdfname + '" />\n'
        print("change line: ",line)

    f_new.write(line)
    line = f.readline()

f.close()
f_new.close()
