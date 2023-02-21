#!/usr/bin/env python3
"""Data handler module to communicate with cies mongoDB"""
__author__ = "kafawi"


import json
import argparse
from datetime import datetime

import glob

import subprocess

from shell_helper import _bash_invoke, diff_str, SshHelper, GitHelper, GitlabApiHelper
from data_handler import CiesData
from script_generator import generate_yml_str, generate_analyse_sh_file




KEY_PREFIX = "report_"
BRANCHES_KEY= "branch"


def check_and_update_yml(cdr_id, tpl_yml_path, ori_yml_path):
    db = CiesData()
    project_dic = db.get_project(cdr_id)
    new_yml = generate_yml_str(project_dic, tpl_yml_path)
    with open(ori_yml_path, 'r', encoding='utf-8') as file:
        old_yml =  file.read()
    is_same = diff_str(new_yml, old_yml)
    if not is_same:
        with open(ori_yml_path, 'w', encoding='utf-8') as file:
            file.write(new_yml)
        git = GitHelper()
        git.set_user("cac@cies.com", "cac de la cdr")
        # just an idea
        git.clone(project_dic[db.CAC_URL_KEY], "CAC", project_dic[db.UPDATE_CAC_PRIKEY_KEY])
        _bash_invoke("mv -f .gitlab-ci.yml ./CAC/.gitlab-ci.yml")
        git.add(".gitlab-ci.yml", "./CAC")
        git.commit("update pipeline", "./CAC")
        git.add_remote("origin", project_dic[db.CAC_URL_KEY],"./CAC")
        git.push("origin", project_dic[db.UPDATE_CAC_PRIKEY_KEY],"./CAC")
        gitlab = GitlabApiHelper()
        print("update yaml, we need to start again")
        gitlab.end_pipeline()
    else:
        print("check yml: nothing to update")


def check_checkout_branch(cdr_id, project_path, gitsha_filename):
    ret = None
    branch = None
    db = CiesData()
    project_dic = db.get_project(cdr_id)
    gitlab = GitlabApiHelper()
    pip_id = gitlab.get_pipeline_id()
    if project_dic.keys().isdisjoint(db.BRANCH_KEY):
        branches = ["master"]
    else:
        branches = project_dic[db.BRANCH_KEY]

    print("branches: ", branches)
    git = GitHelper()
    for branch in branches:
        git.checkout(branch, project_path)
        gitsha = git.get_commit(project_path)
        print("gitsha im haupt project: "+ git.get_commit())
        print("gitsha: "+gitsha+ "\n")

        db.init_report(cdr_id, pip_id, gitsha)
        if db.is_report_taken(cdr_id, gitsha):
            print("kann nicht sein")
            db.rm_report(cdr_id, pip_id, gitsha)
            continue
        else:
            if db.take_report(cdr_id, pip_id, gitsha):
                with open(gitsha_filename, 'w',encoding='utf-8') as file:
                    file.write(gitsha)
                return gitsha
            else:
                print("second try failed")
                db.rm_report(cdr_id, pip_id, gitsha)
                continue
    print("no free report find, nothing to do")
    gitlab.end_pipeline()
    return -1


def generate_scripts(cdr_id, project_dir, template_dir, dest_dir_path, analysis_types=['style_check','static','dynamic']):
    db = CiesData()
    project_dic = db.get_project(cdr_id)
    pwd = _bash_invoke("echo $PWD")
    project_root  = pwd + "/" + project_dir + "/"
    tpl_dir_path  = template_dir + "/"
    dest_dir_path = pwd + "/" + dest_dir_path + "/"
    for analysis_type in analysis_types:
        filename = analysis_type + ".sh"
        generate_analyse_sh_file(project_dic, project_root, filename, tpl_dir_path, dest_dir_path)


def init_env(cdr_id, project_dir, script_dir, report_dir):
    git = GitHelper()
    db = CiesData()
    project_dic = db.get_project(cdr_id)
    git.clone(project_dic[db.CDR_URL_KEY], project_dir,project_dic[db.CLONE_CDR_PRIKEY_KEY])
    _bash_invoke("mkdir " + script_dir)
    _bash_invoke("mkdir " + report_dir)


#python3 setup_pipeline.py $CDR_ID $PROJECT_DIR $SCRIPT_DIR $REPORT_DIR $GITSHA_FILENAME $PYSCRIPTS_PATH
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="setup analyse in first stage of pipeline (clone and checkout)")
    parser.add_argument("cdr_id", type=str, help="project id")
    parser.add_argument("project_dir", type=str, help="project_dir")
    parser.add_argument("script_dir", type=str, help="script_dir")
    parser.add_argument("report_dir", type=str, help="report_dir")
    parser.add_argument("gitsha_filename", type=str, help="gitsha_filename")
    parser.add_argument("pyscripts_path", type=str, help="pyscripts_path")
    args = parser.parse_args()
    print(args)
    cdr_id = args.cdr_id
    project_dir = args.project_dir
    script_dir = args.script_dir
    report_dir = args.report_dir
    gitsha_filename = args.gitsha_filename
    pyscripts_path = args.pyscripts_path
    template_dir = str(pyscripts_path) + "/Templates"
    yml_path = template_dir + "/.gitlab-ci.yml"
    check_and_update_yml(cdr_id, yml_path, ".gitlab-ci.yml")
    init_env(cdr_id, project_dir, script_dir, report_dir)
    generate_scripts(cdr_id, project_dir, template_dir, script_dir)
    _bash_invoke("cd PROJECT && git status")
    print("nicht im project")
    _bash_invoke("git status")
    check_checkout_branch(cdr_id, project_dir, gitsha_filename)
    _bash_invoke("ls -la")
    _bash_invoke("ls -la script_dir")
    _bash_invoke("ls -la report_dir")
    print("ende")
