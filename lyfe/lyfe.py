#/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Fetches lyrics from azlyrics.com

"""

from bs4 import BeautifulSoup
from urllib import request
import sys

# Globals

"""
- 0 for beginning
- 1 for continuing
- 2 for error typing
"""

def quit(s):
    print("\n" + s)
    flag = False
    sys.exit()

def replace_(s, c):
    s = s.lower()
    for i in c:
        s = s.replace(i, '')

    return s

def fetch(song, page):
    #Assertions
    try: 
        req = request.urlopen('https://search.azlyrics.com/search.php?q={}&w=songs&p={}'.format(song.replace(' ', '+'), page))
        print(req.url)
    except:
        quit("Didn't provide any song name")

    if len(sys.argv) > 2:
        quit('Too many arguments')
    elif sys.argv[1] is (int or float):
        quit('Numbers are forbidden')
    
    soup = BeautifulSoup(req.read(), 'html5lib')

    # Searching for the Sorry string with no results
    try:
        if "Sorry" in soup.find("div", class_="alert").text:
            quit("No results found :(")
    except EOFError:
        print("exiting...")
    except:
        pass

    band = ''
    song_name = ''
    counter = 1
    songs = []
    search_result = []

    for i in soup.find_all(class_='text-left visitedlyr'):
        
        band = i.b.get_text()
        song_name = i.b.next_element.next_element.next_element.get_text()

        # Some songs happen to be unfilled with their respective artist
        if song_name == '' and band == '':
            quit('No results, try again :)')
        
        if band == '':
            band = 'NO_CLUE'


        # Ignores unicode characters + special chars because the url completely ignores them and 
        search_result.append(str(counter) + '. ' + song_name + ' - ' + band)
        band = replace_(band, '() \'')
        song_name = replace_(song_name, '() \'')
        songs.append(band + ' ' +  song_name)

        counter = counter + 1
#
##    try:
##        slctn = int(input('Make your selection, or see more results (0): '))
##        if slctn == 0:
##            return True
##        if slctn > 20 or slctn < 1:
##            slctn = int(input('Invalid,\nMake your selection: '))
#
#    except ValueError:
#        quit('Bad luck: str given')
#    except EOFError:
#        quit('Exiting...')
#        

#    req = request.urlopen('https://www.azlyrics.com/lyrics/{}/{}.html'.format(songs[slctn - 1].split(' ')[1], songs[slctn - 1].split(' ')[0]))
#
#    soup = BeautifulSoup(req.read(), 'html5lib')
#    title = soup.find("div", class_='ringtone').find_next("div")
#    lyr = title.get_text()
    
    retur
    search_result, False

    
def run(song):
    page = 0
    flag = True
    while flag:
        page = page + 1
        song_list, flag = fetch(song, page)
        return song_list
