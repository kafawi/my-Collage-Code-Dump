#!/usr/bin/env python3
"""Data handler module to communicate with cies mongoDB"""
__author__ = "kafawi"


import json

import pymongo
from pymongo import MongoClient
#from pymongo import ObjectId
from bson.json_util import dumps, loads

from timestamp import stamp
import datetime

class CiesData:
    """CiesData class provide methodes to communicate with data bank

    collections:
    db.customer -- customer collection
    db.project  -- projects collection
    db.report   -- reports collection

    class vars:
    client -- mongoDB client
    db     -- database (cies)
    """
    MONGO_HOST = 'mongodb://mongodb.cies-mongodeploy.svc.cluster.local:27017'
    # REPORT
    TIMESTAMP_KEY = "timestamp"
    CDR_ID_KEY = "CDR_ID"
    PIP_ID_KEY = "PIP_ID"
    GITSHA_KEY = "gitsha"
    REPORTS_KEY = "reports"
    REPORT_STATUS_KEY = "status"
    REPORT_STATUS_TAKEN = "taken"
    REPORT_STATUS_CHECKING = "checking"

    # PROJECT KEY
    PROJECT_NAME_KEY = 'name'
    CDR_NAME_KEY = 'cdr_name'
    CAC_NAME_KEY = 'cac_name'
    CDR_ID_KEY = 'CDR_ID'
    CAC_ID_KEY = 'CAC_ID'
    CDR_URL_KEY = 'cdr_url'
    CAC_URL_KEY = 'cac_url'
    PROJECT_EMAIL_KEY = 'email'
    USER_PUBKEY_KEY = 'projectpublickey'
    USER_PRIKEY_KEY = "cdrprivatekey"
    CDR_PUSH_PUBKEY_KEY = 'cacpublickey'
    CDR_PUSH_PRIKEY_KEY = 'cacprivatekey'
    CLONE_CDR_PUBKEY_KEY = 'clone_cdr_publickey'
    CLONE_CDR_PRIKEY_KEY = 'clone_cdr_privatekey'
    UPDATE_CAC_PUBKEY_KEY = 'update_cac_publickey'
    UPDATE_CAC_PRIKEY_KEY = 'update_cac_privatekey'
    BRANCH_KEY = 'branch'
    SRC_DIR_KEY = 'src_dir'


    def __init__(self):
        """Constructor

        Keyword arguments:
        client -- MongoDB client
        db -- data base cies
        """
        self.client = MongoClient(self.MONGO_HOST)
        self.db = self.client.userdata


    def init_index(self):
        """initializes index.

        Keyword arguments:
        self -- the self-pointer
        """
        self.db.projects.create_index(
            [("CDR_ID", pymongo.ASCENDING)], unique=True)  # project
        # self.db.report.create_index( { "gitsha": 1, "CDR_ID"  :1, "PIP_ID" :
        # 1},unique=True)#report
        self.db.customers.create_index(
            [("ID", pymongo.ASCENDING)], unique=True)  # customer


    def get_credential(self, mail):
        print("get_credential +++ \ninput:\n", mail)
        #ret = self.db.customer.find_one({"ID": custom_id})
        ret = self.db.credentials.find_one({"mail": mail})
        print("output:\n", ret, "\n --- get_credential")
        return ret



    def get_report_by_pipeline_cdr_id(self, pid, cid):
        """retrieves report by project ID and customer ID

        Keyword arguments:
        self -- the self-pointer
        pid -- the project ID
        cid -- the CDR project ID
        """
        print("get_report_by_pipeline_cdr_id +++ \ninput:\n", pid, ":", cid)
        ret = self.get_one_report(cdr_id=cid, pip_id=pid)
        print("output:\n", ret, "\n --- get_report_by_pipeline_cdr_id")
        return ret



    def get_report_by_gitsha_cdr_id(self, gitsha, cid):
        """retrieves report by git-hash and customer ID

        Keyword arguments:
        self -- the self-pointer
        gitsha -- the commit's hash
        cid -- the CDR project ID
        """
        #gitsha=gitsha.encode("utf-8").strip()
        print("get_report_by_gitsha_cdr_id +++ \ninput:\n", gitsha, ":", cid)
        ret = self.get_one_report(cdr_id=cid, gitsha=gitsha)
        print("output:\n", ret, "\n --- get_report_by_gitsha_cdr_id")
        return ret


    # def get_repositories_by_customer(self, custom_id):
    #    ret = {}
    #    custom_id = str(custom_id)
    #    repo_list = self.get_customer_by_id(custom_id)['repositories']
    #    for repo_id in repo_list:
    #        i = str(repo_id)
    #        ret[i] = self.all_repository[i]
    #    return ret

    def get_project(self, pid):
        """retrieves report by project ID

        Keyword arguments:
        self -- the self-pointer
        pid -- the project ID
        """
        print("get_project +++ \ninput:\n", pid)
        ret = self.db.projects.find_one({self.CDR_ID_KEY : int(pid)})
        print("output:\n", ret[self.PROJECT_NAME_KEY], "\n --- get_project")
        return ret


    def update_project(self, cdr_id, set_dic):
        self.db.projects.update_one({self.CDR_ID_KEY: int(cdr_id)}, {'$set': set_dic})


    def get_email(self):
        """retrieves email account data from database

        Keyword arguments:
        self -- the self-pointer
        """
        print("get_email +++ \ninput:\n" "-")
        ret = self.client.cies.email.find({"NAME": "AG-TeSSA"})[0]
        print("output:\n", ret, "\n --- get_email")
        return ret


    def insert_project(self, project_json):
        """Inserts project description into database

        Keyword arguments:
        self -- the self-pointer
        project_json -- the project description in json format
        """
        print(" +++ insert_project")
        is_valid = (project_json["CAC_ID"] != None and
                    project_json["cac_name"] != None and
                    project_json["cac_url"] != None and
                    project_json["CDR_ID"] != None and
                    project_json["email"] != None and
                    project_json["cdrprivatekey"] != None and
                    project_json["projectpublickey"] != None and
                    project_json["name"] != None )
        if is_valid:
            self.db.projects.insert(project_json)
            print(self.get_project(project_json["CDR_ID"]))
        else:
            print("invalid project_json")
        print(" --- insert_project")


    def insert_report(self, report_json):
        """inserts new report into database

        Keyword arguments:
        self -- the self-pointer
        report_json -- the report in json format
        """
        print("insert_report +++ \ninput:\n", report_json)
        self.db.reports.insert(report_json)
        print(self.db.reports.find_one(
            {"$and": [{"gitsha": report_json["gitsha"]}, {"CDR_ID": report_json["CDR_ID"]}]}))
        print(" --- insert_report")

    # def mod_project(self, CDR_ID, cdr_name=None, cac_name=None, cdr_url=None, cac_url=None,
    #                 src_dir=None,
    #                 lang=None, target=None, codingstyle=None, branch=None,
    #                 analyze_opt=None, blacklist=None, payment_methode=None, active=None,
    #                 report_arcive=None
    #                 ):
    #     print("TODO")

    # def mod_customer(self, ID, name, email, parr=[], password=None, bankacc=None):
    #     print("TODO")

    def insert_credential(self, cred_dict):
        """inserts new credential/customer into database

        Keyword arguments:
        self -- the self-pointer
        cred_dict -- the credentials/customer infos in a dictionary
        """
        is_valid = (cred_dict["mail"] != None and cred_dict["name"] != None and cred_dict["password"] != None)
        if (is_valid):
            #is_mail_free = (self.db.credentials.find_one({"mail":cred_dict["mail"]})==)
            #if (is_mail_free )
            self.db.credentials.insert(cred_dict)
        else:
            print("credentials dict is not valid: it needs at least 'mail', 'name' and 'password'")



    def init_report(self, cdr_id, pip_id, gitsha):
        report_frame = {
             self.CDR_ID_KEY   : int(cdr_id)
            ,self.PIP_ID_KEY   : int(pip_id)
            ,self.GITSHA_KEY   : str(gitsha)
            ,self.TIMESTAMP_KEY: stamp()
            ,self.REPORT_STATUS_KEY : self.REPORT_STATUS_CHECKING
            ,self.REPORTS_KEY  : {}
            }
        self.db.reports.insert(report_frame)
        #print(type(ret),ret)


    def take_report(self, cdr_id, pip_id, gitsha):
        """
        this must be a transaction
        """
        take = False
        if not self.is_report_taken(cdr_id, gitsha):
            self._update_report(cdr_id, pip_id, gitsha, self.REPORT_STATUS_KEY , str(self.REPORT_STATUS_TAKEN))
            take = True
        return take


    def get_taken_report(self, cdr_id, gitsha):
        query = {"$and": [{self.CDR_ID_KEY : int(cdr_id)}, {self.GITSHA_KEY : str(gitsha)}, {self.REPORT_STATUS_KEY : self.REPORT_STATUS_TAKEN}]}
        return self.db.reports.find_one(query)


    def is_report_taken(self, cdr_id, gitsha):
        return self.get_taken_report(cdr_id, gitsha) is not None


    def _update_report(self, cdr_id, pip_id, gitsha, key, update):
        query = self._gen_report_query(cdr_id=int(cdr_id), pip_id=int(pip_id), gitsha=str(gitsha))
        update = {"$set" : {str(key) : update}}
        ret = self.db.reports.update_one(query, update, upsert=False, bypass_document_validation=False, collation=None, array_filters=None, session=None)
        return ret


    def _gen_report_query(self, cdr_id=None, pip_id=None, gitsha=None, timestamp=None, beforTimestamp=False):
        tmp=dict()
        if gitsha:
            tmp.update({self.GITSHA_KEY : str(gitsha)})
