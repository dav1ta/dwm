/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:style:medium:size=14",
                                        "Material Design Icons-Regular:size=14" };
static const char dmenufont[]       = "monospace:size=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#225577";
static const char col_border[]        = "#fcd095";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_border },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                  instance    title           tags mask   switchtotag  isfloating   monitor */
	{ "Gimp",                 NULL,       NULL,           0,               0,            1,           -1 },
	{ "firefox",              NULL,       NULL,           1 << 0,          0,           0,           -1 },
	{ "jetbrains-pycharm",    NULL,       NULL,           1 << 2,          0,           0,           -1 },
	{ "Skype",                NULL,       NULL,           1 << 8,          0,           0,           -1 },
	{ "subl",                 NULL,       NULL,           1 << 4,          0,           0,           -1 },
	{ "mpv",                  NULL,       NULL,           0,               0,           1,           -1 },
	{ NULL,                   NULL,       "st_float",     0,               0,           1,           -1 },
};


/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[H]",      grid },
    { "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod1Mask
#define WINKEY Mod4Mask
#define CONT ControlMask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st","-t","st_tag",NULL };
static const char *termcmdfloat[]  = { "st", "-t","st_float","-g", "100x30", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "100x30", NULL };


static Key keys[] = {

	/* modifier             key    function        argument */
	{ MODKEY,               24,    killclient,     {0} },
	{ WINKEY,       		    65,    spawn,          SHCMD("setxkbmap -query | grep -q 'ge,us' && setxkbmap us || setxkbmap ge,us; pkill -RTMIN+1 dwmblocks") },
	{ MODKEY,            	  26,    spawn,          SHCMD("firefox") },
	{ MODKEY,            	  53,    spawn,          SHCMD("/home/davit/.local/scripts/launch_buffer_python.py") },
	{ 0,                    123,   spawn,          SHCMD("amixer -c 2 -q sset Master 10%+ && pkill -RTMIN+2 dwmblocks") },
	{ 0,                    122,   spawn,          SHCMD("amixer -c 2 -q sset Master 10%- && pkill -RTMIN+2 dwmblocks") },
	{ 0,                    121,   spawn,          SHCMD("amixer -c 2 set Capture toggle && pkill -RTMIN+2 dwmblocks") },
	{ 0,                    232,   spawn,          SHCMD("brightnessctl s 10%-") },
	{ 0,                    233,   spawn,          SHCMD("brightnessctl s +10%") },
	{ MODKEY,               33,    spawn,          SHCMD("/home/davit/.local/launch/pycharm") },
	{ 0,                    107,   spawn,          SHCMD("/home/davit/.local/scripts/screenshot.sh") },
	{ MODKEY,               42,    spawn,          {.v = dmenucmd } }, // g */
  { MODKEY,             55,    setlayout,        {.v = &layouts[3]} },
	{ MODKEY,               27,    spawn,          {.v = termcmdfloat } }, // R
	{ MODKEY,               56,    togglebar,      {0} },             // b
	{ MODKEY,               44,    focusstack,     {.i = +1 } },      // j
	{ MODKEY,               45,    focusstack,     {.i = -1 } },      // k
	{ MODKEY,               31,    incnmaster,     {.i = +1 } },      // i
	{ MODKEY,               32,    incnmaster,     {.i = -1 } },      // o
	{ MODKEY,               43,    setmfact,       {.f = -0.05} },    // h
	{ MODKEY,               46,    setmfact,       {.f = +0.05} },    // l
	{ MODKEY,               36,    zoom,           {0} },             // Return
	{ MODKEY,               23,    view,           {0} },             // Tab
	{ MODKEY|ShiftMask,     54,    killclient,     {0} },             // c
	{ MODKEY,               28,    setlayout,      {.v = &layouts[0]} }, // t
	// { MODKEY,               41,    setlayout,      {.v = &layouts[1]} }, // f
  { MODKEY,               41,    togglefullscr,  {0} },
	{ MODKEY,               57,    setlayout,      {.v = &layouts[4]} },
	{ MODKEY,               58,    setlayout,      {.v = &layouts[2]} }, // m
	{ MODKEY,               65,    setlayout,      {0} },             // space
	{ CONT,                 65,    togglefloating, {0} },             // space
	{ MODKEY,               19,    view,           {.ui = ~0 } },     // 0
	{ MODKEY|ShiftMask,     19,    tag,            {.ui = ~0 } },     // 0
	{ MODKEY,               59,    focusmon,       {.i = -1 } },      // comma
	{ WINKEY,               23,    focusmon,       {.i = +1 } },      // period
	{ MODKEY|ShiftMask,     59,    tagmon,         {.i = -1 } },      // comma
	{ MODKEY|ShiftMask,     36,    spawn,          {.v = termcmd}},      //Enter
	{ MODKEY,     			    40,    tagmon,         {.i = +1 } },      // period
  { MODKEY,               25,      winview,      {0} },
  { MODKEY,               49,  togglescratch,  {.v = scratchpadcmd } },
	TAGKEYS(                10,                    0)                 // 1
	TAGKEYS(                11,                    1)                 // 2
	TAGKEYS(                12,                    2)                 // 3
	TAGKEYS(                13,                    3)                 // 4
	TAGKEYS(                14,                    4)                 // 5
	TAGKEYS(                15,                    5)                 // 6
	TAGKEYS(                16,                    6)                 // 7
	TAGKEYS(                17,                    7)                 // 8
	TAGKEYS(                18,                    8)                 // 9
	{ MODKEY|ShiftMask,     26,    quit,           {0} },             // q
 };
/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

