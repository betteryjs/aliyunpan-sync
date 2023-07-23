# -*- coding: UTF-8 -*-
import json,os
import hashlib

import time
start=time.time()


def get_file_sha1(filepath):
    with open(filepath,'rb') as f:
        m = hashlib.sha1()

        while True:
            data = f.read(10240)
            if not data:
                break

            m.update(data)
    return m.hexdigest()
#返回空目录
def path_to_dict(path):
    d = {'name': os.path.basename(path)}
    if os.path.isdir(path):
        d['type'] = "directory"
        d['children'] = [path_to_dict(os.path.join(path,x)) for x in os.listdir(path)]
    else:
        d['type'] = "file"
    return d



#空目录不返回
def path_to_dict(path, my_string=None):
    d = {'name': os.path.basename(path)}
    if os.path.isdir(path):
        d['type'] = "directory"
        d['children'] = []
        paths = [os.path.join(path,x) for x in os.listdir(path)]
        for p in paths:
            c = path_to_dict(p, my_string)
            if c is not None:
                d['children'].append(c)
        if not d['children']:
            return None
    else:
        d['type'] = "file"
        d['abs_path']=path
        d['file_time']=os.stat(path).st_mtime
        # d["sha1"]=get_file_sha1(path)
        print(path)

    return d

d={}
def all_dir(path):
    if os.path.isdir(path):
        d[path]= True
        paths = [os.path.join(path,x) for x in os.listdir(path)]
        if paths is not None:
            for p in paths:
                all_dir(p)




    return d

path = "/home/yjs/CPP/aliyunpan-sync-xmake"

print(all_dir(path))

# print(json.dumps(path_to_dict(path),ensure_ascii=False, indent=2))
#
# with open("files.json", 'w') as file:
#     file.write(json.dumps(path_to_dict(path),ensure_ascii=False, indent=2))

with open("dirs.json", 'w') as file:
    file.write(json.dumps(all_dir(path),ensure_ascii=False, indent=2))
# print(json.dumps(path_to_dict(path),ensure_ascii=False, indent=2))

# print(os.stat("/home/yjs/CPP/aliyunpan-sync-xmake/src/main.cpp"))

# path = "/home/yjs/CPP/aliyunpan-sync-xmake/PVE_OSX_KVM.zip"
#
# print(get_file_sha1(path))
print(time.time()-start)