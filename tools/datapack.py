import json
import os
import sys
import hashlib

fs_dir = dict()
os.chdir(sys.argv[1])
for root, subdirs, files in os.walk("."):
    for f in files:
        fs_dir[f] = str(hashlib.md5(f.encode()).hexdigest())
        #os.rename(f, fs_dir[f])
print(fs_dir)