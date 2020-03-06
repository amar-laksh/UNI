#!/bin/bash -
#===============================================================================
#
#          FILE: part2.sh
#
#         USAGE: ./part2.sh
#
#   DESCRIPTION:
#
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Amar Lakshya (), amar.lakshya@xaviers.edu.in
#  ORGANIZATION:
#       CREATED: 05/03/20 23:03:17
#      REVISION:  ---
#===============================================================================

set -o nounset                                  # Treat unset variables as an error
MY_IP="192.168.101.2"

# Flushing all existing chains
sudo iptables -F INPUT &&
sudo iptables -F FORWARD &&
sudo iptables -F OUTPUT &&

# Setting default permit rules
sudo iptables -P INPUT ACCEPT &&
sudo iptables -P OUTPUT ACCEPT &&
sudo iptables -P FORWARD ACCEPT &&

# Allow unlimited traffic on loopback
sudo iptables --append INPUT -i lo -j ACCEPT &&
sudo iptables --append OUTPUT -o lo -j ACCEPT &&

# Setting specific rules according to the part
sudo iptables --append INPUT --protocol tcp --dst $MY_IP --dport 80 --jump DROP &&
sudo iptables --append INPUT --protocol udp --dst $MY_IP --dport 80 --jump DROP
