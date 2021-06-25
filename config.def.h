/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Iosevka Custom:size=10", "Symbols Nerd Font:size=10" };
static const char dmenufont[]       = "Iosevka Custom:size=10";
static const char black[]       = "#000000";
static const char darkGrey[]       = "#444444";
static const char darkWhite[]       = "#bbbbbb";
static const char white[]       = "#ffffff";
static const char blue[]        = "#0000FF";
static const unsigned int baralpha = 0x7F;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { darkWhite, black, darkGrey },
	[SchemeSel]  = { blue, black, blue  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "", "", "拾", "", "", "漣", "", "ﱘ", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	// { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "T",      tile },    /* first entry is default */
	{ "0",      NULL },    /* no layout function means floating behavior */
	{ "F",      monocle },
	{ "B",      bstack },
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
#define TERMINAL "st"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", black, "-nf", darkWhite, "-sb", blue, "-sf", white, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *cmuscmd[]  = { TERMINAL, "-e", "cmus"};

/* Inclue keys like volume keys */
#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd} },
	{ MODKEY,     		        XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_bracketright,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_bracketleft,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_m, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY, 		        XK_x,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_n,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[3]} },
	// { MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_f, 	   togglefloating, {0} },
	{ MODKEY|ShiftMask, 	        XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY, 			XK_q,      quit,           {1} }, 
	{ MODKEY,      	      	        XK_w,      spawn,          SHCMD("firefox") },
	{ MODKEY,      	      	        XK_i,      spawn,          SHCMD("firefox --private-window") },
	{ MODKEY,      	      	        XK_y,      spawn,          SHCMD("firefox --new-window youtube.com") },
	{ MODKEY,      	      	        XK_c,      spawn,          {.v = cmuscmd}},
	{ MODKEY,      	      	        XK_d,      spawn,          SHCMD("discord") },
	{ MODKEY,      	      	        XK_z,      spawn,          SHCMD("zathura") },
	{ MODKEY,      	      	        XK_m,      spawn,          SHCMD("multimc") },
	{ MODKEY|ShiftMask,             XK_Print,  spawn,          SHCMD("flameshot gui") },
	{ MODKEY,      	      	        XK_space,  spawn,          SHCMD("picom -b experimental-backends") },
	{ MODKEY|ShiftMask,             XK_space,  spawn,          SHCMD("pkill picom") },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("xkill") },
	{ MODKEY|ShiftMask,             XK_r,      spawn,          SHCMD("systemctl reboot") },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("systemctl poweroff") },
	{ MODKEY|ShiftMask,             XK_h,      spawn,          SHCMD("systemctl hibernate") },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("systemctl suspend") },
	{ 0,      	      	        XF86XK_AudioRaiseVolume,  spawn,          SHCMD("pulsemixer --change-volume +1") },
	{ 0,      	      	        XF86XK_AudioLowerVolume,  spawn,          SHCMD("pulsemixer --change-volume -1") },
	{ 0,      	      	        XF86XK_AudioMute,  spawn,                 SHCMD("pulsemixer --toggle-mute") },
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

