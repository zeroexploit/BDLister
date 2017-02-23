# BDLister
Reads the Bind9 Query Logs to Ouput a filtered List of Domain Names to another File or the Console. Designed to list the Domains a single IP Address has queried in an easylie readable Format. Additionally Domains containing special Keywords can be highlighted in Console Ouput.

# Highlighting
In Order to highlight special Domains or Search Terms in the resulting Domain Name List, create a simple Text File containing one Search Term per Line

# Usage Example
    
    bdlister [Log File] [IP Address] [Output] [Sorting] [Highlight]
    bdlister "/var/log/query.log" "192.168.1.110" - time
    bdlister "/var/log/query.log" "192.168.1.110" "/root/192_168_1_110.query" count "/root/hlist.txt"

# Parameters
    Log File:   Path to the Bind9 Query Log
    IP Address: Ip of the Client you want to List the Domains for
    Sorting: 
        time -  The Output will be sorted from the oldest to the newest Entry.
        count - The Output will be sorted from the least queried Domain to the most queried one
    Highlight:  Path to a plain Textfile containing a single Keyword per Line. Domains containing one of these Keywords will be
                highlighted on Console Ouput

Notice: The Order of these Parameters is important! Only the Highlight File is not required!
