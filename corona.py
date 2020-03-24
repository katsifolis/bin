#!/usr/local/bin/python3
# Greece mortality COVID19 nums
import requests
# Url For Greece
url = 'https://coronavirus-tracker-api.herokuapp.com/v2/locations?country_code=GR'

r = requests.get(url)
t = r.json()["latest"]
conf = t["confirmed"]
dead = t["deaths"]
recov = t["recovered"]
print(' 😷 ' + ": " + str(conf), end='')
print(' 💀 ' + ": " + str(dead), end='')
print(' 🥳  ' + ": " + str(recov))
