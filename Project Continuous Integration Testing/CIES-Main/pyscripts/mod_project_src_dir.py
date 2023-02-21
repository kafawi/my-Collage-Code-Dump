#!/usr/bin/env python3

import json
import argparse
from datetime import datetime
from data_handler import CiesData

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="change CDRs project src_dir")
    parser.add_argument("cdr_id", type=int,
                        help="gitlab CDR id")
    parser.add_argument("src_dir", type=str, help="new source directory")
    args = parser.parse_args()

    db = CiesData()
    db.mod_project_src_dir(args.cdr_id, args.src_dir)


    B]8cHsFsZp@{&S<2&