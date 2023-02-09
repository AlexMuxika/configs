#!/bin/sh

userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/etc/X11/xinit/.Xresources
sysmodmap=/etc/X11/xinit/.Xmodmap

# merge in defaults and keymaps

if [ -f $sysresources ]; then







    xrdb -merge $sysresources

fi

if [ -f $sysmodmap ]; then
    xmodmap $sysmodmap
fi

if [ -f "$userresources" ]; then







    xrdb -merge "$userresources"

fi

if [ -f "$usermodmap" ]; then
    xmodmap "$usermodmap"
fi

# start some nice programs

if [ -d /etc/X11/xinit/xinitrc.d ] ; then
 for f in /etc/X11/xinit/xinitrc.d/?*.sh ; do
  [ -x "$f" ] && . "$f"
 done
 unset f
fi

# start the dwm status bar

# backlight
blt() {
	blt="$(xbacklight -get | cut -c -3)"
	echo -e " $blt"
}

# cmus stream
cst() {
	cst="$(cmus-remote -Q | grep -w 'stream'     | cut -c 7-)"
	echo -e "$cst"
}

# cmus tag artist
cta() {
	cta="$(cmus-remote -Q | grep -w 'tag artist' | cut -c 11-)"
	echo -e "$cta"
}

# cmus tag title
ctt() {
	ctt="$(cmus-remote -Q | grep -w 'tag title'  | cut -c 11-)"
	echo -e "$ctt"
}

# date
dte() {
	dte="$(date +' %A, %B %d, %Y, %I:%M %p')"
	echo -e " $dte"
}

# memory
mmy() {
	mmy="$(free -h | grep Mem | awk '{print $3"/"$2}' | sed s/i//g)"
	echo -e " $mmy"
}

# network
nwk() {
	nwk="$(nmcli device show wlo1 | grep 'GENERAL.CONNECTION' | cut -c 41-)"
	echo -e " $nwk"
}

# battery power
pwr() {
	pwr="$(cat /sys/class/power_supply/BAT0/capacity)"
	echo -e " $pwr"
}

# updates
upd() {
	upd="$(checkupdates-with-aur | wc | awk '{print $1}')"
	echo -e " $upd"
}

# volume
vol() {
	vol="$(pulsemixer --get-volume | awk '{print $1}')"
	echo -e " $vol"
}

# weather
wtr() {
	wtr="$(curl -s wttr.in/Orangetree?format=1)"
	echo -e "$wtr"
}

# status bar
while true; do
	xsetroot -name "$(cta)  $(ctt)  $(cst)  $(upd)  $(nwk)  $(vol)  $(pwr)  $(mmy)  $(blt)  $(dte)  $(wtr)"
	sleep 1s
done &

eval $(gnome-keyring-daemon --start) &
export SSH_AUTH_SOCK &
xset -dpms s off &
xset s off &
xset -dpms &
xinput set-prop 11 275 1 &
xinput set-prop 11 283 1 &
numlockx &
#/home/muxika/.local/bin/dwm-bar/dwm_bar.sh &
#wal -R &
#picom --config ~/.config/picombare.conf &
picom --config ~/.config/picomshadow.conf &
# picom &
feh --bg-fill -z ~/Pictures/Wallpaper &
#feh --bg-fill -z ~/Pictures/Wallpaper/nord &
nextcloud --background &
exec dwm
