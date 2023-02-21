import sys
import argparse
import ssh_agent_setup
import subprocess as sp
import os

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="git push and pull via ssh wrapper")
    parser.add_argument("key", type=str, help="RSA Private Key")
    parser.add_argument("-clone", nargs=1, type=str, metavar=("url"),
                        help="--")
    parser.add_argument("-push", nargs=1, type=str, metavar=("remote"),
                        help="--")
    parser.add_argument("-pull", nargs=1, type=str, metavar=("remote"),
                        help="--")
    #parser.add_agrument("pid", type= int, help="projectid of CAC to terminate ")
    args = parser.parse_args()
    key = args.key
    #key = SSH_PRIVATE_KEY
    #print(key)
    with open('id_rsa', 'w') as file:
        file.write(key)
        os.chmod('./id_rsa', 0o600)
    #o=sp.run(["chmod", "600", "id_rsa"], shell=True)
    ssh_agent_setup.setup()
    ssh_agent_setup.addKey( './id_rsa' )
    output=sp.check_output("ssh-agent -s", shell=True)
    print(output)
    output=sp.check_output("mkdir -p ~/.ssh", shell=True)
    print(output)
    output=sp.check_output(
        '[[ -f /.dockerenv ]] && echo -e "Host *\n\tStrictHostKeyChecking no\n\n"> ~/.ssh/config',
        shell=True) 
    print(output)
    #print(type(output))
    #o=sp.run(["eval ", output], shell=True)
    #print(o)
    #o=sp.run(["ssh-add", key], shell=True, stdout=sp.DEVNULL)
    #print(o)
    #o=sp.run(["ssh-add","-l"], shell=True)
    #print(o)
    print(args.clone[0])
    if args.clone:
        o=sp.check_output("git clone " + args.clone[0], shell=True)
    elif args.push:
        o=sp.check_output("git push " + args.push[0], shell=True)
    elif args.pull:
        o=sp.check_output("git pull " + args.pull[0], shell=True)
    print(o)
    ##
    ## Create the SSH directory and give it the right permissions
    ##
    #o=sp.run(["mkdir", "-p",  "~/.ssh"], shell=True)
    #o=sp.run(["chmod", "700", "~/.ssh"], shell=True)
    #cdr_url = "git@gitlab.informatik.haw-hamburg.de:CIES/TCDR.git"
    #o=sp.run(["git", "clone", cdr_url, "PROJECT"], shell=True)
    #o=sp.run(["ls -la"], shell=True)