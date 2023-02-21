#!/usr/bin/env python3
"""Generate a .gitlab-ci.yml for anaylsis pipeline in cac

script usage: 
    python3 yaml_generator.py customer_id cdr_id [fpath [tplpath]]

Keyword arguments:
customer_id -- customer ID 
cdr_id      -- gitlab project id from CDR
tplpath     -- (optional) path to template for .gitlab-ci.yml
fpath       -- (optonal) path to output file
"""
__author__ = "kafawi"

from jinja2 import Template
from data_handler import CiesData
import argparse
#from db_feed import test_init

DEFAULT_TEMPLATE_PATH = './Templates/tpl-gitlab-ci.yml'
DEFAULT_OFILE_PATH = '.gitlab-ci.yml'

def generate_gitlab_ci_yml(cdr_id, 
    tplpath=DEFAULT_TEMPLATE_PATH, fpath=DEFAULT_OFILE_PATH):
    """Generates .gitlab-ci.yml (function)

    Keyword arguments:
    cdr_id      -- gitlab project id from CDR
    tplpath     -- (optional) path to template for .gitlab-ci.yml
    fpath       -- (optonal) path to output file
    """
    
    db = CiesData()
    project = db.get_project(cdr_id)
    project.pop('_id')
    #project = {'cac_url': 'gitlab.informatik.haw-hamburg.de/CIES/TCAC', 'payment_method': 'FPPM', 'report_arcive': [], 'target': 'linux','src_dir': 'CPP/HELLO_WORLD/', 'blacklist': [], 'active': True, 'CDR_ID': 1044, 'lang': 'cpp', 'cdr_url': 'gitlab.informatik.haw-hamburg.de/CIES/TCDR', 'cdr_name': 'TCDR', 'branch': ['master'], 'cac_name': 'TCAC', 'analyze_opt': [], 'codingstyle': None} 
    with open(tplpath , 'r') as file:
        file_str = file.read()
    template = Template(file_str)
    sfile=template.render(p=project)
    print(sfile)
    with open(fpath, 'w') as file:
            file.write(sfile)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="creates .gitlab-ci.yml")
    parser.add_argument("cdr_id", type=int, help="Gitlab project id") 
    parser.add_argument("fpath", type=str, nargs="?", help="outputpath/.gitlab-ci.yml")
    parser.add_argument("tplpath", type=str, nargs="?", help="inputpath/tpl-gitlab-ci.yml") 
    args= parser.parse_args()
    
    if args.tplpath:
        tplpath = args.tplpath
    else:
        tplpath = DEFAULT_TEMPLATE_PATH
    if args.fpath:
        fpath = args.fpath
    else:
        fpath = DEFAULT_OFILE_PATH
    #test_init()    
    generate_gitlab_ci_yml(args.cdr_id,
        tplpath,fpath)