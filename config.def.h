#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0:     pin systray to monitor X */
static const unsigned int systrayonleft = 0;           /* 0: systray in the right corner, >0: systr    ay on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the firs    t monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const char *fonts[]          = {"JetBrainsMono Nerd Font:size=13", "Font Awesome 6 Free Solid:size=13" };
static const char dmenufont[]       = "UbuntuMono:bold:pixelsize=26";
static const char col_gray1[]       = "#282a36";
static const char col_gray2[]       = "#282a36";
static const char col_gray3[]       = "#ffffff";
static const char col_gray4[]       = "#ff71ce";
static const char col_cyan[]        = "#4d4d4d";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff0000";
static const char col_yellow[]      = "#ffff00";
static const char col_white[]       = "#ffffff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] =   { col_gray3, col_gray1,  col_gray2 },
       	[SchemeSel]  =   { col_gray4, col_gray1,   col_gray4 },
       	[SchemeWarn] =   { col_black, col_yellow, col_red },
       	[SchemeUrgent]=  { col_white, col_red,    col_red },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "qBittorrent",  "qbittorrent",       NULL,       2,       0,           -1 },
	{ "Qalculate-gtk",  "qalculate-gtk",       "Qalculate!",       1,       1,           0 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-i", "-l", "24", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browser[] = { "firefox", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,	                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,		        XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY, 			XK_x,	   spawn,	   SHCMD("archlinux-logout") },
	{ MODKEY|ControlMask,           XK_Return, zoom,           {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	
	/* SUPER + SHIFT KEYS */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask, 		XK_Return, spawn,	   SHCMD("thunar") },

	/* CONTROL + ALT KEYS */
	{ Mod1Mask|ControlMask, 	XK_f,	   spawn,	   {.v = browser } },
	{ Mod1Mask|ControlMask, 	XK_b,	   spawn,	    SHCMD("brave") },
	{ Mod1Mask|ControlMask, 	XK_e,	   spawn,	    SHCMD("emacsclient -c -a 'emacs'") },
	{ Mod1Mask|ControlMask, 	XK_c,	   spawn,	    SHCMD("vscodium") },
	{ Mod1Mask|ControlMask, 	XK_p,	   spawn,	    SHCMD("pavucontrol") },
	{ Mod1Mask|ControlMask, 	XK_v,	   spawn,	    SHCMD("virt-manager") },
	{ Mod1Mask|ControlMask, 	XK_s,	   spawn,	    SHCMD("steam") },
	{ Mod1Mask|ControlMask, 	XK_t,	   spawn,	    SHCMD("thunderbird") },
	{ Mod1Mask|ControlMask, 	XK_q,	   spawn,	    SHCMD("qbittorrent") },

	/* MEDIA CONTROL KEYS */
        { 0, XF86XK_AudioMute, spawn, SHCMD("amixer set Master toggle; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume, spawn, SHCMD("amixer set Master 5%-; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume, spawn, SHCMD("amixer set Master 5%+; kill -44 $(pidof dwmblocks)") },
	/* OTHER KEYS */
	{ 0,                       	XK_Print,  spawn,          SHCMD("xfce4-screenshooter") },
	{ MODKEY,                      	XK_Print,  spawn,          SHCMD("thunar ~/Pictures/Screenshots") },
	{ 0,                       	XF86XK_Calculator,      spawn,          SHCMD("qalculate-gtk") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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

