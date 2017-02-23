# BDLister
Reads the Bind9 Query Logs to Ouput a filtered List of Domain Names to another File or the Console. Designed to list the Domains a single IP Address has queried in an easylie readable Format. Additionally Domains containing special Keywords can be highlighted in Console Ouput.

# Usage
  bdLister <Log File> <IP Address> <Output File | -> <Sorting: time | count> [Highlight: Needle File]
  
# Example
  bdlister "/var/log/query.log" "192.168.1.110" time
  bdlister "/var/log/query.log" "192.168.1.110" time "/root/hlist.txt"
  
# Highlighting
In Order to highlicht special Domains or Search Terms in the resulting Domain Name List, create a simple Text File containing one Search Term per Line
