#!/usr/bin/env python3
"""Generate report-delivery.sh or analyze.sh for anaylsis pipeline in cac

this

script usage:
  for report-delivery.sh:
    python3 script_generator.py -r customer_id cdr_id pipeline_id [fpath [tplpath]]
  for analyse.sh
    python3 script_generator.py -a cdr_id [fpath [tplpath]]

Keyword arguments:
customer_id -- customer ID
cdr_id      -- gitlab project id from CDR
pipeline_id -- Pipline ID of CAC pipeline
tplpath     -- (optional) path to template for .gitlab-ci.yml
fpath       -- (optonal) path to output file
"""
__author__ = "kafawi"

import argparse
import json
from jinja2 import Template
from data_handler import CiesData
import glob

DEFAULT_OUT_SEND_PATH = "./report-delivery.sh"
DEFAULT_IN_SEND_TEMP = "./Templates/tpl-report-delivery.sh"
DEFAULT_OUT_ANALYZE_PATH = "./analyze.sh"
DEFAULT_IN_ANALYZE_TEMP = "./Templates/tpl-analyze.sh"



def generate_yml_str(project, tpl):
    yml_str = ""
    with open(tpl, 'r', encoding='utf-8') as file:
        tpl_str = file.read()
    template = Template(tpl_str)
    yml_str = template.render(p=project)
    return yml_str

def generate_send_sh_str(email, report, project, credential, tpl):
    send_str = ""
    with open(tpl, 'r', encoding='utf-8') as file:
        tpl_str = file.read()
    template = Template(tpl_str)
    send_str = template.render(e=email, r=report, p=project, c=credential)
    return send_str


def generate_analyze_sh_str(project, src_root, tpl):
    analyze_str = ""
    with open(tpl, 'r', encoding='utf-8') as file:
        tpl_str = file.read()
    template = Template(tpl_str)
    analyze_str = template.render(rdata=project, projectroot=src_root)
    return analyze_str



def generate_analyse_sh_file(project, project_root, filename, tpl_dir_path, dest_dir_path):
    db = CiesData()
    src_dir = project[db.SRC_DIR_KEY]
    print(src_dir)
    src_root = project_root + '/'+ src_dir
    src_root = src_root.replace("//", "/")
    src_root = src_root.replace(".sh.sh", ".sh")
    print(src_root)
    tpl = tpl_dir_path + '/' + filename + '.sh'
    tpl = tpl.replace("//", "/")
    tpl = tpl.replace(".sh.sh", ".sh")
    print(tpl)
    script_str = generate_analyze_sh_str(project,src_root,tpl)
    print(script_str)
    out_file = dest_dir_path + '/' + filename +'.sh'
    out_file = out_file.replace("//", "/")
    out_file = out_file.replace(".sh.sh", ".sh")
    with open(out_file, 'w', encoding='utf-8') as file:
        file.write(script_str)



def generate_send_sh_file(cdr_id, credential, gitsha, pipeline_id, report_dir, tpl_dir_path, dest_dir_path):
    db = CiesData()
    project = db.get_project(cdr_id)
    credential = db.get_credential(project[db.PROJECT_EMAIL_KEY])
    report = db.get_one_report(cdr_id, pipeline_id, gitsha)
    #src_dir = project[db.SRC_DIR_KEY]
    #print(src_dir)
    #src_root = project_root + '/'+ src_dir
    tpl = tpl_dir_path + '/' + filename + '.sh'
    tpl = tpl.replace("//", "/")
    tpl = tpl.replace(".sh.sh", ".sh")
    #print(tpl)
    #script_str = generate_analyze_sh_str(project,src_root,tpl)
    #print(script_str)
    script_str = generate_send_sh_str(email, report, project, credential, report_dir, tpl)
    out_file = dest_dir_path + '/' + filename +'.sh'
    out_file = out_file.replace("//", "/")
    out_file = out_file.replace(".sh.sh", ".sh")
    with open(out_file, 'w', encoding='utf-8') as file:
        file.write(script_str)
    print("TODO")



def generate_send_script(email, report, project, credential, tplpath=DEFAULT_IN_SEND_TEMP, fpath=DEFAULT_OUT_SEND_PATH):
    """Generate the deliver script for the report

    Keyword arguments:
    email    -- dictionary of cies email account
    customer -- dictionary of customer
    report   -- dictionary of report
    cdr_name -- Name of Project (CDR)
    tplpath  -- (optional) path to template for .gitlab-ci.yml
    fpath    -- (optonal) path to output file
    """
    with open(tplpath, 'r', encoding='utf-8') as file:
        file_str = file.read()
    template = Template(file_str)
    script = template.render(e=email, r=report, p=project, c=credential)
    with open(fpath, 'w', encoding='utf-8') as file:
        file.write(script)

def generate_analyze_script(project, projectroot, tplpath=DEFAULT_IN_ANALYZE_TEMP, fpath=DEFAULT_OUT_ANALYZE_PATH):
    """Generate the deliver script for the report

    Keyword arguments:
    project  -- dictionary of project
    tplpath  -- (optional) path to template for .gitlab-ci.yml
    fpath    -- (optonal) path to output file
    """
    with open(tplpath, 'r', encoding='utf-8') as file:
        file_str = file.read()
    template = Template(file_str)
    print("project doc out of db:")
    print(project)
    script = template.render(rdata=project, projectroot=projectroot)
    with open(fpath, 'w',encoding='utf-8') as file:
        file.write(script)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="generates bash script for analyse")
    parser.add_argument("-r", nargs=2, type=int, metavar=('projectID', 'pipelineID'),
                        help="generates the delivery_report.sh")
    parser.add_argument("-a", nargs=2, type=str, metavar=("pid", "projctroot"),
                        help="generates the analyze.sh")
    parser.add_argument("fpath", nargs="?", type=str,
                        help="path to output file")
    parser.add_argument("tplpath", nargs="?", type=str,
                        help="path template file")
    args = parser.parse_args()
    if not args.r and not args.a:
        parser.print_help()
    else:
        data = CiesData()
        if args.r:
            fpath = DEFAULT_OUT_SEND_PATH
            tplpath = DEFAULT_IN_SEND_TEMP
            if args.fpath:
                fpath = args.fpath
            if args.tplpath:
                tplpath = args.tplpath
            #umail = str(args.r[0])
            project = data.get_project(int(args.r[0]))
            credential = data.get_credential(project["email"])
            #report_ds = data.get_report_by_pipeline_cdr_name(args.r[2],projectname)
            report_ds = data.get_report_by_pipeline_cdr_id(int(args.r[1]), int(args.r[0]))
            report = report_ds["reports"]["static"]
            #report = data.get_report_by_pipeline_cdr_name(args.r[2],projectname)
            with open("report.json", 'w',encoding='utf-8') as file:
                json.dumps(report)
            #customer = data.get_customer_by_id(args.r[0])
            email = data.get_email()
            generate_send_script(email,report_ds,project, credential)
        if args.a:
            fpath = DEFAULT_OUT_ANALYZE_PATH
            tplpath = DEFAULT_IN_ANALYZE_TEMP
            if args.fpath:
                fpath = args.fpath
            if args.tplpath:
                tplpath = args.tplpath
            print(args.a[0])
            print(args.a[1])
            pro_root = args.a[1]+"/"
            project = data.get_project(int(args.a[0]))
            generate_analyze_script(project, pro_root)
