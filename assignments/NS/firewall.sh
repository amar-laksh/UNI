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
#sudo docker pull ubuntu && \
sudo docker build  -t ubuntu-router router/ &&
sudo docker build  -t ubuntu-client client/ &&
sudo docker build  -t ubuntu-server server/ &&

sudo docker network create --driver=bridge --subnet=192.168.100.0/24  client-net && \
sudo docker network create --driver=bridge --subnet=192.168.101.0/24  server-net && \

sudo docker create -it --network=client-net --name=client --hostname=client ubuntu-client /bin/bash && \
sudo docker create -it --network=server-net --name=server --hostname=server ubuntu-server /bin/bash && \
sudo docker create -it --network=server-net --name=router --hostname=router ubuntu-router /bin/bash && \
sudo docker network connect client-net router && \
sudo docker start router && \
sudo docker start client && \
sudo docker start server && \

# Attaching containers to the networks
#sudo docker run -itd --network=client-net --name=client --hostname=client ubuntu-client /bin/bash && \
#sudo docker run -itd --network=server-net --name=server --hostname=server ubuntu-server /bin/bash && \
#sudo docker run -itd --network=server-net --name=router --hostname=router ubuntu-router /bin/bash && \
#sudo docker network connect client-net router && \
##sudo docker start router && \
#


# Executing containers to the networks
tmux split-window "sudo docker exec -it  --privileged router bash -c '/bin/bash'" && \
tmux split-window "sudo docker exec -it  --privileged client bash -c '. /etc/apache2/envvars && mkdir -p /var/run/apache2 && /bin/bash'" && \
tmux split-window "sudo docker exec -it  --privileged server bash -c '. /etc/apache2/envvars && mkdir -p /var/run/apache2 && /bin/bash'"
