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
#       CREATED: 06/03/20 02:34:45
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


# Setting specific rules according to the part4-2
sudo iptables --append FORWARD --protocol tcp --dst $SERVERNET --dport 80 --jump logdrop &&
sudo iptables --append FORWARD --protocol udp --dst $SERVERNET --dport 80 --jump logdrop

# Setting specific rules according to the part4-3
#sudo iptables -A FORWARD -m conntrack --src $SERVERNET --ctstate ESTABLISHED,RELATED,RELATED -j ACCEPT &&
#sudo iptables -A FORWARD -m conntrack --dst $SERVERNET --ctstate ESTABLISHED,RELATED,RELATED -j ACCEPT &&
#sudo iptables --append FORWARD --protocol tcp --dst $SERVERNET --dport 22 -m conntrack --ctstate NEW,ESTABLISHED,RELATED --jump ACCEPT &&
#sudo iptables --append FORWARD --protocol all --src $SERVERNET --jump ACCEPT &&
#sudo iptables --append FORWARD --protocol all --dst $SERVERNET --jump logdrop
