#!/usr/bin/python

import re, urllib, urllib2

class Client(object):
  def __init__(self, email, password):
    super(Client, self).__init__()
    self.email = email
    self.password = password

  def _get_auth_token(self, email, password, source, service):
    url = "https://www.google.com/accounts/ClientLogin"
    params = {
      "Email": email, "Passwd": password,
      "service": service,
      "accountType": "HOSTED_OR_GOOGLE",
      "source": source
      }
    req = urllib2.Request(url, urllib.urlencode(params))
    return re.findall(r"Auth=(.*)", urllib2.urlopen(req).read())[0]

  def get_auth_token(self):
    #print "Getting Auth Token..."
    source = type(self).__name__
    return self._get_auth_token(self.email, self.password, source, service="wise")

  def download(self, spreadsheet_id, gid=0, format="xlsx"):
    url_format = "https://spreadsheets.google.com/feeds/download/spreadsheets/Export?key=%s&exportFormat=%s&gid=%i"
    headers = {"Authorization": "GoogleLogin auth=" + self.get_auth_token(),"GData-Version": "3.0"}
    #print "Sending Request..."
    req = urllib2.Request(url_format % (spreadsheet_id, format, gid), headers=headers)
    return urllib2.urlopen(req)

# Prompt User for user name and return as a string
def getUserFromPrompt():
    username = raw_input("Your '@electricimp.com' Username:")
    return username

# Write a "user=<username>" line into .libuser
# This file is used by getUserFromDotfile to ID the user
def updateDotfile(username):
    with open(".libuser", 'w') as userfile:
        userfile.write("user="+username)
    return username

# Look for .libuser in the database folder and parse for username
# If the file or information are not present, prompt the user and fix it
def getUserFromDotfile():
    try:
        with open(".libuser", 'r') as userfile:
            for line in userfile:
                field = line.partition('=')[0].strip()
                value = line.partition('=')[2].strip()
                if "user" in field:
                    return value
            # if we're here, we didn't find "user" in the dotfile
            print "Username not found in .libuser. Adding now."
            return updateDotfile(getUserFromPrompt())
    except IOError:
        # This means .libuser didn't exist
        return updateDotfile(getUserFromPrompt())

if __name__ == "__main__":
  import getpass, os

  sheets = {
    'passives'         : '0AoVOC9OWjPRldDZkaVpMbUtrSzZpRjE1NE9GYzdoQXc',
    'discretes'        : '0AoVOC9OWjPRldG51Q3NjSEFWUmVtSE53Tjh5UU1lLWc',
    'connectors'       : '0AoVOC9OWjPRldFZRQ0I1a2VjUXlPZFlaT0pOMWtJVmc',
    'electromechanical': '0AoVOC9OWjPRldDBBRmU5Q2EwZXV4S0dOM081TllYVmc',
    'opto'             : '0AoVOC9OWjPRldHZBRDNRMGR2MVoyU0M1am5tMW1JNnc',
    'xtalosc'          : '0AoVOC9OWjPRldDdISEdtSFI0MjFySEktSWdWb2hNVVE',
    'ic'               : '0AoVOC9OWjPRldG9GZUlLZDg0X3MydW9LWl96QXYwbFE',
    'mechanical'       : '0AiR85SKN_-TndGRTV3JzVGNxaGRNRHhvZERIRFNjMWc',
    'modules'          : '0AoVOC9OWjPRldDZuSmRFSlQ5MzVSU2lDVWpkaDl0b1E',
    'electrical'       : '0AoVOC9OWjPRldEo4bExMYWVKQ3VFSmpSZTN3S0t4S0E',
    }

  os.chdir('Z:\ei-hardware\imp-sharedlibs\database')
  
  # Create client
  email =  getUserFromDotfile() + '@electricimp.com';
  password = getpass.getpass('Password for ' + email + ':')
  gs = Client(email, password)


  for sheet, sheet_id in sheets.iteritems():

    print "Downloading "+sheet+".xlsx"

    # Request a file-like object containing the spreadsheet's contents
    try:
      xls_file = gs.download(sheet_id)
    except urllib2.URLError as err:
      print err
      raw_input("Press enter to quit.")
      exit()

    # Open the xls file for writing
    try:
      out = open(sheet+'.xlsx','wb')
    except IOError as err:
      print err
      raw_input("Press enter to quit.")
      exit()

    # Write file out
    for row in xls_file:
      out.write(row)
