#!/usr/bin/env python3
"""Insert report into data bank

script usage: 
    python3 stor_report.py reportpath gitSHA piplineid cdr_id

Keyword arguments:
reportpath  -- path to report.json
gitSHA      -- git hash of CDR commit
piplineid   -- pipeline id of CDR pipeline
cdr_id      -- project id (CDR_ID) 
"""
__author__ = "kafawi"

import json
import argparse
from datetime import datetime
from data_handler import CiesData
import glob

REPORT_PREFIX = "report_"

def add_all_reports(db, cdr_id, pip_id, gitsha, report_dir):
    reports = glob.glob(report_dir+"*.json")
    for report in reports:
        reportkey = report
        reportkey.replace(report_dir, "")
        reportkey.replace(".json", "")
        with open(report, 'r', encoding='utf-8') as file:
             redict = json.load(file)
        db.update_report(cdr_id, pip_id, gitsha, reportkey, redict)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="converts report to db jason")
    parser.add_argument("cdr_id", type=int, help="project (CDR) id")
    parser.add_argument("pip_id", type=int, help="pipeline id")
    parser.add_argument("gitsha", type=str, help="Commit SHA")
    parser.add_argument("report_dir", type=str, help="path to the report dir")

    args = parser.parse_args()

    db = CiesData()
    add_all_reports(db, args.cdr_id, args.pip_id, args.gitsha, args.report_dir):