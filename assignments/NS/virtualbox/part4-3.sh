#!/bin/bash -
#===============================================================================
#
#          FILE: part4-3.sh
#
#         USAGE: ./part4-3.sh
#
#   DESCRIPTION:
#
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Amar Lakshya (), amar.lakshya@xaviers.edu.in
#  ORGANIZATION:
#       CREATED: 05/03/20 23:30:46
#      REVISION:  ---
#===============================================================================

set -o nounset                                  # Treat unset variables as an error
SERVERNET="192.168.101.2/24"
CLIENTNET="192.168.100.2/24"

# Flushing all existing chains
sudo iptables -F INPUT &&
sudo iptables -F FORWARD &&
sudo iptables -F OUTPUT &&

# Setting default permit rules
sudo iptables -P INPUT ACCEPT &&
sudo iptables -P OUTPUT ACCEPT &&
sudo iptables -P FORWARD DROP &&

# Allow unlimited traffic on loopback
sudo iptables --append INPUT -i lo -j ACCEPT &&
sudo iptables --append OUTPUT -o lo -j ACCEPT &&

# Setting specific rules according to the part
sudo iptables --append FORWARD --protocol tcp --dst $SERVERNET --dport 22 --jump ACCEPT &&
sudo iptables --append FORWARD --protocol udp --dst $SERVERNET --dport 22 --jump ACCEPT
