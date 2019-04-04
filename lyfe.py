# Abstract
# Lyric Fetcher - LyFe

"""
Fetches lyrics from azlyrics.com

"""
from bs4 import BeautifulSoup
from urllib import request
import sys

def quit(s):
    print(s)
    sys.exit()
    

def fetch():

    #Assertions
    try: 
        req = request.urlopen('https://search.azlyrics.com/search.php?q=%s&w=songs&p=1' % sys.argv[1])
    except:
        quit("Didn't provide any song name")

    if len(sys.argv) > 2:
        quit('Too many arguments')
    
    soup = BeautifulSoup(req.read(), 'html5lib')

    # Searching for the Sorry string with no results
    try:
        if "Sorry" in soup.find("div", class_="alert").text:
            quit("No results found :(")
    except:
        pass

    band = ''
    song_name = ''
    counter = 1
    songs = []

    for i in soup.find_all(class_='text-left visitedlyr'):
        
        band = i.b.get_text()
        song_name = i.b.next_element.next_element.next_element.get_text()
        if band == '' or song_name == '':
            quit('No results, try again :)')

        #Ignores unicode characters + special chars because the url completely ignores them and 
        band = band.encode('ascii', 'ignore').decode('utf-8').replace('(', '').replace(')', '')
        song_name = song_name.encode('ascii', 'ignore').decode('utf-8').replace('(', '').replace(')', '')

        print(str(counter) + '. ' + song_name + ' - ' + band)
        songs.append(band.lower().replace(' ', '') + ' ' +  song_name.lower().replace(' ', ''))

        counter = counter + 1

    try:
        slctn = int(input('Make your selection: '))
        while slctn > 20 or slctn < 0: 
            slctn = int(input('Invalid,\nMake your selection: '))

    except:
        sys.exit()

    req = request.urlopen('https://www.azlyrics.com/lyrics/{}/{}.html'.format(songs[slctn - 1].split(' ')[1], songs[slctn - 1].split(' ')[0]))

    soup = BeautifulSoup(req.read(), 'html5lib')
    title = soup.find("div", class_='ringtone').find_next("div")
    lyr = title.get_text()
    print(lyr)
    
fetch()
