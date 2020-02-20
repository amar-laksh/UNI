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
#sudo docker build --no-cache -t ubuntu .

# Creating server-net and client-net networks
sudo docker network create --driver=bridge --subnet=192.168.100.0/24 --ip-range=192.168.100.1/24  client-net && \
sudo docker network create --driver=bridge --subnet=192.168.101.0/24 --ip-range=192.168.101.1/24  server-net && \

# Attaching containers to the networks
sudo docker run -itd --network=client-net --name=client ubuntu /bin/bash && \
sudo docker run -itd --network=server-net --name=server ubuntu /bin/bash && \

# Creating and attaching router container to both server-net and client-net networks
#sudo docker run -itd --network=server-net --name=router ubuntu /bin/bash && \
sudo docker create -it --network=server-net  --name=router ubuntu /bin/bash && \
sudo docker network connect client-net router && \
sudo docker start router && \
# Executing containers to the networks
#tmux set-option remain-on-exit on
tmux split-window "sudo docker exec -it client bash -c 'echo \"192.168.101.2 server\" >> /etc/hosts && cat /etc/hosts'"  && \
tmux split-window "sudo docker exec -it server bash -c 'echo \"192.168.100.2 client\" >> /etc/hosts && cat /etc/hosts'" && \
tmux split-window "sudo docker exec -it router bash -c 'cat /etc/hosts'"