#            tmp[GITSHA_KEY] = gitsha
        if cdr_id:
            tmp.update({self.CDR_ID_KEY : int(cdr_id)})
#            tmp[CDR_ID_KEY] = cdr_id
        if pip_id:
            tmp.update({self.PIP_ID_KEY : int(pip_id)})
#            tmp[PIP_ID_KEY] = pip_id
        if timestamp:
            if type(timestamp) == datetime.datetime:
                date = timestamp
                if beforTimestamp:
                   cmp_op = "$lte"
                else:
                   cmp_op = "$gte"
                tmp.update({ self.TIMESTAMP_KEY : { cmp_op : date } })
#                tmp[TIMESTAMP_KEY] = { cmp_op : date }
        if not tmp:
            query = dict()
        elif len(tmp) == 1:
            query = tmp
        else:
            query = {"$and": [tmp]}
        return query


    def get_reports(self, cdr_id=None, pip_id=None, gitsha=None, timestamp=None, beforTimestamp=False):
        """retrive all report dictionary that matches the parameters

        """
        query = self._gen_report_query(cdr_id, pip_id, gitsha, timestamp, beforTimestamp)
        cursor = self.db.reports.find(query)
        ret = list(cursor)
        return ret


    def get_one_report(self, cdr_id=None, pip_id=None, gitsha=None, timestamp=None, beforTimestamp=False):
        ret = self.get_reports(cdr_id, pip_id, gitsha, timestamp, beforTimestamp)
        if len(ret) == 0:
            ret = None
        else:
            ret = ret[0]
        return ret


    def add_file_report(self, cdr_id, pip_id, gitsha, reportkey, dic):
        query = self._gen_report_query(cdr_id=int(cdr_id), pip_id=int(pip_id), gitsha=str(gitsha))
        update = {"$set" : {self.REPORTS_KEY+"."+(str(reportkey)) : [dic]}}
        ret = self.db.reports.update_one(query, update, upsert=False, bypass_document_validation=False, collation=None, array_filters=None, session=None)
        return ret


    def rm_credential(self, email):
        """removes just one credential from database
        """
        self.db.credentials.remove({"mail": email}, {"justOne": True})


    def rm_all_credentials(self, email):
        """removes all credentials from database
        """
        self.db.credentials.remove({"mail": email}, {"justOne": False})


    def rm_project(self, cdr_id):
        """removes just one project from database

        Keyword arguments:
        self -- the self-pointer
        CDR_ID -- the identifier of the project to be removed
        """
        self.db.projects.remove({self.CDR_ID_KEY: cdr_id}, {"justOne":True})


    def rm_all_projects(self, cdr_id):
        """removes just one project from database

        Keyword arguments:
        self -- the self-pointer
        CDR_ID -- the identifier of the project to be removed
        """
        self.db.projects.remove({self.CDR_ID_KEY:cdr_id}, {"justOne":False})


    def rm_report(self, cdr_id, pip_id, gitsha):
        """removes just one report from database

        Keyword arguments:
        self -- the self-pointer
        gitsha -- the git-hash of the report to be removed
        PIP_ID -- Pipeline id
        CDR_ID  -- the customer analysis repositories ID
        """
        query = self._gen_report_query(cdr_id, pip_id, gitsha)
        self.db.reports.remove(query, {"justOne":True})

