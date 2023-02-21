#!/usr/bin/env python3
"""Helper function and classes

import all:
from shell_helper import _bash_invoke SshHelper GitHelper GitlabApiHelper

"""
__author__ = "kafawi"



import subprocess
import sys
import os
import requests
from difflib import unified_diff

def _bash_invoke(cmd):
    """ invokes in a subprocess a shell command

    Keyword arguments:
    cmd -- shell command
    """
    try:
        out = subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT)
        out = str(out.strip().decode('utf-8'))
        print(out)
    except subprocess.CalledProcessError as err:
        print(err)
        out = "-1"
    return out


def diff_str(ref, actual):
    """ diff string agains a ref

    returns if:   ref == actual -> True
            else:               -> False

    Keyword arguments:
    ref    -- reference (how it should be)
    actual -- actual (how it is)
    """
    is_same = True
    for line in unified_diff(ref.split('\n'), actual.split('\n'), fromfile='ref', tofile='actual'):
        print(line)
        if line.strip():
            is_same = False
    return is_same


def get_mail(id_str):
    """ get mail out of mailbox
    returns mail as string

    Keyword arguments:
    id_str -- string that identifys the mail
    """
    mail = "no mail"
    #TODO
    return mail

class SshHelper():
    """ssh setup wrapper

    Keyword arguments:
    _SSH_SETUP_BASH -- template of ssh setup script
    _SSH_SETUP_NAME -- name of ssh setup bash script
    """


    _SSH_SETUP_BASH = """
#!/bin/bash
#
# set up the SSH agent to access the repositories of the dependencies of
# this project. Currently only works on Ubuntu or Debian machines.
#
# use: setup-ssh #
# set the private key as project secret
#

# check if this is actually ubuntu
ID="something else"
test -f /etc/os-release && source /etc/os-release
case "$ID" in
  debian|ubuntu|manjaro)
    # Install ssh-agent if not already installed, it is required by Docker.
    which ssh-agent>/dev/null || ( apt-get update -y && apt-get install openssh-client -y )
    # Run ssh-agent (inside the build environment)
    AGENT_SETUP=$(ssh-agent -s) ; echo "$AGENT_SETUP"

    # need info here too
    eval $AGENT_SETUP>/dev/null

    # For Docker builds disable host key checking. Be aware that by adding that
    # you are susceptible to man-in-the-middle attacks.
    # WARNING: Use this only with the Docker executor, if you use it with shell
    # you will overwrite your user's SSH config.
    [[ -f /.dockerenv ]] && mkdir -p ~/.ssh
    [[ -f /.dockerenv ]] && chmod 600 ~/.ssh
    [[ -f /.dockerenv ]] && echo -e "Host *\\n\\tStrictHostKeyChecking no\\n\\n"> ~/.ssh/config

    echo -n "#"
    ssh-add <(echo "$1" | tr -d '\\r' )
    echo -n "# Key loaded:  "
    ssh-add -l

  ;;
  *)
    echo "echo OS is $ID, which is unknown to mee, no setup done"
    exit 0
esac
"""

    _SSH_SETUP_NAME = "ssh_setup.sh"

    def __init__(self):
        """Constructor creates ssh setup script

        Keyword arguments:
        ssh_setup_path -- absolute path to temporary created setup shell script
        """
        with open(self._SSH_SETUP_NAME, 'w') as file:
            file.write(self._SSH_SETUP_BASH)
        self.ssh_setup_path = os.path.abspath(self._SSH_SETUP_NAME)
        print(self.ssh_setup_path)

    def __del__(self):
        """Destructor removes ssh setup script

        Keyword arguments:
        """
        os.remove(self.ssh_setup_path)


    def secure_invoke(self, key, invoke):
        """setup a ssh agent, add a private key
        and invokes a shell command in same subprocess
        returns the output

        Keyword arguments:
        key    -- ssh private key
        invoke -- shell command

        """
        bash_cmd = 'eval $(bash ' + self.ssh_setup_path + ' "' + key +'") && ' + invoke
        return _bash_invoke(bash_cmd)
        # rm the ssh setup output and returns just the outpu of invoke
        #return "\n".join(_bash_invoke(bash_cmd).splitlines()[2:])


    def setup(self, key):
        """setup a ssh agent and add a private key

        Keyword arguments:
        key -- ssh private key
        """
        cmd = 'eval $(bash ' + self.ssh_setup_path + ' "' + key +'")'
        _bash_invoke(cmd)


