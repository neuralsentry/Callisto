import json
import subprocess

def analyzeC(function):
    # Write function to file for analysis
    f = open("sgrep/semgrep.c", "w")
    f.write(function)
    f.close()

    resultsConcat = ""
    resultsLineNum = []
    sGrepResults = subprocess.run(["semgrep", "--config=sgrep/semgrep-rules-c/c", "--json", "sgrep/semgrep.c"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    sGrepResults = sGrepResults.stdout.decode('utf-8')
    sGrepResults = json.loads(sGrepResults)
    
    if not sGrepResults['results']:
      return ''
    else:
      return sGrepResults["results"][0]["extra"]["message"]
