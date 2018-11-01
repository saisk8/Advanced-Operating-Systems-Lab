printf 'Oldest Process:\n';
ls -ltr /proc/ | head -n 2 | tail -n 1
printf '\nYoungest Process\n';
ls -lt /proc/ | head -n 2 | tail -n 1
printf '\nSmallest process\n';
ps -eo pid,%mem --sort=%mem | head -n 2 | tail -n 1
printf '\nLargest process\n';
ps -eo pid,%mem --sort=%mem | tail -n 1
