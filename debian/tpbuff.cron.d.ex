#
# Regular cron jobs for the tpbuff package
#
0 4	* * *	root	[ -x /usr/bin/tpbuff_maintenance ] && /usr/bin/tpbuff_maintenance