class GitHelper:
    """ git wrapper with ssh

    """

    def __init__(self):
        """Constructor

        Keyword arguments:
        _ssh - ssh helper for secure git comands
        """
        self._ssh = SshHelper()


    def set_user(self, email, name):
        """set global user and email for git actions

        Keyword arguments:
        email -- user email
        name  -- user name
        """
        base = "git config --global user."
        _bash_invoke(base + "email " + email)
        _bash_invoke(base + "name " + name)


    def clone(self, remote_repo, dest_path="", key=None):
        """clone a remote reposetory

        Keyword arguments:
        remote_repo -- repo to clone
        dest_path   -- destionation in local filesystem
        key         -- ssh private key
        """
        cmd = "git clone " + remote_repo + " " + dest_path
        if key:
            self._ssh.secure_invoke(key, cmd)
        else:
            _bash_invoke(cmd)


    def push(self, remote="orgin", key=None, repo_path=None):
        """push local to remote

        Keyword arguments:
        remote    -- remote name
        repo_path -- path to local remote
        """
        cmd = "git push " + remote
        if repo_path:
            cmd = "cd " + repo_path + " && " + cmd
        if key:
            self._ssh.secure_invoke(key, cmd)
        else:
            _bash_invoke(cmd)


    def checkout(self, branch, repo_path=None):
        """check out repo to branch

        Keyword arguments:
        brach     -- branch to check out to
        repo_path -- path to local remote
        """
        cmd = "git checkout " + branch
        if repo_path:
            cmd = "cd " + repo_path + " && " + cmd
        _bash_invoke(cmd)


    def get_commit(self, repo_path=None):
        """retrive commit sha of repo

        Keyword arguments:
        repo_path -- path to local remote
        """
        cmd = 'echo $(git rev-parse HEAD)'
        if repo_path:
            cmd = "cd " + repo_path + " && " + cmd
        return _bash_invoke(cmd)


    def get_branch(self, rep_path=None):
        """retrive current checkouted branch

        Keyword arguments:
        repo_path -- path to local remote
        """
        cmd = 'echo $(git rev-parse --abbrev-ref HEAD)'
        if repo_path:
            cmd = "cd " + repo_path + " && " + cmd
        return _bash_invoke(cmd)


    def add(self, files='*', repo_path=None):
        """add changes to repo

        Keyword arguments:
        files     -- modified files, you want to add into the index
        repo_path -- path to local remote
        """
        if isinstance(files, list):
            files = ' '.join(files)
        cmd = "git add "+ files
        if repo_path:
            cmd = "cd " + repo_path + " && " + cmd
        _bash_invoke(cmd)


    def commit(self, msg="update", repo_path=None):
        """commit indexed changes

        Keyword arguments:
        msg       -- commit message
        repo_path -- path to local remote
        """
        cmd = 'git commit -m "' + msg + '"'
        if repo_path:
            cmd = "cd " + repo_path + " && " + cmd
        _bash_invoke(cmd)


    def add_remote(self, name, url, repo_path=None):
        """set up a new remote

        Keyword arguments:
        name      -- alias of url
        url       -- location of remote
        repo_path -- path to local remote
        """
        cmd = 'git remote add ' + name + ' ' + url
        if repo_path:
            cmd = "cd " + repo_path + " && " + cmd
        _bash_invoke(cmd)


class GitlabApiHelper:
    """ gitlab api wrapper

    Keyword arguments:
    """


    _GITLAB_PROJECTS_URL = "https://gitlab.informatik.haw-hamburg.de/api/v4/projects/"

    _PIPELINE_ID_KEY = "id"
    _PIPELINE_STATUS_KEY =  "status"
    _PIPELINE_STATUS_PENDING = "pending"
    _PIPELINE_STATUS_SUCCESS = "success"
    _PIPELINE_STATUS_FAILED = "failed"
    _PIPELINE_STATUS_NOT_DEFINED = "not defined"


    def end_pipeline(self):
        """ends the running pipeline hard"""
        sys.exit(1)

    def get_job_name(self):
        """ retrieve the current job name"""
        return _bash_invoke("echo $CI_JOB_NAME")


    def get_pipeline_id(self):
        """ retrieve the curren pipeline id"""
        return _bash_invoke("echo $CI_PIPELINE_ID")


    def get_pipeline_status(self, project_id, pipeline_id, api_token):
        """ get pipline status of a project and pipeline

        Keyword arguments:
        project_id  -- project id
        pipeline_id -- pipeline id
        api_token   -- gitlan api token
        """
        url = self._GITLAB_PROJECTS_URL + str(project_id) + "/pipelines"
        header = {"private-token" : api_token}
        status = self._PIPELINE_STATUS_NOT_DEFINED
        PIPELINE_DATA = requests.get(url, headers=header).json()
        for i in range(0, 100):
            if i < len(PIPELINE_DATA):
                if PIPELINE_DATA[i][self._PIPELINE_ID_KEY] == pipeline_id:
                    status = PIPELINE_DATA[i][self._PIPELINE_STATUS_KEY]
                break
            else:
                break
        return status


if __name__ == "__main__":
    print("shell_helper")

    gitlab = GitlabApiHelper()
    print(gitlab.get_job_name())
    print(gitlab.get_pipeline_id())

