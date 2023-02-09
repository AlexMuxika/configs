/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 1;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int stairpx   = 20;       /* depth of the stairs layout */
static const int stairdirection     = 1;        /* 0: left-aligned, 1: right-aligned */
static const int stairsamesize      = 1;        /* 1 means shrink all the staired windows to the same size */
static const char *fonts[]          = { "fontawesome-regular:size=12" };
static const char dmenufont[]       = { "fontawesome-regular:size=12" };

#include "/home/muxika/.cache/wal/colors-wal-dwm.h"

static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
static const char *tagsalt[] = {  "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const int momentaryalttags = 0; /* 1 means alttags will show only when key is held down*/
static const char *defaulttagapps[] = { "qutebrowser","st -e aerc", NULL, NULL, "kdeconnect-sms", NULL, "libreoffice", NULL, "steam" };

#include <X11/XF86keysym.h>

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int attachdirection = 0;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

#include "grid.c"
#include "tatami.c"
#include "fibonacci.c"
#include "horizgrid.c"
#include "tcl.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|[T]|",      tcl },
	{ "DD",       doubledeck },
	{ "[][]=",    tilewide },
	{ "|+|",      tatami },
	{ "|||",      col },
	{ "HHH",      grid },
	{ "###",      horizgrid },
 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
	{ "[S]",      stairs },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL, NULL, NULL, NULL, NULL };
static const char *termcmd[] = { "st", NULL };
static const char *tterm[]  = { "tabbed", "-c", "st", "-w", NULL };
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };
static const char *update[] = { "st", "-e", "yay", "-Syu", NULL };
static const char *play[] = { "playerctl", "play-pause", NULL, NULL, NULL };
static const char *next[] = { "playerctl", "next", NULL, NULL, NULL };
static const char *prev[] = { "playerctl", "prev", NULL, NULL, NULL };
static const char *up[]   = { "xbacklight", "-inc", "5", NULL, NULL };
static const char *down[] = { "xbacklight", "-dec", "5", NULL, NULL };
static const char *kbup[]  = { "brightnessctl", "-d", "smc::kbd_backlight", "s", "+5%", NULL };
static const char *kbdown[] = { "brightnessctl", "-d", "smc::kbd_backlight", "s", "5%-", NULL };
static const char *email[] = { "st", "-e", "aerc", NULL};
static const char *calendar[] = { "st", "-e", "calcurse", NULL };
static const char *tasks[] = { "st", "-e", "vim", "/home/muxika/Notes/todo.txt", NULL };
static const char *vifmimg[] = { "st", "-e", "/home/muxika/.config/vifm/scripts/vifmrun", NULL };
static const char *cmus[] = { "st", "-e", "cmus", NULL };
static const char *gomuks[] = { "st", "-e", "gomuks", NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ Mod4Mask,                     XK_x,      spawn,          {.v = gomuks } },
	{ Mod4Mask, 			XK_m,	   spawn, 	   {.v = email } },
	{ Mod4Mask, 			XK_c,      spawn,          {.v = calendar } },
	{ Mod4Mask,                     XK_t,      spawn,          {.v = tasks } },
	{ Mod4Mask,			XK_e,      spawn,	   {.v = vifmimg } },
	{ Mod4Mask,			XK_p,	   spawn,	   {.v = cmus } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          {.v = tterm } },
	{ MODKEY,                       XK_s,      spawndefault,   {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_j,      inplacerotate,  {.i = +1} },
	{ MODKEY|ControlMask,           XK_k,      inplacerotate,  {.i = -1} },
	{ MODKEY|ControlMask,           XK_h,      inplacerotate,  {.i = +2} },
	{ MODKEY|ControlMask,           XK_l,      inplacerotate,  {.i = -2} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
/*	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },*/
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
/*	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },*/
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
/*	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },*/
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
/*	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[3]} },*/
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,			XK_g,	   setlayout,	   {.v = &layouts[5]} },
	{ MODKEY,                       XK_w,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
	{ 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                       XF86XK_AudioMute, spawn, {.v = mutevol } },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
	{ MODKEY,                       XK_u,      spawn,          {.v = update } }, 
        { 0,                       XF86XK_AudioNext, spawn, {.v = next } },
	{ 0,                       XF86XK_AudioPrev, spawn, {.v = prev } },
	{ 0,                       XF86XK_AudioPlay, spawn, {.v = play } },
	{ 0,                       XF86XK_MonBrightnessUp, spawn, {.v = up } },
	{ 0,                       XF86XK_MonBrightnessDown, spawn, {.v = down } },
	{ 0,                       XF86XK_KbdBrightnessDown, spawn, {.v = kbdown } },
	{ 0,                       XF86XK_KbdBrightnessUp,   spawn, {.v = kbup } },
	{ MODKEY,                       XK_minus, scratchpad_show, {0} },
	{ MODKEY|ShiftMask,             XK_minus, scratchpad_hide, {0} },
	{ MODKEY,                       XK_equal,scratchpad_remove,{0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

