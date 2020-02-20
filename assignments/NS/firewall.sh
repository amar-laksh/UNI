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
#sudo docker network create --driver=bridge --subnet=192.168.100.0/24  client-net && \
#sudo docker network create --driver=bridge --subnet=192.168.101.0/24  server-net && \
#
# Attaching containers to the networks
sudo docker run --network=client-net --ip 192.168.100.2 -itd --name=client ubuntu /bin/bash && \
sudo docker run --network=server-net --ip 192.168.101.2 -itd --name=server ubuntu /bin/bash && \
# Creating and attaching router container to both server-net and client-net networks
sudo docker run --network=server-net --ip 192.168.101.1 -itd --name=router ubuntu /bin/bash && \
exit 0 && \
sudo docker create --network=server-net --ip 192.168.101.1 -it --name=router ubuntu /bin/bash && \
sudo docker create --network=server-net --ip 192.168.101.1 -it --name=router ubuntu /bin/bash && \
sudo docker network connect --ip 192.168.100.1 client-net router && \

# Executing containers to the networks
#tmux set-option remain-on-exit on
tmux split-window "sudo docker exec -it client bash -c 'echo \"192.168.101.2 server\" >> /etc/hosts && cat /etc/hosts'"  && \
tmux split-window "sudo docker exec -it server bash -c 'echo \"192.168.100.2 client\" >> /etc/hosts && cat /etc/hosts'" && \
tmux split-window "sudo docker exec -it router bash -c 'ifconfig'"
