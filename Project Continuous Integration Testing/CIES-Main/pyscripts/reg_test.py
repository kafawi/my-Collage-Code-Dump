#!/usr/bin/env python3
"""Helper function and classes

import all:
from shell_helper import _bash_invoke SshHelper GitHelper GitlabApiHelper

"""
__author__ = "kafawi"

from shell_helper import _bash_invoke, diff_str, SshHelper, GitHelper, GitlabApiHelper
from data_handler import CiesData
from timestamp import stamp_file
import sys
from time import sleep
import argparse

TSR_PATH = "./TSR/"
TIMESTAMP_FILE = "timer.txt"
TIMESTAMP_FILE_PATH = TSR_PATH + TIMESTAMP_FILE

REF_DIR_PATH = "./regtest_ref/"

POLL_TIMES = 10


def setup_reg_test(user_email, user_name, tsr_url, tsr_key, branch):
    git = GitHelper()
    git.set_user(user_email, user_name)
    git.clone(tsr_url, TSR_PATH, tsr_key)
    git.checkout(branch, TSR_PATH)


def mod_repo_and_launch_trigger(project_id, tsr_key):
    stamp_file(TIMESTAMP_FILE_PATH)
    db = CiesData()
    project_dic = db.get_project(project_id)
    _bash_invoke("cat " + TIMESTAMP_FILE_PATH)
    git = GitHelper()
    git.add(TIMESTAMP_FILE, TSR_PATH)
    git.commit("update", TSR_PATH)
    #git.add_remote("origin",args.tsr_url)
    git.push("origin", tsr_key, TSR_PATH)
    git.add_remote("tcdr", project_dic[db.CDR_URL_KEY], TSR_PATH)
    #launch trigger
    git.push("tcdr", project_dic[db.USER_PRIKEY_KEY], TSR_PATH)


def wait_for_pipeline(project_id, api_token, times):
    git = GitHelper()
    gitsha = git.get_commit(TSR_PATH)
    # poll report
    db = CiesData()
    pipeline_id = 0
    for t in range(0, times):
        print(times-t, flush=True)
        sleep(30)
        report = db.get_taken_report(cdr_id=project_id, gitsha=gitsha)
        if report:
            pipeline_id = report[db.PIP_ID_KEY]
            print("found report")
            print(pipeline_id)
            break
        if t == (times - 1):
            print("no report found", flush=True)
            sleep(1)
            sys.exit(3)
    # poll pipeline
    gitlab = GitlabApiHelper()
    cac_id = db.get_project(project_id)[db.CAC_ID_KEY]
    print("polling countdown",  flush=True)
    status = gitlab._PIPELINE_STATUS_NOT_DEFINED
    for t in range(0, times):
        print(times-t, flush=True)
        sleep(30)
        status = gitlab.get_pipeline_status(cac_id, pipeline_id, api_token)
        if status == gitlab._PIPELINE_STATUS_SUCCESS:
            return pipeline_id
        elif status == gitlab._PIPELINE_STATUS_FAILED:
            print("pipeline failed", flush=True)
            sleep(1)
            sys.exit(1)
    print("requested pipeline is still:")
    print(status,flush=True)
    sleep(1)
    sys.exit(2)


def validate(ref_dir, project_id, pipeline_id, branch):
    git = GitHelper()
    gitsha = git.get_commit(TSR_PATH)
    db = CiesData()
    report_dic = db.get_one_report(cdr_id=project_id, gitsha=gitsha, pip_id=pipeline_id)
    reports = reportdb[db.REPORTS_KEY]

    keys = reports.
    for report in reports:

    with open(refpath, 'r') as file:
        ref = loads(file.read())



#python3 reg_test.py $TCDR_ID $EMAIL_USER $NEXUS_USER $TSR_URL $SSH_KEY_TSR $ACCESS_TOKEN "master"

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="regession test script")
    parser.add_argument("cdr_id", type=int,
                        help="project id of desired project")
    parser.add_argument("user_email", type=str,
                        help="git user email addr")
    parser.add_argument("user_name", type=str,
                        help="git user name")
    parser.add_argument("tsr_url", type=str,
                        help="tsr ssh project url")
    parser.add_argument("tsr_key", type=str,
                        help="tsr deploy key")
    parser.add_argument("token", type=str,
                        help="private token for gitlab api requests")
    parser.add_argument("branch", type=str,
                        help="branch to checkout and test")
    args = parser.parse_args()
    setup_reg_test(args.user_email, args.user_name, args.tsr_url, args.tsr_key, args.branch)
    mod_repo_and_launch_trigger(args.cdr_id, args.tsr_key)
    pipeline_id = wait_for_pipeline(args.cdr_id, args.token, POLL_TIMES)
    validate(REF_DIR_PATH, args.cdr_id, pipeline_id, args.branch)
    # poll pipeline

