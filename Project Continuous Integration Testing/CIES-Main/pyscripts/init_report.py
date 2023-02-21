#!/usr/bin/env python3
"""Insert report dummy into data bank

script usage: 
    python3 stor_report.py cdr_id piplineid gitsha

Keyword arguments:
cdr_id      -- project id (CDR_ID) 
piplineid   -- pipeline id of CDR pipeline
gitSHA      -- git hash of CDR commit
"""
__author__ = "kafawi"

import json
import argparse
from datetime import datetime
from data_handler import CiesData


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="insert report dummy into db")
    parser.add_argument("cdr_id", type=int, help="project (CDR) id")
    parser.add_argument("pip_id", type=int, help="pipeline id")
    parser.add_argument("gitsha", type=str, help="Commit SHA")

    args = parser.parse_args()

    db = CiesData()
    db.init_report(cdr_id=args.cdr_id, pip_id=args.pip_id, gitsha=args.gitsha)
    #db.add_report(args.gitSHA, args.cdr_id, args.pipelineid, args.reportpath)
