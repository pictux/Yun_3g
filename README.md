**YUN 3G**

Here you can find an Arduino sketch<br />
YUN_3g_set.ino<br />
that allows you to configure your YUN to connect to a 3G/UMTS network.

Basically this sketch downloads from this repository the script<br />
linino_set3g.sh<br />
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
luci-proto-3g_svn-r9931-1_ar71xx.ipk<br />
is the luci page for 3g configuration.

You can find more information about 3g connection on the following OpenWRT page:
http://wiki.openwrt.org/doc/recipes/3gdongle

Printscreen of luci-3g-proto page<br />
![alt tag](https://raw.github.com/pictux/Yun_3g/master/luci_proto_3g.png)

Printscreen of luci-firewall with wan zone updated<br />
![alt tag](https://raw.github.com/pictux/Yun_3g/master/luci_firewall.png)

