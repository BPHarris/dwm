/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const int startwithgaps[]    = { 1 };	/* 1 means gaps are used by default, this can be customized for each tag */
static const unsigned int gappx[]   = { 10 };   /* default gap between windows in pixels, this can be customized for each tag */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *alttrayname      = "tray";    /* Polybar tray instance name */
static const char *altbarcmd        = "~/.config/dwm/startbar"; /* Alternate bar launch command */
static const int focusonwheel       = 0;        /* 0 means allow mouse wheel click */
static const int decorhints         = 0;        /* 1 means respect decoration hints */
static const char *fonts[]          = { "FiraCode Nerd Font Mono:size=13" };
static const char dmenufont[]       = "FiraCode Nerd Font Mono:size=13";


/* colour */
static const char c_black[]       = "#080808";
static const char c_dark_grey[]   = "#161616";
static const char c_grey[]        = "#242424";
static const char c_light_grey[]  = "#323232";

static const char c_off_white[]   = "#e0e0e0";
static const char c_white[]       = "#f5f5f5";

static const char c_red[]         = "#da291c";
static const char c_flat_red[]    = "#e0493e";

static const char c_green[]       = "#328b2d";
static const char c_flat_green[]  = "#4f9a4a";

static const char c_blue[]        = "#003052";
static const char c_flat_blue[]   = "#004b87";

static const char c_yellow[]      = "#e07400";
static const char c_flat_yellow[] = "#ffcd00";

static const char c_purple[]      = "#66023c";
static const char c_flat_purple[] = "#972066";

static const char *colors[][4]      = {
	/*               fg             bg             border         float          */
	[SchemeNorm] = { c_white,       c_dark_grey,   c_dark_grey,   c_dark_grey    },
	[SchemeSel]  = { c_white,       c_flat_green,  c_off_white,   c_off_white    },
	[SchemeUrg]  = { c_white,       c_flat_green,  c_flat_red,    c_flat_red     },
};

/* scratchpads */
const char *sp_terminal[] = {"alacritty", "--class", "sp_term", "--config-file", ".config/alacritty/scratchpad.yml", NULL };
const char *sp_keepassxc[] = {"keepassxc", NULL };

static Scratchpad scratchpads[] = {
	/* name          cmd */
	{"sp_term",  sp_terminal},
	{"sp_pass",  sp_keepassxc},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* Note
	 * St with Xresources patch is 'St' otherwise it is 'st'
	 */
	/* class      instance    title       tags mask     isfloating   isfreesize   isterminal   noswallow    monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           1,           0,           0,           -1 },
	{ "Surf",     NULL,       NULL,       0,            0,           0,           0,           -1,          -1 },
	{ "Emacs",    NULL,       NULL,       0,            0,           0,           0,           -1,          -1 },
	{ "st",       NULL,       NULL,       0,    	    0,           0,           1,           0,           -1 },
	{ "St",       NULL,       NULL,       0,            0,           0,           1,           0,           -1 },
	{ "Alacritty",NULL,       NULL,       0,    	    0,           0,           1,           0,           -1 },
	{ NULL,       "nextcloud",NULL,       0,            1,           1,           0,           0,           -1 },
	{ NULL,       NULL,   "Event Tester", 0,            0,           0,           0,           1,           -1 },
	/* steam */
	{ "Steam",    "Steam", "Friends List",0,            1,           1,           0,           0,           -1 },
	/* scratchpads */
	{ NULL,       "sp_term",  NULL,       SPTAG(0),     1,           1,           0,           0,           -1 },
	{ NULL,       "keepassxc",NULL,       SPTAG(1),     1,           1,           0,           0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", c_dark_grey, "-nf", c_white, "-sb", c_flat_green, "-sf", c_off_white, NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ControlMask,           XK_space,  togglealwaysontop, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Right,  viewnext,       {0} },
	{ MODKEY,                       XK_Left,   viewprev,       {0} },
	{ MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
	{ MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	{ MODKEY,                       XK_bracketleft,  togglescratch,  {.ui = 0 } },
	{ MODKEY,                       XK_bracketright, togglescratch,  {.ui = 1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ ControlMask|AltMask,          XK_Delete, quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

