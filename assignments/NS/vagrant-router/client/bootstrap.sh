#!/bin/bash -
#===============================================================================
#
#          FILE: bootstrap.sh
#
#         USAGE: ./bootstrap.sh
#
#   DESCRIPTION:
#
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: YOUR NAME (),
#  ORGANIZATION:
#       CREATED: 21/02/20 12:57:02
#      REVISION:  ---
#===============================================================================

set -o nounset                                  # Treat unset variables as an error

#!/usr/bin/env bash

apt-get update
apt-get install -y apache2
if ! [ -L /var/www ]; then
  rm -rf /var/www
  ln -fs /vagrant /var/www
fi

