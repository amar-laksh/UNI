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
sudo iptables -P FORWARD ACCEPT &&

# Allow unlimited traffic on loopback
sudo iptables --append INPUT -i lo -j ACCEPT &&
sudo iptables --append OUTPUT -o lo -j ACCEPT &&

# Setting specific rules according to the part
sudo iptables -A FORWARD -m conntrack --src $SERVERNET --ctstate ESTABLISHED,RELATED,RELATED -j ACCEPT &&
sudo iptables --append FORWARD --protocol tcp --dst $SERVERNET --dport 22 -m conntrack --ctstate NEW,ESTABLISHED,RELATED --jump ACCEPT &&
sudo iptables --append FORWARD --protocol all --src $SERVERNET --jump ACCEPT &&
sudo iptables --append FORWARD --protocol all --dst $SERVERNET --jump DROP
