#!/bin/bash -
#===============================================================================
#
#          FILE: part5.sh
#
#         USAGE: ./part5.sh
#
#   DESCRIPTION:
#
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Amar Lakshya (), amar.lakshya@xaviers.edu.in
#  ORGANIZATION:
#       CREATED: 06/03/20 02:45:41
#      REVISION:  ---
#===============================================================================

set -o nounset                                  # Treat unset variables as an error

SERVERNET="192.168.101.2/24"
CLIENTNET="192.168.100.2/24"

# Creating a separate logging chain for clean log drops
sudo iptables -N logdrop &&
sudo iptables -A logdrop -m limit --limit 1/s --limit-burst 100 -j LOG &&
sudo iptables -A logdrop -j DROP &&

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

# Deny all traffic except known addresses
sudo iptables -A PREROUTING --protocol all ! --src $SERVERNET --jump DROP &&
sudo iptables -A PREROUTING --protocol all ! --src $CLIENTNET --jump DROP