#
    def rm_all_reports(self, cdr_id, pip_id=None, gitsha=None):
        """removes reports from database

        Keyword arguments:
        self -- the self-pointer
        gitsha -- the git-hash of the report to be removed
        CDR_ID  -- the customer analysis repositories ID
        """
        query = self._gen_report_query(cdr_id, pip_id, gitsha)
        #query = {"$and": [{"gitsha": gitsha, "CDR_ID": CDR_ID}]}
        self.db.reports.remove(query, {"justOne":False})


    def add_project(self, CDR_ID, cdr_name, cac_name, cdr_url, cac_url, email,src_dir=None,
                    lang="cpp", target="linux", codingstyle=None, branch=["master"],
                    analyze_opt=[], blacklist=[], payment_method="FPPM", active=True,
                    report_arcive=[]
                    ):
        """Adds project to database

        Keyword arguments:
        self -- the self-pointer
        CDR_ID  -- the customer development repo's ID
        cdr_name -- the customer development repo's name
        cac_name -- the customer analysis copy's name
        cdr_url -- the customer development repo's URL
        cdr_url -- the customer analysis copy's URL
        """
        project = {
            "CDR_ID": int(CDR_ID),
            "cdr_name": str(cdr_name),
            "cac_name": str(cac_name),
            "cdr_url": cdr_url,
            "cac_url": cac_url,
            "src_dir": src_dir,
            "email" : email,
            "lang": lang,
            "target": target,
            "codingstyle": codingstyle,
            "branch": branch,
            "analyze_opt": analyze_opt,
            "blacklist": blacklist,
            "payment_method": payment_method,
            "active": active,
            "report_arcive": report_arcive}
        self.insert_project(project)
        return CDR_ID


    def add_customer(self, name, email, parr=[], ID=None, password=None, bankacc=None):
        """Adds a new customer to database.

        Keywords arguments:
        self -- the self-pointer
        name -- the customer's name
        email -- the customer's  email-address
        """
        # RACECONDITIONS possible this hole block has to be protected
        if ID == None:
            ID = self.find_free_customer_id()
        customer = {
                "ID": ID,
                "name": name,
                "email": email,
                "password": password,
                "bankacc": bankacc,
                "project": parr}
        id = self.insert_customer(customer)
        # RACECONDITIONS end
        return id


    def add_report(self, gitsha, CDR_ID, PIP_ID, reportpath):
        """Adds a new report to database

        Keyword arguments:
        self -- the self-pointer
        gitsha -- the origin commit's hash
        CDR_ID -- the customer development repo's ID
        PIP_ID -- the origin pipeline's ID
        reportpath -- the path to report on filesystem. Absolute path is preferred
        """
        with open(reportpath, 'r') as file:
            report = json.loads(file.read())
        self.add_report_dic(gitsha, CDR_ID, PIP_ID, report)
        # TODO add report to project


    def add_report_dic(self, gitsha, CDR_ID, PIP_ID, reportdic):
        """Adds report to dictionary

        Keyword arguments:
        self -- the self-pointer
        gitsha -- the origin commit's hash
        CDR_ID -- the customer development repo's ID
        PIP_ID -- the origin pipeline's ID
        reportdic -- the target dictionary
        """
        dbreport = {
            self.CDR_ID_KEY   :  CDR_ID,
            self.PIP_ID_KEY   : PIP_ID,
            self.GITSHA_KEY   : gitsha,
            self.TIMESTAMP_KEY: stamp(""),
            "static_report": [reportdic]}
        self.insert_report(dbreport)


