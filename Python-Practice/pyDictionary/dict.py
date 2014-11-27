import urllib
import json
import os
import time
webpage = urllib.urlopen("http://dict.cn/ws.php?q=good");#get the rss feed from bing
for line in webpage:
	print line
