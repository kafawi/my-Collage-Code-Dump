#!/usr/bin/env python3
"""Fill data bank with data for regesiontest and cies email acc

test data is hard coded

script usage: 
    python3 db_feed.py emial server pw port

Keyword arguments:
email  -- email user/address
server -- email server
pw     -- password
port   -- port to send
"""
__author__ = "kafawi"

from pymongo import MongoClient
import argparse
import sys
import json
from bson.json_util import dumps, loads
from data_handler import CiesData
from bson.objectid import ObjectId
from timestamp import stamp

def delete_db(cc):
    """
    Deletes default dataset from database.

    Keyword arguments:
    cc -- pointer to database
    """
    #cc.customers.drop_indexes()
    #cc.projects.drop_indexes()
    #cc.email.drop_indexes()
    #cc.reports.drop_indexes()
    #cc.cies.drop_indexes()
    #cc.customer.drop_indexes()
    #cc.customer.drop()
    #cc.project.drop_indexes()
    #cc.project.drop()
    #cc.email.drop_indexes()
    cc.email.drop()
    #cc.report.drop_indexes()
    #cc.report.drop()
    #cc.cies.drop_indexes()
    #cc.cies.drop()
    #cc.credentials.drop()
    #cc.customers.drop()
    #cc.projects.drop()
    #cc.reports.drop()
    db = CiesData()
    db.rm_customer(ID=0)
    db.rm_project(CDR_ID=1044)
    db.rm_project(CDR_ID=1044)
    db.rm_project(CDR_ID=1588)
    db.rm_project(CDR_ID=1588)
    db.rm_report(gitsha="123456GITSCH",CDR_ID=1044)