#tsr_test:
#   stage: regression_test
#   image: $DOCKER_REGISTRY/$DO_LINUX_ANAYLYSE:latest
#   before_script:
#     - python3 -m pip install --upgrade argparse jinja2 requests pymongo
#     #- bash ./dockerfiles/send_report/install.sh
#     #- bash ./dockerfiles/linux_analyse/install.sh
#   script:
#     - pwd
#     - ls
#     - cd ..
#     - git config --global user.email $EMAIL_USER
#     - git config --global user.name $NEXUS_USER
#     - touch timer.txt
#     - python3 ./CIES-Main/pyscripts/timestamp.py timer.txt
#     - export TS=$(cat timer.txt)
#     # update gitlab-ci yaml (rm old, cp new)
#     - cd ./CIES-Main/pyscripts
#     - python3 yaml_generator.py $TCDR_ID
#     - cd ../../
#     - pwd
#     - ls -la
#     - echo "$TCAC_URL"
#     #- python3 ./CIES-Main/pyscripts/git_ssh.py "$SSH_PRIV_KEY_TCAC" -clone "$TCAC_URL"
#     - eval $(bash ./CIES-Main/pyscripts/setup_ssh.sh "$SSH_KEY_UPDATE_CAC" )
#     - git clone "$TCAC_URL"
#     #- git clone "https://oauth2:"$ACCESS_TOKEN"@"$GITLAB_PATH/$TCAC
#     - cd TCAC
#     # Check if old yaml == new yaml, because git push will fail, is nothing to commit
#     - DIFF=$(diff .gitlab-ci.yml ../CIES-Main/pyscripts/.gitlab-ci.yml) || true
#     - echo $DIFF
#     - if [ "$DIFF" != "" ]; then
#     - rm -f .gitlab-ci.yaml
#     - /bin/cp ../CIES-Main/pyscripts/.gitlab-ci.yml .
#     - git add .gitlab-ci.yml
#     - git commit -m "UPDATE .gitlab-ci.yaml" -n
#     - git remote add tcac $TCAC_URL
#     #- git remote set-url tcac https://oauth2:$ACCESS_TOKEN@$GITLAB_PATH/$TCAC
#     #- python3 ./CIES-Main/pyscripts/git_ssh.py "$SSH_PRIV_KEY_TCAC" -push "tcac master"
#     - git push tcac master
#     - fi
#     - cd ..
#     # start trigger and reg test clone, add, commit push
#     #  -> webhook to TCAC
#     - eval $(bash ./CIES-Main/pyscripts/setup_ssh.sh "$SSH_KEY_TSR" )
#     - git clone "$TSR_URL"
#     #- git clone "https://oauth2:"$ACCESS_TOKEN"@"$GITLAB_PATH/$TSR
#     - cd TSR
#     #- git remote set-url tcdr https://oauth2:$ACCESS_TOKEN@$GITLAB_PATH/$TCDR
#     #- git pull tcdr master
#     - ls
#     - /bin/cp -f ../timer.txt timer.txt
#     - cat timer.txt
#     - git add timer.txt
#     - git commit -m "regtest"
#     - git push origin master
#     #
#     - eval $(bash ../CIES-Main/pyscripts/setup_ssh.sh "$SSH_KEY_USERGATE" )
#     - git remote add tcdr $TCDR_URL
#     - git push tcdr master
#     # Poll Pipeline in TCAC till it change status -> failed or finish
#     #- echo $CI_JOB_TOKEN
#     - GITSHA=$(git rev-parse HEAD)
#     #- python3 ../CIES-Main/pyscripts/poll_pipeline.py $TCAC_ID . master $CI_JOB_TOKEN 10 $GITSHA
#     - python3 ../CIES-Main/pyscripts/poll_pipeline.py $TCAC_ID $TCDR_ID . master $ACCESS_TOKEN 10 $GITSHA
#     - python3 ../CIES-Main/pyscripts/validate_testreports.py $TCDR_ID $GITSHA /CIES/CIES-Main/regtest_ref/hello_world.json