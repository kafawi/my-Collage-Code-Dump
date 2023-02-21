#!/usr/bin/env python3
"""Validate report with reference report

Get report out of data bank
if: report == reference -> exit 0
else: -> exit 1
   
script usage: 
    python3 validate_testreports.py cdr_id gitsha refpath

Keyword arguments:
cdr_id      -- project id (CDR_ID) 
gitsha      -- git hash of CDR commit
refpath     -- (optional) path to reference report.json (output of analyze.sh)
"""
__author__ = "kafawi"

import sys
import json
from bson.json_util import dumps, loads
import argparse
from data_handler import CiesData
from difflib import unified_diff

DEFAULT_FPATH = "/mnt/cies-vol/regtest_ref/report.json"

if __name__ == "__main__":  # testing
    parser = argparse.ArgumentParser(description="regtest validation")
    parser.add_argument("cdr_id", type=int, help="cdr id")
    parser.add_argument("gitsha", type=str, help="commit sha")
    parser.add_argument("refpath", type=str, nargs="?",
                        help="Path to reference jason")
    args = parser.parse_args()
    if args.refpath:
        refpath = args.refpath
    else:
        refpath = DEFAULT_FPATH
    db = CiesData()
    reportdb = db.get_report_by_gitsha_cdr_id(args.gitsha, args.cdr_id)
#    reportdb = {'PIP_ID': 20499, 'CDR_ID': 1044, 'cdr_name': 'TDSR', 'gitsha': '4aa3795', 'timestamp': '2018-01-13::10:01:59', 'static_report': [{'files': [{'err_ids': [{'line': '1', 'decription': "'stdio' file not found ;;; ^", 'row': '10', 'errid': '0', 'type': 'fatal error'}, {
#        'line': '1', 'decription': "'stdio' file not found ;;; ^", 'row': '10', 'errid': '1', 'type': 'fatal error'}], 'file_name': 'main.cpp'}], 'stats': {'numberOfErrors': '2', 'numberOfLines': '7', 'numberOfWarnings': '0'}}]}
    reportdb = reportdb["static_report"]
    report = reportdb[0]

    with open(refpath, 'r') as file:
        ref = loads(file.read())
    
    slref=dumps(ref, indent=3, sort_keys=True).splitlines(1)
    slreport=dumps(report, indent=3, sort_keys=True).splitlines(1)

    for line in unified_diff(slref, slreport, fromfile='reference.json', tofile='report.json'):
        print(line)

    if sorted(report) == sorted(ref):
        print("regtest success")
    else:
        print("report is not equal to reference")
        sys.exit(1)