def init_db(emailacc):
    """Initializes database.

    Keyword arguments:
    emailacc -- email-accout dictionary in json format
    """
    # remove everything
    client = MongoClient('mongodb://mongodb.cies-mongodeploy.svc.cluster.local:27017')
    cc = client.userdata
    delete_db(cc)
    client.cies.email.drop()
    db = CiesData()
    
    print("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
    for p in db.db.projects.find():
        print(p)
    print("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
    client.cies.email.insert_one(emailacc)
    es = cc.email.find()
    i = 0
    for e in es:
        print(i, ": userdata : ",e["email"])
        i= i+1

    es = client.cies.email.find()
    i = 0
    for e in es:
        print(i, ": cies      : ",e["email"])
        i= i+1
    print("email done\n\n")

    #db.init_index()

    TSR_doc = {
        "CAC_ID"       : 1045,
        "CDR_ID"       : 1044,
        "cac_name"     : "TCAC",
        "cac_url"      : "git@gitlab.informatik.haw-hamburg.de:CIES/TCAC.git",
        "cdr_name"     : "TCDR",
        "cdr_url"      : "git@gitlab.informatik.haw-hamburg.de:CIES/TCDR.git",
        "cdrprivatekey": "-----BEGIN RSA PRIVATE KEY-----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-----END RSA PRIVATE KEY-----",
        "email"        : "cies.tessa@haw-hamburg.de",
        "name"         : "TSR",
        "projectpublickey" : "ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAACAQDWVJayk4JnrgQqvpf4fSX8RbBrSYrjV+5AQgic0B4F04l6wrfGdFASJzMwZKCnzUzKvib2rjrPROoU6RT+qCdkKQunHd4HPIcsOSX/6e3w6hEFeGPS/VHXVH3usToUzsl6hJy7BKXLJ/a9mFsGkwz9uWKo1YbgZD4b7VjHYibN//RvFfUv7ftvWT5ehs5gPFhxwG7ZoyqfdfwGFWCvdJecmtaBuHEzVZeKFvykfvfvwkGFlNtxLZlqCwzRPhMK/M0BlA8FQ8bAqqHufamp5r/awL0ssGX/cgyVqTSc03cWnJiiMhkFEBS2Pxk9LT97ZScB9D6oYUz8wQuUXM3QM40kLP//n2Q4bKBo7aPvApRzxJX7FcEuapyCz/vFJrwzG+N0p6QC2YninVJZKLJZZk5vy3mMXsTBY1ypZopN0sU8uC1hHbe64uTI1WR34ayYAz8klAVzgo4pHKfHQs+w0RDXXdBcTiqAQmlxbW4dB/eN73sYsp7te5Tam2tkPrEgy/ACcR9mA8eO5gTFx7K3VFRQryNuGfXt5Cvqih8swPCQL8jUMzK3wIkluFM9PGfeEwl328eUD+Ydq3SXtSvBKgoS5OzKd4eTi6VZefBWo8G7tPBys6QvNDV/QdxPlGFSyOv5bIC8ECG20FaCHW6h01AiB1jc5MFTgm4c3j+cu6JpKw== abx932@gitlab.informatik.haw-hamburg.de",
        "src_dir"      : "CPP/HELLO_WORLD/"
    }

    CAC_stable_doc = {
        "CAC_ID"       : 0,
        "CDR_ID"       : 1588,
        "cac_name"     : "CAC_sable",
        "cac_url"      : "git@gitlab.informatik.haw-hamburg.de:CIES/CAC_stablegit",
        "cdr_name"     : "",
        "cdr_url"      : "",
        "cdrprivatekey": "RSAKEY",
        "email"        : "cies.tessa@haw-hamburg.de",
        "name"         : "CAC_stable",
        "projectpublickey" : "ssh-rsa"
    }
    db.insert_project(TSR_doc)
    db.insert_project(CAC_stable_doc)

    testdummy_doc = {
        "mail": "cies.tessa@haw-hamburg.de",
        "name": "Testdummy McDummtest",
        "password": "password"
    } 
    # needs the rsh key pair
    db.insert_credential(testdummy_doc)
    
    print("db_feed: find projects in cc.project")
    ps = cc.projects.find()
    i = 0
    for e in ps:
        print(i," :",e["CDR_ID"])
        i= i+1
    # test get project id
    print("project done\n\n")

    db.add_report_dic(gitsha="123456GITSCH", CDR_ID=1044, PIP_ID=0, reportdic={"bird":"word"})
    ps = cc.reports.find()
    i = 0
    for e in ps:
        print(i," :",e["gitsha"])
        i = i+1
    print("report done \n\n")

    id = db.add_customer(name="testdummy", email="cies.tessa@haw-hamburg.de" , parr=[ 1044 ], ID = 0)
    print("ID:",id)
    cs = cc.customers.find()
    i = 0
    for c in cs:
        print(i, " :", c["ID"], c["name"])
        i = i+1
    print("customer done \n\n")



def test_init():
    """Initialisation self-test
    """
    db = CiesData()
    ret = db.get_email()
    if not ret:
        sys.exit(1)
    ret = db.get_customer(0)
    if not ret:
        sys.exit(1)
    ret = db.get_project(1044)
    if not ret:
        sys.exit(1)

    print("\n-----\n\ntest_find_id\n\n------\n")
    id = db.find_free_customer_id()
    print("found_id", id)
    if id != 1:
        sys.exit(1)

    print("test get report_querys")
    ret = db.get_report_by_pipeline_cdr_id(0, 1044)
    if not ret:
        sys.exit(1)
    ret = db.get_report_by_gitsha_cdr_id("123456GITSCH", 1044)
    if not ret:
        sys.exit(1)
    ret = db.get_report_by_gitsha_cdr_id("123456GITSCH", 1044)
    if not ret:
        sys.exit(1)
    ret = db.get_report_by_gitsha_cdr_name("123456GITSCH", "TCDR")
    if not ret:
        sys.exit(1)




if __name__ == "__main__":  # testing
    parser = argparse.ArgumentParser(description="feet th db")
    parser.add_argument("email", type=str, help="email")
    parser.add_argument("server", type=str, help="server")
    parser.add_argument("pw", type=str, help="password")
    parser.add_argument("port", type=str, help="port")
    args = parser.parse_args()

    emailacc={ \
        "NAME" : "AG-TeSSA", \
        "email": args.email, \
        "receive": 993, \
        "server" : args.server, \
        "pw"    : args.pw, \
        "port"   : args.port}
    init_db(emailacc)
    data = CiesData()
    #data.db.customers.drop() # later
    databases = data.client.database_names()
    print("database  : ", databases)
    databases = data.client.database_names()
    for db in databases:
        exec("collections"  + " = data.client."+db+".collection_names()")
        print(" -", db,"\t:", collections) 
        for co in collections:
            exec("entrys" + " = data.client."+ db +"."+ co +".find()")
            i = 0
            for e in entrys:
               #e.pop('_id')
               s = dumps(e, indent=3, sort_keys=True)
               stoe = loads(s)
               if sorted(stoe) == sorted(e):
                  print("s = dumps(a) -> b = loads(s): a==b ")
               print(" --",co,"\t-",i,"\t:", s)
               i+=1

    #print(" -admin   : ", data.client.admin.collection_names())
    #print(" -cies    : ", data.client.cies.collection_names())
    #print(" -config  : ", data.client.config.collection_names())
    #print(" -local   : ", data.client.local.collection_names())
    #print(" -test    : ", data.client.test.collection_names())
    #print(" -userdata: ", data.db.collection_names())
    #init_db(emailacc)
    #db = CiesData()

    #test_init()
