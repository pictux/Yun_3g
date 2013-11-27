**YUN 3G**

Here you can find an Arduino sketch<br />
<i>YUN_3g_set.ino</i><br />
that allows you to configure your YUN to connect to a 3G/UMTS network.

Basically this sketch downloads from this repository the script<br />
<i>linino_set3g.sh</i><br />
and executes it.

The script linino_set3g.sh does the following:
- installs all required packages (available in repository)
- downloads and installs the binary package 'lucti-proto-3g' available in this repository
- creates the new interface (wan2) in the /etc/config/network file
- creates the script /root/check3g.sh to maintain the 3g connection up and running,
        and adds it to the root contab (check every 5 seconds)
- updates firewall wan zones

Of course you can download directly from the CLI the script and execute it, or run manually every command.

The binary package that i built for the Arudino Yun:<br />
<i>luci-proto-3g_svn-r9931-1_ar71xx.ipk</i><br />
is the luci page for 3g configuration.

You can find more information about 3g connection on the following OpenWRT page:<br />
http://wiki.openwrt.org/doc/recipes/3gdongle



Printscreen of <i>luci-3g-proto</i> page, where you can see the new interface <b>WAN2</b><br />
![alt tag](https://raw.github.com/pictux/Yun_3g/master/luci_proto_3g.png)

Printscreen of <i>luci-firewall</i> where you can see the wan zone updated with <i>wan2</i> interface<br />
![alt tag](https://raw.github.com/pictux/Yun_3g/master/luci_firewall.png)

