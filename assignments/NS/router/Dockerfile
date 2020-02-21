FROM ubuntu:latest
RUN apt-get update && apt-get install -y locales && rm -rf /var/lib/apt/lists/* \
										&& localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8
										ENV LANG en_US.utf8
										RUN  apt-get update && apt-get install -y net-tools iputils-ping iptables sudo tcpdump iproute2 && echo "net.ipv4.conf.all.forwarding=1" >> /etc/sysctl.conf && echo "net.ipv4.ip_forward=1" >> /etc/sysctl.conf

