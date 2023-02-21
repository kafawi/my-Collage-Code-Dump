#!/usr/bin/env python3
# author: Karl-Fabian Witte

from datetime import datetime
import argparse
import os
import os.path

# constans
C_SUFFIX = ('cpp', 'c', 'h', 'hpp')
DEF_TIME_STAMP = 'TIMESTAMP:'

# retuns the comment string of sorce code
def getSourceCommentStr(fpath):
    index = fpath.rfind('.', 0)
    commentStr = ''
    if index > 0:
        suffix = fpath[index+1:]
        for s in C_SUFFIX:
            if s == suffix:
                commentStr = '//'
            # other CommentStrTupel Check from other Sourcefamilys
    return commentStr

# generates a pettier string from a datetime object
def prettyStamp(prefix=DEF_TIME_STAMP, dt=datetime.now()):
    return prefix + ' ' + datetime.strftime(dt, '%Y-%m-%d %H:%M:%S')

# generates a utc to handel correct datetime object
def stamp(prefix=None, dt=datetime.utcnow()):
    if prefix:
        return prefix + str(dt)
    else:
        return dt

def intStamp(dt=datetime.utcnow() ):
    return datetime.strftime(dt, '%Y%m%d%H%M%S')


# Write a string (stamp) into a file at position with the tac
# or adds a new line, if tac is not found in file
# if line is passt, the file gets the timestamp insert
def writeTimeStamp(fpath, stamp, insert_line, tac=DEF_TIME_STAMP):
    with open(fpath, 'r') as file:
        lines = file.readlines()
    # find old Timestamp
    old_timestamp_idx = None
    for i, line in enumerate(lines):
        if line.find(tac) != -1:
            old_timestamp_idx = i
            break
    # get the right line to insert.
    if insert_line != None:
        if insert_line > len(lines):
            timestamp_idx = len(lines)
        else:
            timestamp_idx = insert_line
        # swapping
        if old_timestamp_idx != None:
            move_line(lines, old_timestamp_idx, timestamp_idx)
    else:
        if old_timestamp_idx != None:
            timestamp_idx = old_timestamp_idx
        else:
            timestamp_idx = len(lines)
    # insert or overwrite Timestamp
    if old_timestamp_idx != None:
        lines[timestamp_idx] = stamp + '\n'
    else:
        lines.insert(timestamp_idx, stamp + '\n')
    #store file with inserted timestamp
    with open(fpath, 'w') as file:
        file.writelines(lines)

def move_line(lines, old_idx, new_idx):
    if old_idx < new_idx:
        if new_idx == len(lines):
            lines.append('')
        lines[old_idx : new_idx]  = lines[old_idx+1: new_idx+1]
    elif new_idx < old_idx:
        lines[new_idx+1: old_idx+1]= lines[new_idx: old_idx]

def stamp_file(filename):
    if not os.path.isfile(filename):
       with open(filename, 'w'): pass
    commentStr = getSourceCommentStr(filename)
    prefix = commentStr + ' ' + DEF_TIME_STAMP
    stampstr = str(stamp(prefix))
    writeTimeStamp(filename, stampstr, 0)

# Rename your file
def renameFileWithStamp(fpath, stamp, prefix='', suffix=''):
    index = fpath.rfind('.', 0)
    if suffix == '':
        if index > 0:
            suffix = fpath[index:]
    if prefix == '':
        if index > 0:
            prefixPath= fpath[:index]
        else :
            prefixPath = fpath
        index = fpath.rfind('\\', 0)
        if index > 0:
            prefix = prefixPath[index+1:]
        else:
            prefix = prefixPath
    os.rename(fpath, prefix + stamp.strip() + suffix)

###############################################################################
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="writes a timestep into a file")
    parser.add_argument("file", type=str, \
        help="file to update/ include timestamp")
    parser.add_argument("line", type=int, nargs='?', \
        help="linenumber where to write the stamp")
    parser.add_argument("--rename", action="store_true", \
        help = "renames the file like <old_name>TIMESTAMP<extention>")
    args = parser.parse_args()
    fpath = args.file
    if args.rename:
        stampstr = stamp('')
        renameFileWithStamp(fpath, stampstr)
    else:
        insert_line = args.line
        commentStr = getSourceCommentStr(fpath)
        prefix = commentStr + ' ' + DEF_TIME_STAMP
        stampstr = intStamp(prefix)
        writeTimeStamp(fpath, stampstr, insert_line)

# nice to have
# - choose of the either rename file or stamp the inside the file
# - user define the suffix and the prefix of renamed file
