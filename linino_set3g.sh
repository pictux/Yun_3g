#!/bin/sh
#title	: linino_set3g.sh
#description	: this script installs all packages needed to enable 3g/umts networking;
#		then configure network device 
#author	: Mirco Piccin (www.xuni.it | www.pictux.org)
#date	: 2013-11
#version : 0.1
#usage	: sh linino_set3g.sh -d DEVICE -a APN -p PIN
#disabled PIN is a problem!

IFCONF=/etc/config/network 
TGCHAT=/etc/chatscripts/3g.chat
FWCONF=/etc/config/firewall
CHECK3G=/root/check3g.sh

DEV="" 
PIN="" 
APN=""

while getopts a:p:d: OPTION
do
  case $OPTION in 
     d)
        DEV=$OPTARG
	;;
     p)
	PIN=$OPTARG
	;;
     a)
	APN=$OPTARG
	;;
  esac
done

if test -z  "$DEV" || test -z "$PIN" || test -z "$APN"; then
   echo "Something Empty!"
   exit 1
fi



#INSTALL PACKAGES
/bin/opkg update
wait
/bin/opkg install unzip kmod-usb2 kmod-usb-core kmod-usb-serial kmod-usb-serial-option kmod-usb-serial-wwan usb-modeswitch usb-modeswitch-data libusb-1.0 comgt chat
wait
/usr/bin/curl -k https://raw.github.com/pictux/Yun_3g/master/luci-proto-3g_svn-r9931-1_ar71xx.ipk -o /tmp/luci-proto-3g_svn-r9931-1_ar71xx.ipk
wait
/bin/opkg install /tmp/luci-proto-3g_svn-r9931-1_ar71xx.ipk


#CREATE INTERFACE (if already exist an interface ppp0, backup the file)
if ! [ -r $IFCONF.bck0 ]; then
	/bin/cat $IFCONF > $IFCONF.bck0
else
	/bin/cat $IFCONF > $IFCONF.bck1
fi     

/bin/cat $IFCONF.bck0 > $IFCONF

/bin/cat <<EOF >> $IFCONF
config interface wan2
        option ifname  ppp0
        option pincode $PIN
        option device  $DEV
        option apn     $APN
        option service umts
        option proto   3g
EOF

#SCRIPT TO CHECK CONNECTIVITY
/bin/cat <<EOF > $CHECK3G
#!/bin/sh
if ! ping -q -c 1 -W 10 -I 3g-wan 8.8.8.8 > /dev/null; then
	(ifup wan; sleep 5; /etc/init.d/multiwan restart) &
fi
EOF

/bin/chmod $CHECK3G 755

#UPDATE ROOT CRONTAB
/bin/echo "*/2 * * * * /root/$CHECK3G" >> /etc/crontabs/root

#UPDATE CHAT SCRIPT
if ! [ -r $TGCHAT.bck0 ]; then
	/bin/cat $TGCHAT > $TGCHAT.bck0
fi

/bin/sed 's/ATD\*99\*\*\*1\#/ATD\*99\#/' $TGCHAT.bck0 > $TGCHAT

#UPDATE FIREWALL CONF
if ! [ -r $FWCONF.bck0 ]; then
        /bin/cat $FWCONF > $FWCONF.bck0
fi

/bin/sed {s/\'wan\'/\'wan\ wan2\'/} $FWCONF.bck0 > $FWCONF

#RESTART CRON
/etc/init.d/cron restart

#DO A REBOOT!