if __name__ == "__main__":  # testing
    # print(d.get_customer_by_id('0'))
    # print(d.get_customer_by_name('testdummy'))
    # print(d.get_repositories_by_customer(0))
    # print(d.get_repository_by_id(0))
    import time
    c = CiesData()
    # testtest:

    PROJECT_ID = 1
    PROJECT_NAME = "pname"
    CAC_NAME = "CAC_name"
    CAC_URL = "CAC_url"
    CAC_ID = 2
    EMAIL = "e@mail.dot"
    PDIC={
        "CAC_ID"   : CAC_ID
      , "cac_name" : CAC_NAME
      , "cac_url"  : CAC_URL
      , "CDR_ID"   : PROJECT_ID
      , "email"    : EMAIL
      , "cdrprivatekey" : "12345"
      , "projectpublickey" : "67890"
      , "name"             : PROJECT_NAME
    }
    print("insert:", PDIC)
    c.insert_project(PDIC)
    print("\n-------------------------PROJECT Test\n")
    time.sleep(10)
    print(c.get_project(PROJECT_ID))
    print("rm project")
    if c.get_project(PROJECT_ID):
        print(c.rm_project(PROJECT_ID))
    print("\n--------------------------REPORT Test\n")

    DICT={
      "0": "ABCD"
     ,"1": "EFGH"
     ,"2": "KLMN"
     ,"3": "OPQR"
     ,"4": "STUV"
     ,"5": "XYZ"
    }
    DICT2={
      "6": "ABCD"
     ,"7": "EFGH"
     ,"8": "KLMN"
     ,"9": "OPQR"
     ,"10": "STUV"
    }

    GITSHA = "123AFFE321"
    PIPLINE_ID = 4
    PIPLINE2_ID = 5
    print("_gen_report_query(1,2,'12da',stamp("")):")
    print(c._gen_report_query(PROJECT_ID, PIPLINE_ID, GITSHA, stamp("")))
    print(c.init_report(PROJECT_ID,PIPLINE_ID,GITSHA))
    print(c.init_report(PROJECT_ID,PIPLINE2_ID, GITSHA ))
    time.sleep(10)
    print("get reports")
    reps = c.get_reports(PROJECT_ID,PIPLINE_ID,GITSHA)
    for rep in reps:
        print(rep, "\n")
    print("get one report")
    print(c.get_one_report(PROJECT_ID))
    print("update")
    print(c.add_file_report(PROJECT_ID,PIPLINE_ID,GITSHA,"static", DICT))
    print(c.add_file_report(PROJECT_ID,PIPLINE_ID,GITSHA,"dynamic", DICT2))
    reps = c.get_reports(PROJECT_ID,PIPLINE_ID,GITSHA)
    for rep in reps:
        print(rep)
    print("decrepated functions")
    print(c.get_report_by_pipeline_cdr_id(PIPLINE_ID, PROJECT_ID))
    print(c.get_report_by_gitsha_cdr_id(GITSHA, PROJECT_ID))
    print("rm reports")
    print(c.rm_report(PROJECT_ID,PIPLINE_ID,GITSHA))
    reps = c.get_reports(PROJECT_ID,PIPLINE_ID,GITSHA)
    for rep in reps:
        print(rep)
    print("---------------------------------------tidyUp")
    print(c.rm_all_reports(PROJECT_ID))


