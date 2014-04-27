The crontab job has to have "DISPLAY=0.0" to make it work. Such as

*/30 * * * * DISPLAY=0.0 python main.py
