
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
  debian|ubuntu)
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
    [[ -f /.dockerenv ]] && echo -e "Host *\n\tStrictHostKeyChecking no\n\n"> ~/.ssh/config

    echo -n "#"
    ssh-add <(echo "$1" | tr -d '\r' )
    echo -n "# Key loaded:  "
    ssh-add -l

  ;;
  *)
    echo "echo OS is $ID, which is unknown to mee, no setup done"
    exit 0
esac
