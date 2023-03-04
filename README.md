dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.

This repository includes base dwm 6.4, a number of patches (seen by
commits preceeded by "apply:") and some custom changes and
configuration.


Requirements
------------
In order to build dwm you need the Xlib and yajl header files.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

For example you may wish to use:

    exec dwm 2> /tmp/dwm.log

(Which will make troubleshooting easier.)

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.


Bar Configuration
-----------------

Via patching Polybar is used as the bar, assuming you have configured
Polybar and installed
[polybar-dwm-module](https://github.com/mihirlad55/polybar-dwm-module)
(available on the AUR), then you *must* provide a startbar script:

```sh
#!/bin/sh
polybar-msg cmd quit
polybar main > /tmp/polybar-dwm.log 2>&1 &
```

`main` must be substituted for your bar's name.


Troubleshooting
---------------

If you followed the setup provided above the logs in `/tmp/dwm.log`
and `/tmp/polybar-dwm.log` will be helpful.

### "module/dwm" stopped with reason: [dwmipcpp] Client with window id XXXXX not found

Via [the github issue](https://github.com/mihirlad55/polybar-dwm-module/issues/26)
this can be solved by removing `<label-title>` in `[module/dwm]` and
the using `[module/title]` for the window title instead.

