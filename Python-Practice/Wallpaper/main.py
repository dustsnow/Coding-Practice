import urllib
import json
import os
import time
webpage = urllib.urlopen("http://www.bing.com/HPImageArchive.aspx?format=js&idx=0&n=1&nc=1397809837851&pid=hp");#get the rss feed from bing
webpage_str = ""
#save the rss to a string
for line in webpage:
	webpage_str += line
webpage_json = json.loads(webpage_str)#decode rss string
date = webpage_json['images'][0]['startdate']#get date
dest = "/home/penghou/Pictures/BingWallpaper/"+date+".jpg"#construct destination string to save the file
url = "http://www.bing.com"
url += webpage_json['images'][0]['url']#construct image url
url = url.replace("1366","1920")#change url to fetch high resolution image
url = url.replace("768","1080")#change url to fetch high resolution image
urllib.urlretrieve(url,dest)
command = "gsettings set org.gnome.desktop.background picture-uri 'file://" + dest +"'"#construct command of changing linux background
start = time.time()
while not os.path.isfile(dest):
	if (time.time() - start) > 10:
		break
os.system(command)#execute command to change the desktop
