#!/bin/bash -
#===============================================================================
#
#          FILE: firewall.sh
#
#         USAGE: ./firewall.sh
#
#   DESCRIPTION:
#
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: YOUR NAME (),
#  ORGANIZATION:
#       CREATED: 20/02/20 16:03:55
#      REVISION:  ---
#===============================================================================

set -o nounset                                  # Treat unset variables as an error

# Docker installation section
# Pulling and setting up docker script
sudo docker pull ubuntu && \
#sudo docker build  -t ubuntu-router router/ && \
sudo docker build  -t ubuntu-client client/ && \
sudo docker build  -t ubuntu-server server/ && \

sudo docker network create --driver=bridge --subnet=192.168.100.0/24 --ip-range=192.168.100.1/24  client-net && \
sudo docker network create --driver=bridge --subnet=192.168.101.0/24 --ip-range=192.168.101.1/24  server-net && \

sudo docker create -it --network=client-net --name=client --hostname=client ubuntu-client /bin/bash && \
sudo docker create -it --network=server-net --name=server --hostname=server ubuntu-server /bin/bash && \
sudo docker create -it -p 2222:22 -p 8728:8728 -p 8729:8729 -p 5900:5900  -p 8080:80 --network=server-net --name=router --hostname=router ubuntu-router vrnetlab/vr-routeros /bin/bash && \
sudo docker network connect client-net router && \
sudo docker start router && \
sudo docker start client && \
sudo docker start server && \

# Executing containers to the networks
tmux split-window "sudo docker exec -it  --privileged router bash -c '/bin/bash'" #&& \
tmux split-window "sudo docker exec -it  --privileged client bash -c '. /etc/apache2/envvars && mkdir -p /var/run/apache2 && /bin/bash'" && \
tmux split-window "sudo docker exec -it  --privileged server bash -c '. /etc/apache2/envvars && mkdir -p /var/run/apache2 && /bin/bash'"
