#include <iostream>

/* Important note, the first time you run this on a vocore2, you will need to
 * supply the C++ runtime library.  Path below:
 * ./build/vocore2/OpenWrt-Toolchain-ramips-mt7628_gcc-4.8-linaro_uClibc-0.9.33.2.Linux-x86_64/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/lib
 * Actual file name: libstdc++.so.6
 * scp libstdc++.so.6 root@192.168.0.X:/lib/
 */

 /* Configuring the wifi sucked */
// uci set wireless.sta.ssid=[HOME AP SSID]
// uci set wireless.sta.key=[AP PASSWORD]
// uci set wireless.sta.network=wwan
// uci set wireless.sta.disabled=0
// uci set wireless.sta.encryption=psk2
// uci set network.wwan.proto=dhcp
// uci commit
// /etc/init.d/network restart


int main(int argc, char ** argv)
{
    std::cout << "Hello World" << std::endl;
    return 0;
}
