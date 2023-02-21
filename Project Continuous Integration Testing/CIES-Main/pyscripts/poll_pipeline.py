#!/usr/bin/env python3
"""Check, if TCAC Pipeline is successful terminated

if status == success: -> exit(0)
else if status == "failed" : -> exit(1)
else: -> exit(2)

script usage:
    python3 poll_pipeline.py project_id git_root git_branch token times

Keyword arguments:
project_id  -- gitlab project ID of CAC
git_root    -- path to git root directory
git_branch  -- branch name of polling git
token       -- access token that provides api level operations
times       -- how often to poll the pipeline status (one poll attac: 10 sec)
"""
__author__ = "kafawi"

import sys
from time import sleep
import argparse
import requests
from data_handler import CiesData

def get_pipeline_status(url, head, pid):
    """
    gets a pipeline's status

    Keyword arguments:
    url -- the active pipeline's URL
    head -- the pipeline's head
    pid -- the pipeline's ID
    """
    status = 'pending'
    PIPELINE_DATA = requests.get(url, headers=head).json()
    for i in range(0, 100):
        if i < len(PIPELINE_DATA):
            if PIPELINE_DATA[i]['id'] == pid:
                status = PIPELINE_DATA[i]['status']
                break
        else:
            break
    return status

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="polling pipeline status every 10 seconds")
    parser.add_argument("cac_id", type=str,
                        help="id in gitlab of desired project")
    parser.add_argument("cdr_id", type=str,
                        help="gitsha")
    parser.add_argument("git_root", type=str,
                        help="path to git root directory")
    parser.add_argument("git_branch", type=str,
                        help="branch of desire")
    parser.add_argument("token", type=str,
                        help="private token for gitlab api requests")
    parser.add_argument("times", type=int,
                        help="Max times polling?")
    parser.add_argument("gitsha", type=str, nargs="?",
                        help="gitsha")

    args = parser.parse_args()
    print("poll report to get Pipeline-id")
    ID = 0
    db = CiesData()
    for times in range(0, args.times):
        print(args.times-times, flush=True)
        sleep(30)
        report = db.get_report_by_gitsha_cdr_id(args.gitsha, args.cdr_id)
        if report:
            ID = report["PIP_ID"]
            print("found report")
            print(ID)
            break
        if times == (args.times - 1):
            print("no report found", flush=True)
            sleep(1)
            sys.exit(3)
    URL = "https://gitlab.informatik.haw-hamburg.de/api/v4/projects/"
    URL += args.cac_id + "/pipelines"
    HEADERS = {"private-token" : args.token.strip()}
    #with open(args.git_root.strip() + "/.git/refs/heads/" + args.git_branch.strip()) as headref:
    #    SHA = headref.read().strip() # remove  and "\n"
    #data = requests.get(URL, headers=HEADERS).json()
    #ID =data[0]['id']
    print("polling countdown",  flush=True)

_PIPELINE_STATUS_KEY =  "status"
    _PIPELINE_STATUS_PENDING = "pending"
    _PIPELINE_STATUS_SUCCESS = "success"
    _PIPELINE_STATUS_FAILED = "failed"
    _PIPELINE_STATUS_NOT_DEFINED = "not defined"