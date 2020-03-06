#!/bin/bash -
#===============================================================================
#
#          FILE: part3.sh
#
#         USAGE: ./part3.sh
#
#   DESCRIPTION:
#
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Amar Lakshya (), amar.lakshya@xaviers.edu.in
#  ORGANIZATION:
#       CREATED: 05/03/20 23:11:05
#      REVISION:  ---
#===============================================================================

#set -o nounset                                  # Treat unset variables as an error
MY_IP="192.168.101.2"

# Flushing all existing chains
sudo iptables -F INPUT
sudo iptables -F FORWARD
sudo iptables -F OUTPUT

# Setting default permit rules
sudo iptables -P INPUT DROP
sudo iptables -P OUTPUT ACCEPT
#sudo iptables -P FORWARD DROP &&

# Allow unlimited traffic on loopback
sudo iptables --append INPUT -i lo -j ACCEPT
sudo iptables --append OUTPUT -o lo -j ACCEPT

# Setting specific rules according to the part
sudo iptables --append INPUT --protocol tcp --src 0/0 --sport 22 --dst $MY_IP --dport 22 -m state --state NEW,ESTABLISHED,RELATED --jump ACCEPT
#sudo iptables --append OUTPUT --protocol tcp --src $MY_IP --sport 22 -m state --state NEW,ESTABLISHED --jump ACCEPT &&
#sudo iptables --append OUTPUT --protocol udp --src $MY_IP --sport 22 -m state --state NEW,ESTABLISHED --jump ACCEPT &&
sudo iptables --append OUTPUT --jump ACCEPT
