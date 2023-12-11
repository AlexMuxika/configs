SINK=0
SOURCE=1
uptime_formatted=$(uptime | cut -d ',' -f1  | cut -d ' ' -f4,5)
date_formatted=$(date "+%a %F %H:%M")
linux_version=$(uname -r | cut -d '-' -f1)
battery_level_0=$(cat /sys/class/power_supply/cw2015-battery/capacity)
battery_level_1=$(cat /sys/class/power_supply/cw2015-battery/capacity)
hostname=$(hostname)
name=$(whoami)
wifi_name=$(iw dev wlan0 link | grep SSID | cut -d: -f2)
current_brightness=$(brightnessctl | grep Current | cut -d '(' -f2 | cut -d '%' -f1)
current_sink_muted=$(pactl list sinks | grep '^[[:space:]]Mute:' | head -n $(( $SINK + 1 )) | tail -n 1 | cut -d ":" -f2 | sed -e 's/^[ \t]*//')
if [ $current_sink_muted = "yes" ]; then
	sink_icon="  "
else
	sink_icon=" "
fi
current_volume=$(pactl list sinks | grep '^[[:space:]]Volume:' | head -n $(( $SINK + 1 )) | tail -n 1 | sed -e 's,.* \([0-9][0-9]*\)%.*,\1,')
current_source_muted=$(pactl list sources | grep '^[[:space:]]Mute:' | head -n $(( $SOURCE + 1 )) | tail -n 1 | cut -d ":" -f2 | sed -e 's/^[ \t]*//')
if [ $current_source_muted = "yes" ]; then
	source_icon=""
else
	source_icon=" "
fi
current_source_volume=$(pactl list sources | grep '^[[:space:]]Volume:' | head -n $(( $SOURCE + 1 )) | tail -n 1 | sed -e 's,.* \([0-9][0-9]*\)%.*,\1,')
current_mem=$(free | grep Mem | awk '{print $3/$2 * 100.0}')
current_mem_rounded=`printf "%.2f" $current_mem`
current_cpu=$(cat /proc/stat | grep 'cpu ' | awk '{print ($2+$4)*100/($2+$4+$5)}')
current_cpu_rounded=`printf "%.2f" $current_cpu`
battery_status0=$(cat /sys/class/power_supply/cw2015-battery/status)
battery_status1=$(cat /sys/class/power_supply/cw2015-battery/status)
x=$(paste /sys/class/power_supply/cw2015-battery/energy_full_design /sys/class/power_supply/cw2015-battery/energy_full_design | awk '{print $1/$2}')
perc_1=$(echo "1/(1+$x)" | bc -l)
battery_level=$(echo "(1-$perc_1)*$battery_level_0 + $perc_1*$battery_level_1" | bc -l)
battery_level_rounded=`printf "%.0f" $battery_level`
if [ $battery_status0 = "Charging" ] || [ $battery_status1 = "Charging" ]; then
	battery_icon=""
else
	if [ $battery_level_0 -ge 95 ]; then
		battery_icon=""
	elif [ $battery_level_0 -ge 85 ]; then
		battery_icon=""
	elif [ $battery_level_0 -ge 75 ]; then
		battery_icon=""
	elif [ $battery_level_0 -ge 65 ]; then
		battery_icon=""
	elif [ $battery_level_0 -ge 55 ]; then
		battery_icon=""
	elif [ $battery_level_0 -ge 45 ]; then
		battery_icon=""
	elif [ $battery_level_0 -ge 35 ]; then
		battery_icon=""
	elif [ $battery_level_0 -ge 25 ]; then
		battery_icon=""
	elif [ $battery_level_0 -ge 15 ]; then
		battery_icon=""
	else
		battery_icon=""
	fi
fi
echo " $wifi_name   $current_brightness%  $sink_icon $current_volume%   $current_cpu_rounded%    $current_mem_rounded%  $battery_icon  $battery_status0  $battery_level_0%   $date_formatted"
