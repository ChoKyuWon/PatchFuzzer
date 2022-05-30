import re
import sys
import fnmatch
import os

def single_patch(name):
    f = open(name, "r")
    try: contents = f.read()
    except: return (0,0)
    splited_patch = contents.split('diff --git')
    header = splited_patch[0]
    try: modified = header.split('---')[1].split('\n')
    except: return (0,0)
    line_num = 0
    files = []
    for line in modified:
        if line.strip() == "" : continue
        line_num += 1
        file_name = re.search("[\w]*\.c", line.split('|')[0].strip())
        if file_name:
            s = line.split('|')[0].strip()
            if "create mode" in s: continue
            else: files.append((line_num,s))

    on_place = 0
    overestimate = 0

    keywords = ("if", "return", "else", "/*", "//", "define", "*s/")
    for line_num in files:

        try: single = splited_patch[line_num[0]]
        except: return (0,0)
        line_cut = single.split('\n')
        func = line_cut[4]
        f = re.findall("\s*(?:(?:inline|static)\s+){0,2}(?!else|typedef|return)\w+\s+\*?\s*(\w+)\s*\([^0]+\)?\s*;?", func)
        if f:
            on_place += 1
        else:
            try:
                target = open("./target/"+line_num[1], "r")
            except:
                continue
            comment = False
            for line in target.read().split("\n"):
                if "/*" in line: comment = True
                if "*/" in line: comment = False; continue
                if comment: continue
                __f = re.findall("\s*(?:(?:inline|static)\s+){0,2}(?!else|typedef|return)\w+\s+\*?\s*(\w+)\s*\([^0]+\)?\s*;?", line)
                if __f:
                    flag = False
                    for keyword in keywords:
                        if keyword in line:
                            flag = True
                    if not flag:
                        overestimate += 1
                        # print(line, __f)
    return on_place, overestimate

on = 0
off = 0

for file in os.listdir('.'):
    if fnmatch.fnmatch(file, '*.patch'):
        count = single_patch(file)
        if count[1] > 100:
            if ("header" in file) or ("copyright" in file): continue
        on += count[0]
        off += count[1]

print(on, off)